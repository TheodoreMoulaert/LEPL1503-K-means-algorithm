#ifndef ASSIGN_VECTORS_TO_CENTROIDS_H
#define ASSIGN_VECTORS_TO_CENTROIDS_H

#include "../headers/assign_vector_to_centro.h"
#include <stddef.h>
#include "../headers/distance.h"
#include "../headers/cluster.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * Affecte les vecteurs aux centroids les plus proches dans les clusters correspondants.
 * 
 * @param centroids Tableau des centroids
 * @param clusters Tableau de pointeurs vers les clusters
 * @param K Nombre de centroids
 * @param distance_func Fonction de calcul de distance entre les points
 * @return Résultat de l'affectation des vecteurs aux centroids les plus proches
 */
result_t assign_vectors_to_centroides(point_t *centroids, cluster_t **clusters, uint32_t K, squared_distance_func_t distance_func) ; 


#endif /* ASSIGN_VECTORS_TO_CENTROIDS_H */
