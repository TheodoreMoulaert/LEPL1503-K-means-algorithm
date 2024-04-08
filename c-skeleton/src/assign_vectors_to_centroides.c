#include "../headers/assign_vector_to_centro.h"
#include <stddef.h>
#include "../headers/distance.h"
#include <stdlib.h>
#include <stdio.h>

cluster_t** assign_vectors_to_centroides(point_t *centroids, cluster_t **clusters, uint32_t K, squared_distance_func_t distance_func) {
    if (centroids == NULL || clusters == NULL) {
        // Gérer l'erreur de pointeur nul
        return NULL;
    }

    // Allouer un nouveau tableau de clusters pour contenir les nouveaux clusters
    cluster_t **new_clusters = (cluster_t**) malloc(K * sizeof(cluster_t*));
    if (new_clusters == NULL) {
        // Gérer l'erreur d'allocation de mémoire
        return NULL;
    }

    // Initialiser chaque nouveau cluster
    for (uint32_t i = 0; i < K; ++i) {
        new_clusters[i] = (cluster_t*) malloc(sizeof(cluster_t));
        if (new_clusters[i] == NULL) {
            // Gérer l'erreur d'allocation de mémoire
            // Libérer la mémoire allouée pour les nouveaux clusters déjà initialisés
            for (uint32_t j = 0; j < i; ++j) {
                free(new_clusters[j]->data);
                free(new_clusters[j]);
            }
            free(new_clusters);
            return NULL;
        }
        new_clusters[i]->size = 0;
        new_clusters[i]->data = NULL; // Initialiser le tableau de données à NULL
    }

    // Parcourir tous les centroides
    for (uint32_t current_centroid_idx = 0; current_centroid_idx < K; ++current_centroid_idx) {
        // Parcourir tous les vecteurs du cluster actuel
        for (uint64_t i = 0; i < clusters[current_centroid_idx]->size; ++i) {
            point_t *vector = clusters[current_centroid_idx]->data[i];
            // Trouver le centroïde le plus proche pour le vecteur
            uint32_t closest_centroid_idx = 0;
            uint64_t closest_centroid_distance = UINT64_MAX;
            for (uint32_t centroid_idx = 0; centroid_idx < K; ++centroid_idx) {
                uint64_t distance = distance_func(vector, &centroids[centroid_idx]);
                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }
            
            // Ajouter le vecteur au cluster le plus proche dans le nouveau tableau de clusters
            uint32_t idx = new_clusters[closest_centroid_idx]->size;
            new_clusters[closest_centroid_idx]->data = (point_t**) realloc(new_clusters[closest_centroid_idx]->data, (idx + 1) * sizeof(point_t*));
            if (new_clusters[closest_centroid_idx]->data == NULL) {
                // Gérer l'erreur d'allocation de mémoire
                // Libérer la mémoire allouée pour les nouveaux clusters déjà initialisés
                for (uint32_t j = 0; j < K; ++j) {
                    free(new_clusters[j]->data);
                    free(new_clusters[j]);
                }
                free(new_clusters);
                return NULL;
            }
            new_clusters[closest_centroid_idx]->data[idx] = vector;
            new_clusters[closest_centroid_idx]->size++;
        }
    }

    // Libérer la mémoire allouée pour les anciens clusters
    for (uint32_t i = 0; i < K; ++i) {
        free(clusters[i]->data);
        free(clusters[i]);
    }
    free(clusters);

    return new_clusters;
}
