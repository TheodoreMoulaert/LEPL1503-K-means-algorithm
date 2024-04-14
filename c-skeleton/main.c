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
    printf(" donnes[0][0].coords[0] = %ld\n", donnes[0][0].coords[0]);
    printf(" donnes[6][0].coords[0] = %ld\n", donnes[6][0].coords[0]);
    printf("%d\n", 1);
    if(p>npoints)
    {
        fprintf(stderr, "Not enough points to generate the combinations\n");
        return -1;

    }

    printf("%d\n", 2);
    int64_t nombre_comb = combinaison(p,k);
    printf(" nombre_comb =  %ld\n", nombre_comb);
    printf("k = %d\n", k);
    printf("npoints = %ld\n", npoints);
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
    /*point_t** final_centroids = calloc(nombre_comb, sizeof(point_t*));
    for(int64_t i = 0; i<nombre_comb; i++){
        final_centroids[i] = malloc(k*sizeof(point_t));
        final_centroids[i]->coords =  malloc(dimension * sizeof(int64_t)); 
    }*/
    point_t **final_centroids = (point_t **)malloc(nombre_comb* sizeof(point_t *));
    for (int i = 0; i < nombre_comb; i++) {
    // Utilisation de calloc pour initialiser chaque élément à NULL
        final_centroids[i] = (point_t *)calloc(k, sizeof(point_t));
        if (final_centroids[i] == NULL) {
            // Gestion d'erreur si l'allocation échoue
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < k; j++) {
            //initial_centroids[i][j].dim = dimension; // Exemple de dimension
            final_centroids[i][j].coords = (int64_t *)calloc(dimension , sizeof(int64_t)); // Exemple d'allocation pour coords
            if (final_centroids[i][j].coords == NULL) {
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
            final_centroids[i][j].dim = initial_combinations[i][j][0].dim;
            printf("%d\n", 0);
            // Copier les coordonnées
            final_centroids[i][j].coords = (int64_t *)malloc(dimension * sizeof(int64_t));

            if (final_centroids[i][j].coords == NULL) {
                // Gestion d'erreur si l'allocation échoue
                exit(EXIT_FAILURE);
            }
            printf("initial_combinations[i][j][0].coords[0]=%ld\n",initial_combinations[i][j][0].coords[0]);
            printf("%d\n", 0);
            memcpy(final_centroids[i][j].coords, initial_combinations[i][j][0].coords, dimension * sizeof(int64_t));
            printf("%d\n", 1);
            // Copier le nombre de vecteurs
            final_centroids[i][j].nbr_vector = initial_combinations[i][j][0].nbr_vector;
            printf("%d\n", 2);
        }
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

    cluster_t **temps_cluster = (cluster_t **)malloc(k * sizeof(cluster_t *));
    if (temps_cluster == NULL) {
        // Gestion d'erreur si l'allocation échoue
        exit(EXIT_FAILURE);
    }

    // Allocation et initialisation de chaque élément de la matrice
    for (int i = 0; i < k; i++) {
        // Utilisation de calloc pour initialiser chaque élément à NULL
        temps_cluster[i] = (cluster_t *)calloc(nombre_comb, sizeof(cluster_t));
        if (temps_cluster[i] == NULL) {
            // Gestion d'erreur si l'allocation échoue
            exit(EXIT_FAILURE);
        }
        temps_cluster[i]->data = (point_t**)malloc(k * sizeof(point_t *));
        /*for (int t=0;t<k;t++){
            //uint64_t s =donnes[t]->nbr_vector;
            //temps_cluster[i]->data[t] = malloc(s*sizeof(point_t));
            printf("%d\n", 2);
            temps_cluster[i]->data[t]->dim =  dimension;
            printf("%d\n", 2);
            temps_cluster[i][0].data[t]->coords = (int64_t *)malloc(dimension * sizeof(int64_t));
            printf("%d\n", 2);
            temps_cluster[i]->data[t]->nbr_vector = k;
        }*/
        printf("%d\n", 22);
        temps_cluster[i]->centroide.coords = (int64_t *)malloc(dimension * sizeof(int64_t));
        //temps_cluster[i]->centroide.dim = initial_centroids[0][0].dim;
        //temps_cluster[i]->centroide.nbr_vector=initial_centroids[0][0].nbr_vector;
    }
    int s = 0;
    for (int i =0;i< nombre_comb;i++){
        for (int j=0;j<k;j++){
            temps_cluster[j]->centroide.dim = initial_centroids[i][j].dim;
            memcpy(temps_cluster[j]->centroide.coords, initial_centroids[i][j].coords, dimension * sizeof(int64_t));
            temps_cluster[j]->centroide.nbr_vector = initial_centroids[i][j].nbr_vector;
            for (int t=0; t<k;t++){
                temps_cluster[j]->data[t] = donnes[j+t+s];//initial_centroids[i][j];
                temps_cluster[j]->data[t]->dim= dimension;
                temps_cluster[j]->data[t]->nbr_vector= 1;
            }
            temps_cluster[j]->size = k;
            s++; 
        }
        s++;
    }
    
    printf("temps_cluster[0][0].data[0][0].coords[0] %ld\n, temps_cluster[0][0].data[0][0].coords[1]  = %ld\n", temps_cluster[0][0].data[0][0].coords[0],temps_cluster[0][0].data[0][0].coords[1]); 
    printf("temps_cluster[0][0].data[1][0].coords[0] = %ld\n temps_cluster[0][0].data[1][0].coords[0] = %ld\n", temps_cluster[0][0].data[1][0].coords[0], temps_cluster[0][0].data[1][0].coords[1]);
    printf("temps_cluster[1][0].data[0][0].coords[0] = %ld\n", temps_cluster[1][0].data[0][0].coords[0]);
    printf("temps_cluster[1][0].data[1][0].coords[0] = %ld\n", temps_cluster[1][0].data[1][0].coords[0]);
      
    point_t* solCentroide = (point_t*)malloc(k*sizeof(point_t)); 
    //for (int i=0;i<k;i++){
    solCentroide->coords = (int64_t *)calloc(dimension , sizeof(int64_t));
    solCentroide->dim = dimension; 
    //}

    point_t* temp_centroide = (point_t*) malloc(k*sizeof(point_t));
    //for (int i=0;i<k;i++){
    temp_centroide->coords = (int64_t *)calloc(dimension , sizeof(int64_t));
    temp_centroide->dim = dimension;
    //}
    
    cluster_t** temps_result_cluster= calloc(k, sizeof(cluster_t*)); 
    for(int64_t i = 0; i < k; i++){
        temps_result_cluster[i] = malloc(sizeof(cluster_t)); 
    }

    cluster_t** solCluster = calloc(k, sizeof(cluster_t*)); 
    for(int64_t i = 0; i < k; i++){
        solCluster[i] = malloc(sizeof(cluster_t)); 
    }


    printf("%d\n", 5);
     
    printf("%d\n", 6);
    printf("initial_centroids[0][0].coords[0]= %ld\n", initial_centroids[0][0].coords[0]);
    printf("initial_centroids[0][0].coords[1]= %ld\n", initial_centroids[0][0].coords[1]);
    printf("initial_centroids[0][1].coords[0] = %ld\n",initial_centroids[0][1].coords[0]);
    printf("initial_centroids[0][1].coords[1]= %ld\n", initial_centroids[0][1].coords[1]);
    

    for (uint64_t i = 0; i < nombre_comb; i++) {
        //uint64_t temp_distorsion=0;
        for(uint32_t j = 0; j<k; j++){

            uint64_t temp_distorsion = 0; 
            printf("%d\n", 7);
            printf("i : %ld , j : %d\n", i,j);

            printf("%d\n", 8);
            printf("temps_cluster[j]->centroide.coords[0]= %ld\n", temps_cluster[j]->centroide.coords[0]);
            printf("initial_centroids[i][j].coords[0]= %ld\n", initial_centroids[i][j].coords[0]);
            printf("donnes[j][0].coords[0] = %ld\n", donnes[6][0].coords[0]);
            printf("temps_cluster[i][j].data[0][0].coords[0] = %ld\n", temps_cluster[0][0].data[1][0].coords[0]);
        
            printf("%d\n", 9);
            temps_result_cluster = k_means(temps_cluster, npoints, k, initial_centroids[i], final_centroids[i], DISTANCE_SQUARED);
            printf("temps_result_cluster[0][0].data[0][0].coords[0] = %ld\n", temps_result_cluster[0][0].data[0][0].coords[0]);
            printf("temps_result_cluster[0][0].data[0][0].coords[1] = %ld\n", temps_result_cluster[0][0].data[0][0].coords[1]);
            printf("temps_result_cluster[1][0].data[0][0].coords[0] = %ld\n", temps_result_cluster[1][0].data[1][0].coords[0]);
            printf("temps_result_cluster[1][0].data[6][0].coords[1] = %ld\n", temps_result_cluster[1][0].data[1][0].coords[1]);
            printf("temps_result_cluster[1][0].centroide.coords[1]= %ld\n", temps_result_cluster[1][0].centroide.coords[1]);
            printf("%d\n", 10);
            for (uint32_t m=0 ; m<k; m++){
                temp_centroide[m].coords = temps_result_cluster[m][0].centroide.coords;
                temp_centroide[m].nbr_vector = temps_result_cluster[m][0].centroide.nbr_vector;
            }
            printf("%d\n", 11);
            temp_distorsion = distortion((cluster_t const **)temps_result_cluster, k, DISTANCE_SQUARED);//distortion((cluster_t const **)clusters_list[i], k, DISTANCE_SQUARED);//distortion((cluster_t const **)temps_result_cluster, k, DISTANCE_SQUARED);
            printf(" temp_distorsion %ld\n", temp_distorsion);
            if (solDistortion > temp_distorsion){
                printf("%d\n", 12);
                solDistortion = temp_distorsion; 
                solCentroide = temp_centroide; 
                solCluster = temps_result_cluster;
            }
            
            final_centroids[i] = solCentroide; 
            clusters_list[i] = solCluster;
            distortion_list[i] = solDistortion; 
            printf("%d\n", 13);
            
        }
    
    }
    printf("clusters_list[0][0][0].data[0][0].coords[0]= %ld\n", clusters_list[0][0][0].data[0][0].coords[0]);
    printf("clusters_list[0][0][0].data[0][0].coords[1]= %ld\n", clusters_list[0][0][0].data[0][0].coords[1]);
    printf("clusters_list[0][0][0].data[1][0].coords[0]= %ld\n", clusters_list[0][0][0].data[1][0].coords[0]);
    printf(" clusters_list[0][0][0].data[1][0].coords[1]= %ld\n", clusters_list[0][0][0].data[1][0].coords[1]);
    printf("clusters_list[0][1][0].data[0][0].coords[0]= %ld\n", clusters_list[0][1][0].data[0][0].coords[0]);
    printf("clusters_list[0][1][0].data[0][0].coords[1]= %ld\n", clusters_list[0][1][0].data[0][0].coords[1]);
    printf("clusters_list[0][1][0].data[1][0].coords[0]= %ld\n", clusters_list[0][1][0].data[1][0].coords[0]);
    printf("clusters_list[0][1][0].data[1][0].coords[1]= %ld\n", clusters_list[0][1][0].data[1][0].coords[1]);
    printf("clusters_list[0][1][0].data[6][0].nbr_vector= %ld\n", clusters_list[0][1][0].data[0]->nbr_vector);
    printf("clusters_list[0][1]->size= %ld\n", clusters_list[0][1]->size);
    printf("clusters_list[0][1][0].size= %ld\n", clusters_list[0][0][0].size);
    //print csv
    printf("%d\n", 14);
    write_csv(output_file, distortion_list,initial_centroids, final_centroids, clusters_list, k, dimension, nombre_comb); 
    printf("%d\n", 15);


    for (uint64_t i = 0; i < npoints; i++) {
        free(donnes[i]->coords);
        //free(donnes[i]->nbr_vector);
        //free(donnes[i]);
    }
    free(donnes);

    for (uint64_t i = 0; i < nombre_comb; i++) {
        /*for (uint32_t j = 0; j < k; j++) {
            free(initial_combinations[i][j]->coords);
        }*/
        for (uint32_t j = 0; j < k; j++) {
            free(initial_combinations[i][j]);
        }
        free(initial_combinations[i]);
    }
    free(initial_combinations);
     // Libération de la mémoire allouée pour initial_centroids
    for(int64_t i = 0; i < nombre_comb; i++) {
        //free(initial_centroids[i]->coords);
        free(initial_centroids[i]);
    }
    free(initial_centroids);

    
    // Libération de la mémoire allouée pour final_centroids
    for (int64_t i = 0; i < nombre_comb; i++) {
        
        //free(final_centroids[i]->coords);
        free(final_centroids[i]);
    }
    free(final_centroids);


     // Libération de la mémoire allouée pour temps_cluster
    for(int64_t i = 0; i < k; i++) {
        free(temps_cluster[i]->data);
        //free(temps_cluster[i]->centroide.coords);
        free(temps_cluster[i]);
    }
    free(temps_cluster);

    // Libération de la mémoire allouée pour solCluster
    for(int64_t i = 0; i < k; i++) {
        //free(solCluster[i]->centroide.coords);
        //free(solCluster[i]->data);
        free(solCluster[i]);
    }
    free(solCluster);
    
    //free(temp_centroide->coords);
    free(temp_centroide);

    // Libération de la mémoire allouée pour solCentroide
    //free(solCentroide->coords);
    free(solCentroide);

     // Libération de la mémoire allouée pour temps_result_cluster
    for(int64_t i = 0; i < nombre_comb; i++) {
        free(temps_result_cluster[i]->centroide.coords);
        free(temps_result_cluster[i]->data);
        free(temps_result_cluster[i]);
    }
    free(temps_result_cluster);


    // Libération de la mémoire allouée pour clusters_list
    for(int64_t i = 0; i < nombre_comb; i++) {
        for(int64_t j = 0; j < k; j++) {
            free(clusters_list[i][j]->centroide.coords);
            //free(clusters_list[i][j]->data);
            free(clusters_list[i][j]);
        }
        free(clusters_list[i]);
    }
    free(clusters_list);

    printf("%d\n", 16);



    // close the files opened by parse_args
    if (program_arguments.input_stream != stdin) {
        fclose(program_arguments.input_stream);
    }
    if (program_arguments.output_stream != stdout) {
        fclose(program_arguments.output_stream);
    }
    return 0;
}
