#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include <stdbool.h>
#include <pthread.h>

#ifndef KMEANS_THREAD_ARGS_H
#define KMEANS_THREAD_ARGS_H

// Structure pour passer les arguments à la fonction k_means_thread
typedef struct {
    cluster_t **clusters;
    cluster_t **result;
    uint64_t num_points;
    uint32_t k;
    point_t *initial_centroids;
    point_t *final_centroids;
    squared_distance_func_t distance_func;
    pthread_mutex_t *mutex;
} k_means_thread_args_t;

typedef{
    bool changes; 
    cluster_t** result_cluster; 
    uint64_t temp_distorsion;
    (cluster_t const **)temps_result_cluster;
    point_t *initial_centroids;
    point_t *final_centroids;

} result_thread;

#endif //KMEANS_THREAD_ARGS_H
