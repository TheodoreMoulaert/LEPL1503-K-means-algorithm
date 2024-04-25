#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <stddef.h>
#include <stdio.h>

#ifndef KMEANS_THREAD_ARGS_H
#define KMEANS_THREAD_ARGS_H

typedef struct{
    //bool changes; 
    //cluster_t** result_cluster; 
    uint64_t temp_distorsion;
    cluster_t** temps_result_cluster;
    point_t *initial_centroids;
    point_t *final_centroids;
    point_t **initial_conserve;

} result_thread;

// Structure pour passer les arguments à la fonction k_means_thread
typedef struct {
    cluster_t **clusters;
    uint64_t num_points;
    uint32_t k;
    uint32_t dimension;
    int64_t nombre_comb;
    point_t **initial_centroids;
    point_t **final_centroids;
    point_t **initial_conserve;
    squared_distance_func_t distance_func;
    FILE *output_file;

    uint32_t n_thread;
    pthread_mutex_t *mutex;
    result_thread res_thread;

} k_means_thread_args_t;


#endif //KMEANS_THREAD_ARGS_H