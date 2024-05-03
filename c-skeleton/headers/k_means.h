#ifndef K_MEANS_H
#define K_MEANS_H

#include <stdbool.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"

/**
 * @brief Applique l'algorithme de K-means pour regrouper les points en k clusters.
 * 
 * @param clusters Tableau de pointeurs vers les clusters initiaux
 * @param num_points Nombre total de points à regrouper
 * @param k Nombre de clusters à former
 * @param initial_centroids Tableau des centroids initiaux
 * @param final_centroids Tableau des centroids finaux mis à jour par l'algorithme
 * @param distance_func Fonction de calcul de distance entre les points
 * @return Tableau de pointeurs vers les clusters finaux, ou NULL en cas d'erreur
 */
cluster_t** k_means(cluster_t**clusters_input, uint64_t num_points, uint32_t k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func) ; 


#endif  // K_MEANS_H