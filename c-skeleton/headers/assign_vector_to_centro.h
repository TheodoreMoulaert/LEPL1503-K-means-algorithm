#ifndef ASSIGN_VECTOR_TO_H
#define ASSIGN_VECTOR_TO_H
#include "../headers/point.h" // Inclure si nécessaire
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/main.h"

#define MAX_DIMENSION 1000
#include <stdint.h>
#include <stdio.h> 

bool assign_vectors_to_centroids(cluster_t clusters[], cluster_t centroids[], uint64_t K, squared_distance_func_t distance_type);


#endif 