#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"
#include "../headers/cluster.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>

bool assign_vectors_to_centroids(cluster_t clusters[], cluster_t centroids[], int64_t dimension, uint64_t K, squared_distance_func_t distance_type) {
    bool unchanged = true;
    for (uint64_t k = 0; k < K; k++) {
        for (int64_t i = 0; i < clusters[k].size; i++) {
            int64_t closest_centroid_idx = -1;
            int64_t closest_distance = INT_MAX;
            for (uint64_t j = 0; j < K; j++) {
                int64_t distance;
                if (distance_type == squared_manhattan_distance) {
                    distance = squared_manhattan_distance(&clusters[k].data[i], &centroids[j].center);
                } else {
                    distance = squared_euclidean_distance(&clusters[k].data[i], &centroids[j].center);
                }
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest_centroid_idx = j;
                }
            }
            if (closest_centroid_idx != k) {
                unchanged = false;
            }
            // Assign the vector to the closest centroid
            centroids[closest_centroid_idx].data[centroids[closest_centroid_idx].size++] = clusters[k].data[i];
        }
    }
    return unchanged;
}

