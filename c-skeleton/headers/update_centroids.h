#ifndef UPDATE_CENTROIDS_H
#define UPDATE_CENTROIDS_H

#include "../headers/cluster.h"

/**
 * @brief Met à jour les centroids des clusters en calculant la moyenne des points de chaque cluster.
 * 
 * @param clusters Tableau de pointeurs vers les clusters
 * @param K Nombre de clusters
 * @return Tableau de pointeurs vers les clusters mis à jour
 */
cluster_t** update_centroids(cluster_t *clusters[], uint32_t K) ; 

#endif // UPDATE_CENTROIDS_H