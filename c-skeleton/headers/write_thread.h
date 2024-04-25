#ifndef WRITE_THREAD_H
#define WRITE_THREAD_H
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> 
#include "../headers/point.h"
#include "../headers/cluster.h"
//#include "../headers/write_csv.h"
#include "../headers/update_centroids.h" 
#include "../headers/kmeans_thread_args.h"

void write_centro_thread(FILE *file, point_t *centroid, int64_t k, int64_t dimension);

void write_clu_thread(FILE *file, cluster_t **cluster, int64_t k, int64_t dimension);

void write_thread(FILE *output_file, uint64_t distortion, point_t *centroid_init, point_t *centroid_final, cluster_t **clusters, int64_t k, int64_t dimension, int64_t nombre_comb);

#endif //WRITE_THREAD_H
