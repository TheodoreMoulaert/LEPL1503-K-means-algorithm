
#ifndef CLUSTER_H
#define CLUSTER_H

#include "point.h"

/*
Structure qui  permet de définir les clusters et les centroïds tel que 
cluster est défini par cluster_t** et centroids est défini par cluster_t* 
*/ 
typedef struct {
    point_t center;
    point_t *data; // [[0,0],[0,0],[1,1]] == liste de vecteurs
    uint64_t size; // nbr de vecteur 
} cluster_t;

#endif //CLUSTER_H

