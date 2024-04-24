
#ifndef CLUSTER_H
#define CLUSTER_H
#include <stdbool.h>
#include "../headers/cluster.h"
#include "point.h"

/*
Structure qui  permet de définir les clusters et les centroïds tel que 
cluster est défini par cluster_t** et centroids est défini par cluster_t* 
*/ 

typedef struct {
    point_t centroide;
    point_t **data; // [[0,0],[0,0],[1,1]] == liste de vecteurs
    uint64_t size; // nbr de vecteur 
} cluster_t;

typedef struct { 
    bool changes; 
    cluster_t** result_cluster; 
} result_t;



#endif //CLUSTER_H

