#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h" // Include if necessary
#include "../headers/cluster.h" // Include if necessary
#include <limits.h> // For INT_MAX
#include <stdbool.h>
#include "cluster.h"

bool assign_vectors_to_centroids(cluster_t clusters[], int centroids[][MAX_DIMENSION], int dimension, int K, squared_distance_func_t distance_type) {
    bool unchanged = true;
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < clusters[k].size; i++) {
            int closest_centroid_idx = -1;
            int closest_distance = INT_MAX;
            for (int j = 0; j < K; j++) {
                int distance;
                if (distance_type == squared_manhattan_distance) {
                    distance = squared_manhattan_distance(clusters[k].data[i], centroids[j], dimension);
                } else {
                    distance = squared_manhattan_distance(clusters[k].data[i], centroids[j], dimension);
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
            clusters[closest_centroid_idx].data[clusters[closest_centroid_idx].size++] = clusters[k].data[i];
        }
    }
    return unchanged;
}

