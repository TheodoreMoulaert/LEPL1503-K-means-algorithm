#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
//#include "../c-skeleton/headers/main.h"
#include "../c-skeleton/headers/distance.h"
#include "../c-skeleton/headers/binary_file_reader.h" 
#include "../c-skeleton/headers/k_means.h"
#include "../c-skeleton/headers/write_csv.h"
#include "../c-skeleton/headers/point.h"
#include "../c-skeleton/headers/cluster.h"
#include "../c-skeleton/headers/combinaison.h"
#include "../c-skeleton/headers/assign_vector_to_centro.h"
#include "../c-skeleton/headers/update_centroids.h"




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
    uint64_t npoints;
    uint32_t dimension; 
    //npoints =5;
    //dimension= 2;
    //uint8_t quiet = program_arguments.quiet;
    uint32_t k = program_arguments.k;
    squared_distance_func_t DISTANCE_SQUARED;
    point_t** donnes;
    


    if (program_arguments.squared_distance_func == squared_manhattan_distance) {
        DISTANCE_SQUARED = squared_manhattan_distance;
    } else {
        DISTANCE_SQUARED = squared_euclidean_distance;
    }
    fprintf(stderr, "%d\n",0);
    donnes =  point_input(input_file, &dimension, &npoints); 
    
    printf("%d\n", 1);
    if(p>npoints)
    {
        fprintf(stderr, "Not enough points to generate the combinations\n");
        return -1;

    }

    printf("%d\n", 2);
    int64_t nombre_comb = combinaison(p,k);
    printf(" nombre_comb =  %ld\n", nombre_comb);
    printf("%d\n", 3);
    point_t ***initial_combinations = generate_combinations(donnes,npoints,k,p);
    printf("%d\n", 4);

    point_t **initial_centroids = (point_t **)malloc(nombre_comb* sizeof(point_t *));
    for (int i = 0; i < nombre_comb; i++) {
    // Utilisation de calloc pour initialiser chaque élément à NULL
        initial_centroids[i] = (point_t *)calloc(k, sizeof(point_t));
        if (initial_centroids[i] == NULL) {
            // Gestion d'erreur si l'allocation échoue
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < k; j++) {
            //initial_centroids[i][j].dim = dimension; // Exemple de dimension
            initial_centroids[i][j].coords = (int64_t *)calloc(dimension , sizeof(int64_t)); // Exemple d'allocation pour coords
            if (initial_centroids[i][j].coords == NULL) {
                // Gestion d'erreur si l'allocation échoue
                exit(EXIT_FAILURE);
            }
            //initial_centroids[i][j].nbr_vector = npoints; // Exemple de valeur pour nbr_vector
                
        }
        printf("k = %d\n", k);
        
    }
    
    for (int i = 0; i < nombre_comb; i++) {
        for (int j = 0; j < k; j++) {
            // Copier la dimension
            initial_centroids[i][j].dim = initial_combinations[i][j][0].dim;
            printf("%d\n", 0);
            // Copier les coordonnées
            initial_centroids[i][j].coords = (int64_t *)malloc(dimension * sizeof(int64_t));

            if (initial_centroids[i][j].coords == NULL) {
                // Gestion d'erreur si l'allocation échoue
                exit(EXIT_FAILURE);
            }
            printf("initial_combinations[i][j][0].coords[0]=%ld\n",initial_combinations[i][j][0].coords[0]);
            printf("%d\n", 0);
            memcpy(initial_centroids[i][j].coords, initial_combinations[i][j][0].coords, dimension * sizeof(int64_t));
            printf("%d\n", 1);
            // Copier le nombre de vecteurs
            initial_centroids[i][j].nbr_vector = initial_combinations[i][j][0].nbr_vector;
            printf("%d\n", 2);
        }
    }
    printf("%d\n", 0);
    printf("initial_centroids[0][1].coords[0]=%ld\n",initial_centroids[0][1].coords[0]);
    printf("initial_combinations[0][1].coords[0]=%ld\n",initial_combinations[0][1]->coords[0]);
    
    //}
    point_t** final_centroids = calloc(nombre_comb, sizeof(point_t*));
    for(int64_t i = 0; i<nombre_comb; i++){
        final_centroids[i] = malloc(k*sizeof(point_t));
        final_centroids[i]->coords =  malloc(dimension * sizeof(int64_t)); 
    }
    uint64_t distortion_list[nombre_comb]; 
    uint64_t solDistortion = UINT64_MAX;

    cluster_t*** clusters_list = calloc(nombre_comb, sizeof(cluster_t**)); 
    for (int64_t i = 0; i < nombre_comb; i++){
        clusters_list[i] = malloc(k * sizeof(cluster_t*));
        for (int64_t j = 0; j < k; j++) {
            clusters_list[i][j] = malloc(sizeof(cluster_t)); 
            clusters_list[i][j] = NULL; // Initialisation à NULL
        }
    }

    cluster_t** temps_cluster= calloc(nombre_comb, sizeof(cluster_t*));
     
    for (int i = 0; i < nombre_comb; i++) {
        uint64_t s = donnes[i]->nbr_vector;
        temps_cluster[i] = malloc(k*sizeof(cluster_t));
        if (temps_cluster[i] == NULL) {
            perror("Erreur d'allocation mémoire pour temps_cluster");
            // Gérer l'erreur et sortir de la fonction si nécessaire
            exit(EXIT_FAILURE);
        }
        //temps_cluster[i]->centroide.coords = malloc(sizeof(int64_t*));
        for (int j = 0; j < k; j++) {
            temps_cluster[i][j].centroide.coords = (int64_t *)malloc(dimension * sizeof(int64_t));
            temps_cluster[i][j].data = malloc(s*sizeof(point_t*));
            temps_cluster[i][j].size = s;//temps_cluster[i]->data[0]->nbr_vector;
            //for (int j = 0; j < s; j++) {

             // Copiez les pointeurs de données appropriés ici
        }
    } 
    /*for(int64_t i = 0; i < k; i++){
        temps_cluster[i] = malloc(sizeof(cluster_t)); 
    }*/

    point_t* solCentroide = calloc(k, sizeof(point_t)); 
    point_t* temp_centroide = calloc(k, sizeof(point_t)); 

    cluster_t** temps_result_cluster= calloc(k, sizeof(cluster_t*)); 
    for(int64_t i = 0; i < k; i++){
        temps_result_cluster[i] = malloc(sizeof(cluster_t)); 
    }

    cluster_t** solCluster = calloc(k, sizeof(cluster_t*)); 
    for(int64_t i = 0; i < k; i++){
        solCluster[i] = malloc(sizeof(cluster_t)); 
    }


    printf("%d\n", 5);

    // Copie de initial_combinations dans initial_centroids
    /*for (int i = 0; i < nombre_comb; i++) {
        memcpy(initial_centroids[i], initial_combinations[0][i], sizeof(point_t));  //sizeof(point_t*)
        for (int j = 0; i < k; i++) {
            printf("%d\n", 0);
            memcpy(initial_centroids[i][j].coords, initial_combinations[0][i][j].coords, sizeof(int64_t));
            // Copier d'autres membres de initial_combinations[0][i][j] si nécessaire
            //initial_centroids[i][j].dim = initial_combinations[0][i][j].dim;
            //memcpy(&initial_centroids[i][j], &initial_combinations[0][i][j], sizeof(const point_t));  //sizeof(point_t*)
        }
    }*/
    /*for (int i = 0; i < nombre_comb; i++) {
        for (int j=0;j <k;j++){
            initial_centroids[i][j] = initial_combinations[0][i][j];
        }
    }*/
     
    printf("%d\n", 6);
    printf("initial_centroids[0]->coords[0]= %ld\n", initial_centroids[0]->coords[0]);
    //printf(" initial_centroids[0][1].coords[0] = %ld\n",initial_centroids[0][1].coords[0]);
    if (&initial_centroids[0][0] == NULL) {
        printf(" &initial_centroids[0] == NULL %d\n", 0);
    }
    /*for (int i = 0; i < k; i++) {
        temps_cluster[i] = malloc(sizeof(cluster_t));
        if (temps_cluster[i] == NULL) {
            perror("Erreur d'allocation mémoire pour temps_cluster");
            // Gérer l'erreur et sortir de la fonction si nécessaire
            exit(EXIT_FAILURE);
        }
    }*/
    //a comparer avec la fichier fin du main 

    for (uint64_t i = 0; i < nombre_comb; i++) {
        //uint64_t temp_distorsion;
        for(uint32_t j = 0; j<k; j++){

            uint64_t temp_distorsion = 0; 
            printf("%d\n", 7);
            printf("i : %ld , j : %d\n", i,j);


            temps_cluster[i][j].centroide = initial_centroids[i][j]; //0
            printf("%d\n", 8);
            printf("temps_cluster[j]->centroide.coords[0]= %ld\n", temps_cluster[j]->centroide.coords[0]);
            temps_cluster[i][j].data = donnes;
            //temps_cluster[j]->size = npoints;//donnes[i]->nbr_vector;//initial_centroids[0]->nbr_vector;
            //temps_cluster[j]->data = malloc(npoints * sizeof(point_t*));//;npoints
            printf("%d\n", 8);


            /*if (temps_cluster[j]->data == NULL) {
                perror("Erreur d'allocation mémoire pour temps_cluster[0]->data");
                break; 
            }
            temps_cluster[j]->data = donnes; */
            printf("temps_cluster[i][0].data[0][0].coords[0] = %ld\n", temps_cluster[i][0].data[0][0].coords[0]);
        
            printf("%d\n", 9);
            temps_result_cluster = k_means(temps_cluster, npoints, k, initial_centroids[i], initial_centroids[i], DISTANCE_SQUARED);
            printf("%d\n", 10);
            /*for (uint32_t m ; m<k; m++){
                initial_centroids[i][m] = temps_cluster[m]->centroide;
                //clusters_list[i][m] =  temps_cluster[m];
            }
            printf("%d\n", 11);*/
            temp_distorsion = distortion((cluster_t const **)temps_result_cluster, k, DISTANCE_SQUARED); //distortion((cluster_t const **)clusters_list[i], k, DISTANCE_SQUARED);
            printf(" temp_distorsion %ld\n", temp_distorsion);
            if (solDistortion > temp_distorsion){
                solDistortion = temp_distorsion; 
                solCentroide = temp_centroide; 
                solCluster = temps_result_cluster;
            }
            final_centroids[i] = solCentroide; 
            clusters_list[i] = solCluster; 
            distortion_list[i] = solDistortion; 
        
        }
    
    }

     // Libération de la mémoire allouée pour initial_centroids
    for(int64_t i = 0; i < nombre_comb; i++) {
        free(initial_centroids[i]->coords);
        free(initial_centroids[i]);
    }
    free(initial_centroids);

    // Libération de la mémoire allouée pour final_centroids
    for(int64_t i = 0; i < nombre_comb; i++) {
        free(final_centroids[i]);
    }
    free(final_centroids);

    // Libération de la mémoire allouée pour clusters_list
    for(int64_t i = 0; i < nombre_comb; i++) {
        for(int64_t j = 0; j < k; j++) {
            free(clusters_list[i][j]);
        }
        free(clusters_list[i]);
    }
    free(clusters_list);

    // Libération de la mémoire allouée pour temps_cluster
    for(int64_t i = 0; i < k; i++) {
        free(temps_cluster[i]->data);
        free(temps_cluster[i]);
    }
    free(temps_cluster);

    // Libération de la mémoire allouée pour temps_result_cluster
    for(int64_t i = 0; i < nombre_comb; i++) {
        free(temps_result_cluster[i]);
    }
    free(temps_result_cluster);

    // Libération de la mémoire allouée pour solCluster
    for(int64_t i = 0; i < k; i++) {
        free(solCluster[i]);
    }
    free(solCluster);

    // Libération de la mémoire allouée pour solCentroide
    free(solCentroide);

    // Libération de la mémoire allouée pour temp_centroide
    free(temp_centroide);



    //print csv
    printf("%d\n", 10);
    write_csv(output_file, distortion_list,initial_centroids, final_centroids, clusters_list, k, dimension, nombre_comb); 
    printf("%d\n", 11);



    // close the files opened by parse_args
    if (program_arguments.input_stream != stdin) {
        fclose(program_arguments.input_stream);
    }
    if (program_arguments.output_stream != stdout) {
        fclose(program_arguments.output_stream);
    }
    return 0;
}
