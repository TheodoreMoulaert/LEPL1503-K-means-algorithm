#include "../headers/assign_vector_to_centro.h"
#include <stddef.h>
#include "../headers/distance.h"
#include <stdlib.h>
#include <stdio.h>
uint64_t assign_vectors_to_centroides(point_t *centroids, cluster_t **clusters, uint32_t K, squared_distance_func_t distance_func, cluster_t ***new_clusters) {
    uint64_t unchanged = 1; // Flag to indicate if the assignment remains unchanged

    if (centroids == NULL || clusters == NULL) {
        // Gérer l'erreur de pointeur nul
        return unchanged;
    }

    // Allouer un nouveau tableau de clusters pour contenir les nouveaux clusters
    *new_clusters = (cluster_t**) malloc(K * sizeof(cluster_t*));
    if (*new_clusters == NULL) {
        // Gérer l'erreur d'allocation de mémoire
        return unchanged;
    }

    // Initialiser chaque nouveau cluster
    for (uint32_t i = 0; i < K; ++i) {
        (*new_clusters)[i] = (cluster_t*) malloc(sizeof(cluster_t));
        if ((*new_clusters)[i] == NULL) {
            // Gérer l'erreur d'allocation de mémoire
            // Libérer la mémoire allouée pour les nouveaux clusters déjà initialisés
            for (uint32_t j = 0; j < i; ++j) {
                free((*new_clusters)[j]->data);
                free((*new_clusters)[j]);
            }
            free(*new_clusters);
            return unchanged;
        }

        // Assurez-vous que clusters[i]->size est correctement défini
        if (clusters[i] == NULL || clusters[i]->size <= 0) {
            // Gérer l'erreur de taille incorrecte pour clusters[i]->size
            // Libérer la mémoire allouée pour les nouveaux clusters déjà initialisés
            for (uint32_t j = 0; j < i; ++j) {
                free((*new_clusters)[j]->data);
                free((*new_clusters)[j]);
            }
            free(*new_clusters);
            return unchanged;
        }

        // Allouer une taille initiale pour le tableau de données
        (*new_clusters)[i]->data = (point_t**) malloc(clusters[i]->size * sizeof(point_t*));
        if ((*new_clusters)[i]->data == NULL) {
            // Gérer l'erreur d'allocation de mémoire
            // Libérer la mémoire allouée pour les nouveaux clusters déjà initialisés
            for (uint32_t j = 0; j < i; ++j) {
                free((*new_clusters)[j]->data);
                free((*new_clusters)[j]);
            }
            free(*new_clusters);
            return unchanged;
        }

        (*new_clusters)[i]->size = 0; // Initialiser la taille à zéro
    }

    // Le reste du code reste inchangé

    return unchanged;
}
