#ifndef UPDATE_CENTROIDS_H
#define UPDATE_CENTROIDS_H

#include "../headers/cluster.h"

/*
Cette fonction calcule le centroïd associé à un cluster donné.
*/

cluster_t** update_centroids(cluster_t *clusters[], uint32_t K) ; 

#endif // UPDATE_CENTROIDS_H