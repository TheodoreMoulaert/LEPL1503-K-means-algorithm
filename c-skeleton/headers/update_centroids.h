#ifndef UPDATE_CENTROIDS_H
#define UPDATE_CENTROIDS_H

#include "../headers/cluster.h"
/*
Cette fonction calcule le centroïd associé à un cluster donné.
La fonction return -1 si une erreur se produit, 0 sinon.
*/
uint64_t update_centroids(cluster_t* );

#endif // UPDATE_CENTROIDS_H