#ifndef K_MEANS_H
#define K_MEANS_H

#include <stdbool.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"

void k_means(cluster_t**clusters_input, int num_points, int k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func) ; 

#endif  // K_MEANS_H