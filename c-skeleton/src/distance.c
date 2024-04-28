
#include "../headers/distance.h"
#include "../headers/point.h"
#include "../headers/cluster.h"
#include <stdlib.h>



/**
 * Calcule la distance de Manhattan au carré entre deux points.
 * 
 * @param p1 Pointeur vers le premier point.
 * @param p2 Pointeur vers le deuxième point.
 * @return La distance de Manhattan au carré entre les deux points.
 */

int64_t squared_manhattan_distance(const point_t *p1, const point_t *p2) {
    
    int64_t result = 0; 
    uint32_t dim = p1->dim; 
    for(uint32_t i = 0; i < dim; i++){
        result += llabs(p2->coords[i] - p1->coords[i]); 
    }
    return result * result;
}

/**
 * Calcule la distance euclidienne au carré entre deux points.
 * 
 * @param p1 Pointeur vers le premier point.
 * @param p2 Pointeur vers le deuxième point.
 * @return La distance euclidienne au carré entre les deux points.
 */

int64_t squared_euclidean_distance(const point_t *p1, const point_t *p2) {

    int64_t result = 0; 
    uint32_t dim = p1->dim; 

    for (uint32_t i = 0; i< dim; i++){
        int64_t diff = p1->coords[i]- p2->coords[i]; 
        result += diff*diff;
    }
    return result;
}

/**
 * Calcule la distorsion totale d'un ensemble de clusters.
 * 
 * @param clusters Un tableau de pointeurs vers les clusters.
 * @param num_clusters Le nombre total de clusters.
 * @param DISTANCE_SQUARED La fonction de calcul de la distance au carré.
 * @return La distorsion totale des clusters.
 */

uint64_t distortion(cluster_t const **clusters, uint32_t num_clusters, squared_distance_func_t DISTANCE_SQUARED) {
    uint64_t result = 0;

    for(uint32_t i = 0; i < num_clusters; i++) {
        uint64_t current_sum = 0;

        for (uint64_t j = 0; j < clusters[i]->size; j++) {
            current_sum += DISTANCE_SQUARED(&clusters[i]->centroide, clusters[i]->data[j]);
        }

        result += current_sum;
    }

    return result;
}
