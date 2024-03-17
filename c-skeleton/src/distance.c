
#include "../headers/distance.h"
#include "../headers/point.h" // Inclure si nécessaire
#include <stdlib.h> // Pour llabs()


int64_t squared_manhattan_distance(const point_t *p1, const point_t *p2) {
    /*
    Calcule la distance de Manhattan au carré entre deux points 

    Arguments
    ----------
    *p1 : pointeur vers le premier point p1
    *p2 : pointeur vers le deuxième point p2
    Retour
    -------
    result : la distance de Manhattan au carré entre les deux points
    */
    
    int64_t result = 0; 
    uint32_t dim = p1->dim; 
    for(uint32_t i = 0; i < dim; i++){
        result += llabs(p2->coords[i] - p1->coords[i]); 
    }
    return result * result;
}


int64_t squared_euclidean_distance(const point_t *p1, const point_t *p2) {
    /*
    Calcule la distance euclidienne au carré entre deux points 

    Arguments
    ----------
    *p1 : pointeur vers le premier point p1
    *p2 : pointeur vers le deuxième point p2
    Retour
    -------
    result : la distance euclidienne au carré entre les deux points
    */

    int64_t result; 
    uint32_t dim = p1->dim; 

    for (uint32_t i = 0; i< dim; i++){
        int64_t diff = p1->coords[i]- p2->coords[i]; 
        result += diff*diff;
    }
    return result;
}

