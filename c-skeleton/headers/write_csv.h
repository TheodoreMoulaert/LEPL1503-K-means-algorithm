#ifndef WRITE_CSV_H
#define WRITE_CSV_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> 
#include "../headers/point.h"
#include "../headers/cluster.h"

void write_centroid(FILE *file, point_t* centroid, int64_t k, int64_t dimension); 
void write_cluster(FILE *file, cluster_t **cluster, int64_t k, int64_t dimension); 
void write_csv(FILE *output_file, uint64_t* distortion, point_t **centroid_init_Array, point_t **centroid_final_Array, cluster_t ***clustersArray, int64_t k, int64_t dimension, int64_t nombre_comb, bool quiet_mode ); 
#endif //WRITE_CSV_H
