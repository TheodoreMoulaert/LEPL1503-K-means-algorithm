#include <stdlib.h> // Pour llabs()

#include "../headers/distance.h"
#include "../headers/point.h" // Inclure si nécessaire
#include "../headers/main.h"


uint64_t distortion(cluster_t *centroids, cluster_t **clusters, uint32_t num_clusters, squared_distance_func_t DISTANCE_SQUARED) {
        uint64_t current_sum = 0;
        for (uint32_t k = 0; k < num_clusters; ++k) {
            for (uint64_t j = 0; j < clusters[k]->size; ++j) {
                current_sum += DISTANCE_SQUARED(clusters[k]->data[j], centroids[k].center);
            }
        }
        return current_sum;
}

