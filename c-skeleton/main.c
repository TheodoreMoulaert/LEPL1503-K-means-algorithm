#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include "headers/distance.h"
#include "headers/binary_file_reader.h" 
#include "headers/k_means.h"
#include "headers/write_csv.h"
#include "headers/point.h"
#include "headers/cluster.h"
#include "headers/combinaison.h"
#include "headers/assign_vector_to_centro.h"
#include "headers/update_centroids.h"


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

int parse_args(args_t *args, int argc, char *argv[]) {
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
    args_t program_arguments;   // allocate the args on the stack
    parse_args(&program_arguments, argc, argv);

    if (program_arguments.n_first_initialization_points < program_arguments.k) {
        fprintf(stderr, "Cannot generate an instance of k-means with less initialization points than needed clusters: %"PRIu32" < %"PRIu32"\n",
                program_arguments.n_first_initialization_points, program_arguments.k);
        return -1;
    }
    // the following fprintf (and every code already present in this skeleton) can be removed, it is just an example to show you how to use the program arguments
    fprintf(stderr, "\tnumber of threads executing the LLoyd's algoprithm in parallel: %" PRIu32 "\n", program_arguments.n_threads);
    fprintf(stderr, "\tnumber of clusters (k): %" PRIu32 "\n", program_arguments.k);
    fprintf(stderr, "\twe consider all the combinations of the %" PRIu32 " first points of the input as initializations of the Lloyd's algorithm\n", program_arguments.n_first_initialization_points);
    fprintf(stderr, "\tquiet mode: %s\n", program_arguments.quiet ? "enabled" : "disabled");
    fprintf(stderr, "\tsquared distance function: %s\n", program_arguments.squared_distance_func == squared_manhattan_distance ? "manhattan" : "euclidean");
    

    FILE *input_file = program_arguments.input_stream;
    FILE *output_file = program_arguments.output_stream;
    uint32_t p = program_arguments.n_first_initialization_points;
    if(p <= 0){
        fprintf(stderr, "Wrong number of initialization points. Needs a positive integer, received \"%d\"\n", program_arguments.n_first_initialization_points);
        return -1;
    }
    uint64_t npoints;
    uint32_t dimension; 
    uint32_t k = program_arguments.k;
    if (k <= 0) {
        fprintf(stderr, "Wrong k. Needs a positive integer, received \"%d\"\n", k);
        return -1;
    }


    bool quiet_mode = program_arguments.quiet;
    squared_distance_func_t DISTANCE_SQUARED;
    point_t** donnes;
    


    if (program_arguments.squared_distance_func == squared_manhattan_distance) {
        DISTANCE_SQUARED = squared_manhattan_distance;
    } else {
        DISTANCE_SQUARED = squared_euclidean_distance;
    }
    donnes =  point_input(input_file, &dimension, &npoints);
    if(p>npoints){
        p = npoints; 

    }
    if (npoints <= 0) {
        fprintf(stderr, "Wrong number of points. Needs a positive integer, received \"%lu\"\n", npoints);
        return -1;
    }
    if (dimension <= 0) {
        fprintf(stderr, "Wrong dimension. Needs a positive integer, received \"%u\"\n", dimension);
        return -1;
    }


    int64_t nombre_comb = combinaison(p,k);
    point_t ***initial_combinations = generate_combinations(donnes,npoints,k,p);


    point_t **initial_centroids = (point_t **)malloc(nombre_comb* sizeof(point_t *));
    point_t **initial_conserve = (point_t **)malloc(nombre_comb* sizeof(point_t *));
    for (int i = 0; i < nombre_comb; i++) {
    // Utilisation de calloc pour initialiser chaque élément à NULL
        initial_centroids[i] = (point_t *)malloc(k* sizeof(point_t));
        if (initial_centroids[i] == NULL) {
            // Gestion d'erreur si l'allocation échoue
            exit(EXIT_FAILURE);
        }

        for (uint32_t j = 0; j < k; j++) {
            //initial_centroids[i][j].dim = dimension; // Exemple de dimension
            initial_centroids[i][j].coords = (int64_t *)malloc(dimension* sizeof(int64_t));
            if (initial_centroids[i][j].coords == NULL) {
                // Gestion d'erreur si l'allocation échoue
                exit(EXIT_FAILURE);
            }
            for  (uint32_t m=0;m<dimension;m++){
                initial_centroids[i][j].coords[m] = 0;
            }      
        }

        
    }
    for (int i = 0; i < nombre_comb; i++) {
    // Utilisation de calloc pour initialiser chaque élément à NULL
        initial_conserve[i] = (point_t *)malloc(k* sizeof(point_t));
        if (initial_conserve[i] == NULL) {
            // Gestion d'erreur si l'allocation échoue
            exit(EXIT_FAILURE);
        }

        for (uint32_t j = 0; j < k; j++) {
          
            initial_conserve[i][j].coords = (int64_t *)malloc(dimension* sizeof(int64_t));
            if (initial_conserve[i][j].coords == NULL) {
                // Gestion d'erreur si l'allocation échoue
                exit(EXIT_FAILURE);
            }
            for  (uint32_t m=0;m<dimension;m++){
                initial_conserve[i][j].coords[m] = 0;
            }      
        }

        
    }
    
    for (int64_t i = 0; i < nombre_comb; i++) {
        for (uint32_t j = 0; j < k; j++) {
            // Copier la dimension
            initial_centroids[i][j].dim =dimension; //initial_combinations[i][j][0].dim;
            //initial_centroids[i][j].coords = initial_combinations[i][j][0].coords;
            memcpy(initial_centroids[i][j].coords, initial_combinations[i][j][0].coords, dimension * sizeof(int64_t));

        }
    }
    for (int64_t i = 0; i < nombre_comb; i++) {
        for (uint32_t j = 0; j < k; j++) {
            // Copier la dimension
            initial_conserve[i][j].dim =dimension; //initial_combinations[i][j][0].dim;
           
            //initial_centroids[i][j].coords = initial_combinations[i][j][0].coords;
            memcpy(initial_conserve[i][j].coords, initial_combinations[i][j][0].coords, dimension * sizeof(int64_t));
           
            initial_conserve[i][j].nbr_vector = initial_combinations[i][j][0].nbr_vector;
          
        }
    }

    point_t **final_centroids = initial_centroids;
    uint64_t distortion_list[nombre_comb];
    
    cluster_t*** clusters_list = malloc(nombre_comb*sizeof(cluster_t**)); 


    cluster_t **temps_cluster = (cluster_t **)malloc(k *sizeof(cluster_t *));
    if (temps_cluster == NULL) {
        // Gestion d'erreur si l'allocation échoue
        exit(EXIT_FAILURE);
    }

    // Allocation et initialisation de chaque élément de la matrice
    for (uint32_t i = 0; i < k; i++) {
      
        temps_cluster[i] = (cluster_t *)malloc(npoints*sizeof(cluster_t));
        if (temps_cluster[i] == NULL) {
            // Gestion d'erreur si l'allocation échoue
            exit(EXIT_FAILURE);
        }
    }
 
    for (int64_t i =0;i< nombre_comb;i++){
        for (uint32_t j=0;j<k;j++){
            temps_cluster[j]->centroide.dim = dimension;
            temps_cluster[j]->centroide.coords=initial_centroids[i][j].coords;

            temps_cluster[j]->centroide.nbr_vector = initial_centroids[i][j].nbr_vector;
            if (j==0){
                temps_cluster[j]->data = donnes;
                temps_cluster[j]->size = npoints;
            }
            else{
                temps_cluster[j]->data = NULL;
                temps_cluster[j]->size = 0;

            }
        }
    }

    point_t* temp_centroide = (point_t*) malloc(k*sizeof(point_t));

    cluster_t** temps_result_cluster= malloc(k* sizeof(cluster_t*)); 
    for(int64_t i = 0; i < k; i++){
        temps_result_cluster[i] = malloc(sizeof(cluster_t));
    }


    for (uint64_t i = 0; i < nombre_comb; i++) {
        
        uint64_t temp_distorsion = 0;
        temps_result_cluster = k_means(temps_cluster, npoints, k, initial_centroids[i], final_centroids[i], DISTANCE_SQUARED);
     
        for (uint32_t m=0 ; m<k; m++){
            temp_centroide[m].coords = temps_result_cluster[m]->centroide.coords;
            temp_centroide[m].nbr_vector = temps_result_cluster[m]->centroide.nbr_vector;
            temp_centroide[m].dim = dimension;
        }
      
        temp_distorsion = distortion((cluster_t const **)temps_result_cluster, k, DISTANCE_SQUARED);

        *final_centroids[i] = *temp_centroide; 
        clusters_list[i] = temps_result_cluster;
        distortion_list[i] = temp_distorsion;
       
        
    }

    //print csv
   
    write_csv(output_file, distortion_list, initial_conserve, final_centroids, clusters_list, k, dimension, nombre_comb, quiet_mode);


        // Libérer la mémoire pour les points de données
    for (uint64_t i = 0; i < npoints; i++) {
        free(donnes[i]->coords);
        free(donnes[i]);
    }
    free(donnes);

    // Libérer la mémoire pour les combinaisons initiales
    for (int64_t i = 0; i < nombre_comb; i++) {
    
        free(initial_combinations[i]);
    }
    free(initial_combinations);

    for (int64_t i = 0; i < nombre_comb; i++) {
        free(initial_centroids[i]);
        free(initial_conserve[i]);
    }
    free(initial_centroids);
    free(initial_conserve);

    for (uint32_t i = 0; i < k; i++) {
        free(temps_cluster[i]);
    }
    free(temps_cluster);

    // Libérer la mémoire pour les clusters de résultats temporaires
    for (uint32_t i = 0; i < k; i++) {
        free(temps_result_cluster[i]);
    }
    free(temps_result_cluster);
    free(temp_centroide);
    free(clusters_list);

    // close the files opened by parse_args
    if (program_arguments.input_stream != stdin) {
        fclose(program_arguments.input_stream);
    }
    if (program_arguments.output_stream != stdout) {
        fclose(program_arguments.output_stream);
    }
    return 0;
}
