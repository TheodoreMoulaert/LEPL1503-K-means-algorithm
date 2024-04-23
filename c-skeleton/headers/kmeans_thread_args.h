#include "point.h"
#include "cluster.h"
#include "distance.h"
#include <stdbool.h>

#ifndef KMEANS_THREAD_ARGS_H
#define KMEANS_THREAD_ARGS_H

// Structure pour passer les arguments à la fonction k_means_thread
typedef struct {
    cluster_t **clusters;
    uint64_t num_points;
    uint32_t k;
    point_t *initial_centroids;
    point_t *final_centroids;
    squared_distance_func_t distance_func;
    pthread_mutex_t *mutex;
} k_means_thread_args_t;

#endif //KMEANS_THREAD_ARGS_H
