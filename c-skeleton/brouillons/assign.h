#ifndef ASSIGN__H
#define ASSIGN__H

//#include "../headers/assign_vector_to_centro.h"
#include <stddef.h>
#include "../headers/distance.h"
#include "../headers/cluster.h"
#include <stdlib.h>
#include <stdio.h>

result_t assign_vectors_to_centroides(point_t *centroids, cluster_t **clusters, uint32_t K, squared_distance_func_t distance_func) ; 


#endif /* ASSIGN__H */
