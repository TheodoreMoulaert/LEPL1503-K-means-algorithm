
#include "../headers/distance.h"
#include "point.h"
#include <stdlib.h> // Pour llabs()

int64_t dimension; 


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
    
    int64_t result; 
    if(dimension == 2 ){
        int64_t dx = p2->x - p1->x; 
        int64_t dy = p2->y - p1->y; 
        int64_t val = llabs(dx)+llabs(dy);
        result = val*val; 
    }else if( dimension == 3){
        int64_t dx = p2->x - p1->x; 
        int64_t dy = p2->y - p1->y; 
        int64_t dz = p2->z - p1->z; 
        int64_t val = llabs(dx)+llabs(dy) + llabs(dz);
        result = val*val; 

    }
    // TODO
    return result;
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
    if(dimension == 2){
        int64_t dx = p1->x - p2->x; 
        int64_t dy = p1->y - p2->y; 
        int64_t carre_x = dx*dx; 
        int64_t carre_y = dy*dy; 
        result = carre_x + carre_y;

    }
    else if(dimension == 3){
        int64_t dx = p1->x - p2->x; 
        int64_t dy = p1->y - p2->y; 
        int64_t dz = p1->z - p2->z; 
        int64_t carre_x = dx*dx; 
        int64_t carre_y = dy*dy; 
        int64_t carre_z = dz*dz; 
        result = carre_x + carre_y+ carre_z;

    }
    // TODO
    return result;
}

