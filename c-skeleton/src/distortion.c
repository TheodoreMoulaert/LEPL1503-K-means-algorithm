#include <stdlib.h> // Pour llabs()

#include "../headers/distance.h"
#include "../headers/point.h" // Inclure si nécessaire
#include "../headers/main.h"
#include "../headers/cluster.h"

uint64_t distortion(cluster_t const **clusters, uint32_t num_clusters, squared_distance_func_t DISTANCE_SQUARED) {
    uint64_t result = 0;
    
    for(uint32_t i = 0; i < num_clusters; i++) {
        uint64_t current_sum = 0;

        for (uint64_t j = 0; j < clusters[i]->size; j++) {
            current_sum += DISTANCE_SQUARED(&clusters[i]->center, &clusters[i]->data[j]);
        }

        result += current_sum;
    }
    
    return result; 
}
