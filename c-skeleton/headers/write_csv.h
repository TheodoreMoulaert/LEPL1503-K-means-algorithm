#ifndef WRITE_CSV_H
#define WRITE_CSV_H
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h> 

#include "../headers/point.h"
#include "../headers/cluster.h"

int8_t create_CSV(cluster_t *clusters, cluster_t centroid_init, uint64_t distortion, uint32_t *clusterParPoint, uint32_t k);

void fprintArrayClusters(FILE *fp, cluster_t *cluster); 

void fprintCoordPoint(FILE *fp, point_t pt);

void fprintArrayPoints(FILE *fp, int64_t* arrayPts, uint64_t nb); 

#endif 
