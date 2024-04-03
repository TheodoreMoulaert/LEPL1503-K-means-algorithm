#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include "../headers/distance.h"
#include "../headers/main.h"
#include "../headers/parse_binary_input.h"
#include "../headers/binary_file_reader.h" 
#include "../headers/k_means.h"
#include "../headers/write_csv.h"
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distortion.h"
#include "../headers/combinaison.h"


typedef struct {
    FILE *input_stream;
    FILE *output_stream;
    uint32_t n_threads;
    uint32_t k;
    uint32_t n_first_initialization_points;
    bool quiet;
    squared_distance_func_t squared_distance_func;
} args_t;


void usage(char *prog_name) {
    fprintf(stderr, "USAGE:\n");
    fprintf(stderr, "    %s [-p n_combinations_points] [-n n_threads] [input_filename]\n", prog_name);
    fprintf(stderr, "    -k n_clusters (default value: 2): the number of clusters to compute\n");
    fprintf(stderr, "    -p n_combinations (default value: equal to k): consider the n_combinations first points present in the input to generate possible initializations for the k-means algorithm\n");
    fprintf(stderr, "    -n n_threads (default value: 4): sets the number of computing threads that will be used to execute the k-means algorithm\n");
    fprintf(stderr, "    -f output_file (default value: stdout): sets the filename on which to write the csv result\n");
    fprintf(stderr, "    -q quiet mode: does not output the clusters content (the \"clusters\" column is simply not present in the csv)\n");
    fprintf(stderr, "    -d distance (manhattan by default): can be either \"euclidean\" or \"manhattan\". Chooses the distance formula to use by the algorithm to compute the distance between the points\n");
}

int parse_args( args_t *args, int argc, char *argv[]) {
    memset(args, 0, sizeof(args_t));    // set everything to 0 by default
    // the default values are the following, they will be changed depending on the arguments given to the program
    args->k = 2;
    args->n_first_initialization_points = args->k;
    args->n_threads = 1;
    args->output_stream = stdout;
    args->quiet = false;
    args->squared_distance_func = squared_manhattan_distance;
    int opt;
    while ((opt = getopt(argc, argv, "n:p:k:f:d:q")) != -1) {
        switch (opt)
        {
            case 'n':
                args->n_threads = atoi(optarg);
                if (args->n_threads <= 0) {
                    fprintf(stderr, "Wrong number of threads. Needs a positive integer, received \"%s\"\n", optarg);
                    return -1;
                }
                break;
            case 'p':
                args->n_first_initialization_points = atoi(optarg);
                if (args->n_first_initialization_points <= 0) {
                    fprintf(stderr, "Wrong number of initialization points. Needs a positive integer, received \"%s\"\n", optarg);
                    return -1;
                }
                break;
            case 'k':
                args->k = atoi(optarg);
                if (args->k <= 0) {
                    fprintf(stderr, "Wrong k. Needs a positive integer, received \"%s\"\n", optarg);
                    return -1;
                }
                break;
            case 'f':
                args->output_stream = fopen(optarg, "w");
                if (!args->output_stream) {
                    fprintf(stderr, "could not open output file %s: %s\n", optarg, strerror(errno));
                    return -1;
                }
                break;
            case 'q':
                args->quiet = true;
                break;
            case 'd':
                if (strcmp("euclidean", optarg) == 0) {
                    args->squared_distance_func = squared_euclidean_distance;
                }
                break;
            case '?':
                usage(argv[0]);
                return 1;
            default:
                usage(argv[0]);
        }
    }
    if (optind == argc) {
        args->input_stream = stdin;
    } else {
        args->input_stream = fopen(argv[optind], "r");
        if (!args->input_stream) {
            fprintf(stderr, "could not open file %s: %s\n", argv[optind], strerror(errno));
            return -1;
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    args_t program_arguments;   // Allocate the args on the stack
    parse_args(&program_arguments, argc, argv);

    if (program_arguments.n_first_initialization_points < program_arguments.k) {
        fprintf(stderr, "Cannot generate an instance of k-means with fewer initialization points than needed clusters: %"PRIu32" < %"PRIu32"\n",
                program_arguments.n_first_initialization_points, program_arguments.k);
        return -1;
    }

    fprintf(stderr, "\tnumber of threads executing the Lloyd's algorithm in parallel: %" PRIu32 "\n", program_arguments.n_threads);
    fprintf(stderr, "\tnumber of clusters (k): %" PRIu32 "\n", program_arguments.k);
    fprintf(stderr, "\tconsidering all the combinations of the %" PRIu32 " first points of the input as initializations of the Lloyd's algorithm\n", program_arguments.n_first_initialization_points);
    fprintf(stderr, "\tquiet mode: %s\n", program_arguments.quiet ? "enabled" : "disabled");
    fprintf(stderr, "\tsquared distance function: %s\n", program_arguments.squared_distance_func == squared_manhattan_distance ? "manhattan" : "euclidean");

    squared_distance_func_t DISTANCE_SQUARED;
    if (program_arguments.squared_distance_func == squared_manhattan_distance) {
        DISTANCE_SQUARED = squared_manhattan_distance;
    } else {
        DISTANCE_SQUARED = squared_euclidean_distance;
    }

    uint32_t dim = get_dimension_from_binary_file(program_arguments.input_stream);
    if (dim == 0) {
        printf("Error retrieving dimension.\n");
        fclose(program_arguments.input_stream);
        return 1;
    }
    uint32_t nbr_vectors = get_nbr_vectors_from_binary_file(program_arguments.input_stream);
    if (nbr_vectors == 0) {
        printf("Error retrieving the number of vectors.\n");
        fclose(program_arguments.input_stream);
        return 1;
    }

    point_t *points;
    uint32_t num_points;
    point_t** vectors = point_input(program_arguments.input_stream);
     if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }
    //uint64_t size_clu = size_clusters(vectors); //1
    uint32_t dim = vectors[0]->dim; //2
    uint64_t vector_count = vectors[0]->nbr_vector; //7

    //uint32_t K = (uint64_t)size_clu; //nombre de centroids à trouver
    uint32_t K = program_arguments.k;

    cluster_t sol_init_centroids;
    sol_init_centroids.data = (point_t*)malloc(K*sizeof(point_t));
    if (sol_init_centroids.data == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les clusters initiaux\n");
        exit(EXIT_FAILURE);
    }
    point_t *sol_centro = NULL;
    cluster_t *sol_clusters = NULL;
    uint64_t sol_distortion = UINT64_MAX; // Utilisez UINT64_MAX pour initialiser sol_distortion à la plus grande valeur possible

    point_t *list_init_centroids = NULL;
    point_t *list_centro = NULL;
    cluster_t *list_clusters = NULL;
    uint64_t *list_distortion = NULL;

    uint64_t combi = combinaison(p, program_arguments.k);

    // Allocation dynamique de mémoire pour les tableaux
    list_init_centroids = malloc(combi * sizeof(point_t));
    list_centro = malloc(combi * sizeof(point_t));
    list_clusters = malloc(combi * sizeof(cluster_t *));
    list_distortion = malloc(combi * sizeof(uint64_t));
    
    // Vérification des allocations mémoire
    if (list_init_centroids == NULL || list_centro == NULL || list_clusters == NULL || list_distortion == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des clusters initiaux
    cluster_t *centro_initial_list = malloc(combi * sizeof(cluster_t));
    if (centro_initial_list == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les clusters initiaux\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des combinaisons
    point_t **vect = malloc(combi * sizeof(point_t *));
    if (vect == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les vecteurs\n");
        exit(EXIT_FAILURE);
    }

    for (uint64_t i = 0; i < combi;i++) {
        vect[i] = vectors[i];
    }

    //cluster_t *combi_cluster;


    for (uint64_t i = 0; i < combi; i++) {

        centro_initial_list[i].data = vect[i]; //centro_initial_list[i].data = vect[i];
        cluster_t *combi_cluster = kmeans(centro_initial_list, program_arguments.k, vector_count, dim, DISTANCE_SQUARED);//, cluster_t combi_clu k_means(point_t *initial_centroids, uint32_t K, point_t **vectors, uint64_t num_vectors, uint32_t dimensions)
        point_t *combi_centro;
        for (uint64_t j = 0; j < combi_cluster->size; j++) {
                combi_centro[j] = combi_cluster->center;
        }
        uint64_t combi_distortion = distortion(combi_cluster, program_arguments.k , DISTANCE_SQUARED);//(cluster_t const **clusters, uint32_t num_clusters, squared_distance_func_t DISTANCE_SQUARED)
        //uint64_t distortion(cluster_t const **clusters, uint32_t num_clusters, DISTANCE_SQUARED) {
        if (sol_distortion > combi_distortion){
            sol_distortion = combi_distortion;
            sol_centro = combi_centro;//combi_cluster[i]->center;
            sol_clusters = combi_cluster;
            sol_init_centroids = centro_initial_list[i];//.center;// centro_initial_list;
        }
        list_init_centroids = centro_initial_list[i].data; //centro_initial_list[i].center;
        list_distortion[i] = combi_distortion;
        list_centro = combi_centro;
        list_clusters = combi_cluster;
    }
    for (uint64_t i = 0; i < combi; i++) {
        free(centro_initial_list[i].data);
    }
    free(centro_initial_list);
    free(vect);

    for (uint64_t i = 0; i < combi; i++) {
        free(list_clusters[i].data);
        //free(list_clusters[i]);
    }
    free(list_clusters);
    free(list_init_centroids);
    free(list_centro);
    free(list_distortion);
    
    //fprintf(stderr,"Best initialisation centroids: % \n",);
    fprintf(stderr, "Best initialisation centroids: :\n");
    for (uint64_t i = 0; i < sol_init_centroids.data->nbr_vector; ++i) {
        fprintf(stderr, "Centroid %lu : (%" PRId64 ",%" PRId64 ")\n", i + 1, sol_init_centroids.data->coords[0], sol_init_centroids.data->coords[1]);
    }
    fprintf(stderr,"Best centroids: (%" PRId64 ",%" PRId64 ")\n",sol_centro->coords[0],sol_centro->coords[1]);
    //fprintf(stderr,"Best clusters: (%" PRId64 ",%" PRId64 ")\n",sol_clusters->data->coords[0],sol_clusters->data->coords[1]);
    fprintf(stderr, "Best clusters: :\n");
    //for  (uint64_t j=0;j< program_arguments.k;j++){
    for (uint64_t i = 0; i < sol_clusters->size; ++i) {
        fprintf(stderr, "Cluster %lu : (%" PRId64 ",%" PRId64 ")\n", i + 1, sol_clusters->data[i].coords[0], sol_clusters->data[i].coords[1]);
        
    }
    
    fprintf(stderr,"Minimal sum of squared distances: %" PRId64 "\n",sol_distortion);

 
    int8_t write_result = write_csv(sol_clusters, sol_init_centroids, sol_distortion, points, vector_count, program_arguments.k, dim);
    
    if (write_result != 0) {
        printf("Error writing results to CSV.\n");
        fclose(program_arguments.input_stream);
        return 1;
    }

    free(points);
    free(sol_clusters);
    fclose(program_arguments.input_stream);
    if (program_arguments.output_stream != stdout) {
        fclose(program_arguments.output_stream);
    }

    return 0;
}