#ifndef ASSIGN_VECTORS_TO_CENTROIDS_H
#define ASSIGN_VECTORS_TO_CENTROIDS_H

#include "cluster.h" // Include cluster_t definition
#include "distance.h" // Include if necessary
#include <stdbool.h>


// Function prototype
bool assign_vectors_to_centroids(cluster_t clusters[], int centroids[][MAX_DIMENSION], int dimension, int K, DistanceType distance_type);

#endif /* ASSIGN_VECTORS_TO_CENTROIDS_H */
