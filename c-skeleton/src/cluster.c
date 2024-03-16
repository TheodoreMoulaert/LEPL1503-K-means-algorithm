#ifndef CLUSTER_H
#define CLUSTER_H

#include "point.c" 

typedef struct {
    point_t center;
    uint64_t surrounding;
    point_t *data;

} cluster_t ;

#endif //CLUSTER_H