#ifndef ASSIGN_VECTOR_TO_H
#define ASSIGN_VECTOR_TO_H

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/main.h"

#include <stdint.h>
#include <stdbool.h>

bool assign_vectors_to_centroids(cluster_t clusters[], cluster_t centroids[], uint64_t K, squared_distance_func_t distance_type);

#endif
