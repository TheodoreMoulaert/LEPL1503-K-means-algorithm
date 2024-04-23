#ifndef K_MEANS_H
#define K_MEANS_H

#include <stdbool.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"

cluster_t** k_means(cluster_t**clusters_input, uint64_t num_points, uint32_t k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func) ; 

// Prototype de la fonction k_means_thread
void *k_means_thread(void *args);

#endif  // K_MEANS_H