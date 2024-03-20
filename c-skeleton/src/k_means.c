#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include "../headers/k_means.h"
#include "../headers/point.h"

point_t* k_means(point_t *initial_centroids, int K) {
    // Implémentation de la fonction k_means
    point_t *centroids = initial_centroids;
    point_t *clusters[K];

    // Initialisation des clusters
    for (int i = 0; i < K; i++) {
        clusters[i]->coords = NULL;
        clusters[i]->dim = initial_centroids->dim;
        clusters[i]->nbr_vector = 0;
    }
    clusters[0] = vectors; // Suppose que vectors est une variable contenant les données à segmenter

    bool changed = true;
    while (changed) {
        changed = assign_vectors_to_centroids(centroids, clusters, K);
        centroids = update_centroids(clusters, K);
    }

    return centroids;
}
