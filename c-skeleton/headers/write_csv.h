#ifndef WRITE_CSV_H
#define WRITE_CSV_H
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h> 

#include "../headers/point.h"
#include "../headers/cluster.h"

void write_csv(FILE *output_file, int64_t distortion, point_t **centroidsArray, cluster_t **clustersArray, int64_t k, int64_t dimension); 
#endif 
