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
    /*int parse_result = parse_binary_input(program_arguments.input_stream, &points, &num_points, &dim);
    if (parse_result != 0) {
        printf("Error parsing binary input.\n");
        fclose(program_arguments.input_stream);
        return 1;
    }*/
    // est ce qu'on n'utiliserait pas la fonction de binary_file_reader --> point_input

    point_t *centroids = k_means(points, program_arguments.k, num_points, dim, DISTANCE_SQUARED);
    if (centroids == NULL) {
        printf("Error running k-means algorithm.\n");
        fclose(program_arguments.input_stream);
        return 1;
    }

    uint64_t distortion = distortion(&centroids,num_points, DISTANCE_SQUARED);
    if (distortion == 0) {
        printf("Error computing distortion.\n");
        fclose(program_arguments.input_stream);
        return 1;
    }

    int write_result = write_csv(centroids, distortion, program_arguments.output_stream, points, num_points, program_arguments.k, dim);
    if (write_result != 0) {
        printf("Error writing results to CSV.\n");
        fclose(program_arguments.input_stream);
        return 1;
    }

    free(points);
    free(centroids);
    fclose(program_arguments.input_stream);
    if (program_arguments.output_stream != stdout) {
        fclose(program_arguments.output_stream);
    }

    return 0;
}