#ifndef K_MEANS_H
#define K_MEANS_H

#include <stdbool.h>
#include "../headers/point.h"

// Fonction pour assigner les vecteurs aux centroids les plus proches
bool assign_vectors_to_centroids(point_t *centroids, point_t **clusters, uint64_t  num_centroids, uint64_t  num_vectors, uint32_t dimensions);

// Fonction pour mettre à jour les centroids
point_t* update_centroids(point_t **clusters, uint32_t K);

// Fonction k_means
//point_t* k_means(point_t *initial_centroids, int K, double **vectors, int num_vectors, int dimensions);
point_t* k_means(point_t *initial_centroids, uint32_t K, point_t **vectors, uint64_t num_vectors, uint32_t dimensions);
#endif /* K_MEANS_H */