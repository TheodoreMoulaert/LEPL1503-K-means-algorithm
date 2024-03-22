#include "../headers/assign_vector_to_centro.h"
#include <stddef.h>
#include "../headers/distance.h"
#include <stdlib.h>



int assign_vector_to_centroids(cluster_t* centroids, cluster_t* clusters, uint32_t K, squared_distance_func_t distance_type) {
    int unchanged = 1; // Flag to indicate if the assignment remains unchanged

    for (uint32_t current_centroid_idx = 0; current_centroid_idx < K; current_centroid_idx++) {
        for (uint32_t i = 0; i < clusters[current_centroid_idx].size; i++) {
            // Find the closest centroid for the vector
            int closest_centroid_idx = -1;
            int64_t closest_centroid_distance = INT64_MAX;

            for (uint32_t centroid_idx = 0; centroid_idx < K; centroid_idx++) {
                int64_t distance = distance_type(&clusters[current_centroid_idx].data[i], &centroids[centroid_idx].data[0]);

                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }

            // Add the vector to the cluster of the closest centroid
            if (closest_centroid_idx != current_centroid_idx) {
                unchanged = 0; // Assignment changed
            }

            point_t* new_point = realloc(clusters[closest_centroid_idx].data, (clusters[closest_centroid_idx].size + 1) * sizeof(point_t));
            if (new_point == NULL) {
                // Handle memory allocation failure
                return -1;
            }
            clusters[closest_centroid_idx].data = new_point;

            clusters[closest_centroid_idx].data[clusters[closest_centroid_idx].size] = clusters[current_centroid_idx].data[i];
            clusters[closest_centroid_idx].size++;

            // Remove the vector from the current centroid's cluster
            for (uint32_t j = i; j < clusters[current_centroid_idx].size - 1; j++) {
                clusters[current_centroid_idx].data[j] = clusters[current_centroid_idx].data[j + 1];
            }
            clusters[current_centroid_idx].size--;
            i--; // Adjust the index as we removed an element
        }
    }

    return unchanged;
}
