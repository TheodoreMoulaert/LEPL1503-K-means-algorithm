#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"

point_t* k_means(point_t *initial_centroids, int K, double **vectors, int num_vectors, int dimensions) {
    // Implémentation de la fonction k_means
    point_t *centroids = initial_centroids;
    point_t *clusters[K];
    
    // Initialisation des clusters
    for (int i = 0; i < K; i++) {
        clusters[i] = malloc(sizeof(point_t)); // Allouer de l'espace pour un cluster
        if (clusters[i] == NULL) {
            // Gestion d'erreur si l'allocation échoue
            for (int j = 0; j < i; j++) {
                free(clusters[j]->coords);
                free(clusters[j]);
            }
            return NULL; // Retourner NULL pour signaler l'échec de l'allocation
        }
        clusters[i]->dim = initial_centroids->dim;
        clusters[i]->coords = malloc(sizeof(int64_t) * initial_centroids->dim); // Allouer de l'espace pour les coordonnées
        if (clusters[i]->coords == NULL) {
            // Gestion d'erreur si l'allocation échoue
            for (int j = 0; j < i; j++) {
                free(clusters[j]->coords);
                free(clusters[j]);
            }
            free(clusters[i]); // Libérer l'espace alloué pour le cluster
            return NULL; // Retourner NULL pour signaler l'échec de l'allocation
        }
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

    // Libération de la mémoire allouée pour les clusters
    for (int i = 0; i < K; i++) {
        free(clusters[i]->coords);
        free(clusters[i]);
    }

    return centroids;
}
