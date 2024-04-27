
#ifndef CLUSTER_H
#define CLUSTER_H
#include <stdbool.h>
#include "../headers/cluster.h"
#include "point.h"

/*
Structure qui permet de définir les clusters
*/ 
typedef struct {
    point_t centroide;
    point_t **data;
    uint64_t size; 
} cluster_t;

typedef struct { 
    bool changes; 
    cluster_t** result_cluster; 
} result_t;



#endif //CLUSTER_H

