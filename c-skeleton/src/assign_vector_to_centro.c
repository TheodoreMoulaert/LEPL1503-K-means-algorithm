#include "../headers/assign_vector_to_centro.h"
#include <stddef.h>
#include "../headers/distance.h"
#include <stdlib.h>
#include <stdio.h>

uint64_t assign_vector_to_centroids(cluster_t *centroids, cluster_t *clusters, uint32_t K, squared_distance_func_t distance_type) {
    uint64_t unchanged = 1; // Flag to indicate if the assignment remains unchanged

    // Allocate memory for centroids and clusters
    for (uint32_t i = 0; i < K; i++) {
        centroids[i].data = (point_t *)malloc(sizeof(point_t) * centroids[i].size);
        clusters[i].data = (point_t *)malloc(sizeof(point_t) * clusters[i].size);
        if (centroids[i].data == NULL || clusters[i].data == NULL) {
            // Handle memory allocation failure
            fprintf(stderr, "Memory allocation failed\n");
            return -1;
        }
    }

    // Iterate over clusters to assign vectors to centroids
    for (uint32_t current_centroid_idx = 0; current_centroid_idx < K; current_centroid_idx++) {
        // Loop through each vector in the current centroid's cluster
        for (uint32_t i = 0; i < clusters[current_centroid_idx].size; i++) { // Removed i++ from loop declaration
            // Find the closest centroid for the vector
            int64_t closest_centroid_idx = -1;
            int64_t closest_centroid_distance = INT64_MAX;
            printf("%d\n", 2);

            for (uint32_t centroid_idx = 0; centroid_idx < K; centroid_idx++) {
                int64_t distance = distance_type(&clusters[current_centroid_idx].data[i], &centroids[centroid_idx].data[0]);
                printf("%d\n", 3);

                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }

            // Add the vector to the cluster of the closest centroid
            if (closest_centroid_idx != current_centroid_idx) {
                unchanged = 0; // Assignment changed
            }

            // Add the vector to the cluster without reallocating memory
            clusters[closest_centroid_idx].data[clusters[closest_centroid_idx].size] = clusters[current_centroid_idx].data[i];
            clusters[closest_centroid_idx].size++;

            // Remove the vector from the current centroid's cluster
            // Move the last element to the current position
            clusters[current_centroid_idx].data[i] = clusters[current_centroid_idx].data[clusters[current_centroid_idx].size - 1];
            clusters[current_centroid_idx].size--;

            // Don't increment i here; it will be incremented by the loop
        }
    }


    return unchanged;
}
