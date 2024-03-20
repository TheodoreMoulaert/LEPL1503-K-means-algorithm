#ifndef K_MEANS_H
#define K_MEANS_H

#include <stdbool.h>
#include "../headers/point.h"

// Fonction pour assigner les vecteurs aux centroids les plus proches
bool assign_vectors_to_centroids(point_t *centroids, point_t **clusters, int num_centroids, int num_vectors, int dimensions);

// Fonction pour mettre à jour les centroids
point_t* update_centroids(point_t **clusters, int K);

// Fonction k_means
point_t* k_means(point_t *initial_centroids, int K, double **vectors, int num_vectors, int dimensions);

#endif /* K_MEANS_H */