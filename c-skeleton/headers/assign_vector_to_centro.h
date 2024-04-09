#ifndef ASSIGN_VECTORS_TO_CENTROIDS_H
#define ASSIGN_VECTORS_TO_CENTROIDS_H

#include "../headers/assign_vector_to_centro.h"
#include <stddef.h>
#include "../headers/distance.h"
#include <stdlib.h>
#include <stdio.h>

uint64_t assign_vectors_to_centroides(point_t *centroids, cluster_t **clusters, uint32_t K, squared_distance_func_t distance_func, cluster_t **new_clusters); 



#endif /* ASSIGN_VECTORS_TO_CENTROIDS_H */
