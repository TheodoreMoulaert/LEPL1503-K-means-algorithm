#ifndef CLUSTER_H
#define CLUSTER_H
#include <stdint.h>
#include "../headers/point.h" 

typedef struct {
    //point_t center;
    point_t *data;
    uint64_t size;

} cluster_t ;

#endif //CLUSTER_H