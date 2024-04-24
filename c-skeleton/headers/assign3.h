#ifndef ASSIGN_POINTS_TO_CLUSTERS_H
#define ASSIGN_POINTS_TO_CLUSTERS_H

#include "point.h"
#include "cluster.h"
#include "distance.h"
#include <stdbool.h>
#include <stdint.h>

/**
 * Assigns each point to the cluster with the closest centroid.
 * @param points Array of pointers to points.
 * @param clusters Array of pointers to clusters.
 * @param num_points Number of points.
 * @param num_clusters Number of clusters.
 * @param point_cluster_indices Array storing the cluster index for each point.
 * @param distance_func Function pointer for calculating the distance between points.
 * @return true if any point's cluster assignment changed, false otherwise.
 */
bool assign_points_to_clusters(point_t **points, cluster_t **clusters, uint64_t num_points, uint32_t num_clusters, int *point_cluster_indices, squared_distance_func_t distance_func);

#endif /* ASSIGN_POINTS_TO_CLUSTERS_H */
