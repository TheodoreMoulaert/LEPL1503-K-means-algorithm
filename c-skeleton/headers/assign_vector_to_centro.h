#ifndef ASSIGN_VECTORS_TO_CENTROIDS_H
#define ASSIGN_VECTORS_TO_CENTROIDS_H

#include "cluster.h"
#include "point.h"

int assign_vector_to_centroids(cluster_t* centroids, cluster_t* clusters, uint32_t K);

#endif /* ASSIGN_VECTORS_TO_CENTROIDS_H */
