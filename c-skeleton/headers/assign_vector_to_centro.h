#ifndef ASSIGN_VECTORS_TO_CENTROIDS_H
#define ASSIGN_VECTORS_TO_CENTROIDS_H

#include "cluster.h"
#include "point.h"
#include "distance.h" 

uint64_t assign_vector_to_centroids(cluster_t* centroids, cluster_t* clusters, uint32_t K, squared_distance_func_t distance_func);

#endif /* ASSIGN_VECTORS_TO_CENTROIDS_H */
