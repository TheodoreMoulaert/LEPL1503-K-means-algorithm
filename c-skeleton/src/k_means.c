#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../headers/k_means.h"
#include "../headers/point.h"

point_t* k_means(point_t *initial_centroids, int K, double **vectors, int num_vectors, int dimensions) {
    // Implémentation de la fonction k_means
    point_t *centroids = initial_centroids;
    point_t *clusters[K];
    
    // Initialisation des clusters
    for (int i = 0; i < K; i++) {
        clusters[i] = malloc(sizeof(point_t)); // Allouer de l'espace pour un cluster
        clusters[i]->dim = initial_centroids->dim;
        clusters[i]->coords = malloc(sizeof(int64_t) * initial_centroids->dim); // Allouer de l'espace pour les coordonnées
        clusters[i]->nbr_vector = 0;
    }
    
    // Copier les données de vectors dans les clusters
    for (int i = 0; i < K; i++) {
        for (uint32_t j = 0; j < initial_centroids->dim; j++) {
            clusters[i]->coords[j] = vectors[i][j];
        }
        clusters[i]->nbr_vector = num_vectors; // Assurez-vous d'ajuster le nombre de vecteurs
    }

    bool changed = true;
    while (changed) {
        changed = assign_vectors_to_centroids((double **)centroids->coords, (double ***)clusters, K, num_vectors, dimensions);
        centroids = update_centroids(clusters);
    }

    return centroids;
}