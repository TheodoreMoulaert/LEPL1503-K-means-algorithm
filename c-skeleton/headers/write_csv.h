#ifndef WRITE_CSV_H
#define WRITE_CSV_H
#include <stdint.h>
#include <stdio.h>
#include <inttypes.h> // Ajout de l'en-tête inttypes.h

#include "../headers/point.h"
#include "../headers/cluster.h"

int8_t create_CSV(point_t* inits, cluster_t *clusters, uint64_t distortion, uint32_t *clusterParPoint, uint32_t k);

void fprintArrayClusters(FILE *fp, cluster_t *cluster); 

void fprintCoordPoint(FILE *fp, point_t pt);

void fprintArrayPoints(FILE *fp, point_t* arrayPts, uint64_t nb);

#endif 
