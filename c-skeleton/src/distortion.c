#include <stdlib.h> // Pour llabs()

#include "../headers/distance.h"
#include "../headers/point.h" // Inclure si nécessaire
#include "../headers/main.h"
#include "../headers/cluster.h"

uint64_t distortion(cluster_t const **clusters, uint32_t k, squared_distance_func_t func) {
    uint64_t sum_totale = 0;
    
    for(uint32_t i = 0; i < k; i++) {
        uint64_t sum = 0;

        for (uint64_t j = 0; j < clusters[i]->size; j++) {
            sum += func(&clusters[i]->center, &clusters[i]->data[j]);
        }

        sum_totale += sum;
    }
    
    return sum_totale; 
}
