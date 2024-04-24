#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"
#include "../headers/cluster.h"



bool assign_points_to_clusters(point_t **points, cluster_t **clusters, uint64_t num_points, uint32_t num_clusters, int *point_cluster_indices, squared_distance_func_t distance_func) {
    bool changed = false;

    for (uint64_t i = 0; i < num_points; i++) {
        int64_t min_distance = distance_func(points[i], &clusters[0]->centroide);
        uint32_t min_cluster_index = 0;

        for (uint32_t k = 1; k < num_clusters; k++) {
            int64_t current_distance = distance_func(points[i], &clusters[k]->centroide);
            if (current_distance < min_distance) {
                min_distance = current_distance;
                min_cluster_index = k;
            }
        }

        if (point_cluster_indices[i] != min_cluster_index) {
            changed = true;
            point_cluster_indices[i] = min_cluster_index;
        }
    }

    return changed;
}
