#include "../headers/assign_vector_to_centro.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "../headers/distance.h"

uint64_t assign_vector_to_centroids(cluster_t *centroids, cluster_t *clusters, uint32_t K, squared_distance_func_t distance_type) {
    uint64_t unchanged = 1; // Flag to indicate if the assignment remains unchanged

    // Allocate memory for centroids and clusters
    for (uint32_t i = 0; i < K; i++) {
        centroids[i].data = (point_t *)malloc(sizeof(point_t) * centroids[i].size);
        clusters[i].data = (point_t *)malloc(sizeof(point_t) * clusters[i].size);
        if (centroids[i].data == NULL || clusters[i].data == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            // Free memory allocated so far
            for (uint32_t j = 0; j < i; j++) {
                free(centroids[j].data);
                free(clusters[j].data);
            }
            return -1;
        }
    }

    // Iterate over clusters to assign vectors to centroids
    for (uint32_t current_centroid_idx = 0; current_centroid_idx < K; current_centroid_idx++) {
        for (uint32_t i = 0; i < clusters[current_centroid_idx].size; i++) {
            // Find the closest centroid for the vector
            int closest_centroid_idx = -1;
            int64_t closest_centroid_distance = INT64_MAX;

            for (uint32_t centroid_idx = 0; centroid_idx < K; centroid_idx++) {
                int64_t distance = distance_type(&clusters[current_centroid_idx].data[i], &centroids[centroid_idx].center);

                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }

            // Add the vector to the cluster of the closest centroid
            if (closest_centroid_idx != current_centroid_idx) {
                unchanged = 0; // Assignment changed
            }

            // Add the vector to the cluster of the closest centroid
            clusters[closest_centroid_idx].data[clusters[closest_centroid_idx].size] = clusters[current_centroid_idx].data[i];
            clusters[closest_centroid_idx].size++;

            // Remove the vector from the current centroid's cluster
            clusters[current_centroid_idx].size--;
            clusters[current_centroid_idx].data[i] = clusters[current_centroid_idx].data[clusters[current_centroid_idx].size];
            i--; // Adjust the index as we removed an element
        }
    }

    return unchanged;
}
