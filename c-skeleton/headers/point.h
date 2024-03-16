
#ifndef POINT_H
#define POINT_H

#include <stdint.h>

typedef struct {
    uint32_t dim; 
    int64_t* coords; 
   
} point_t;

#endif //POINT_H
