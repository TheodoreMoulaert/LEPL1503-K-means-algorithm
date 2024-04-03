#include <stdbool.h> // Ajout de la bibliothèque stdbool.h
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"

void k_means(cluster_t**clusters_input, int num_points, int k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func) {
    // Initialise les centroids finaux avec les centroids initiaux
    for (int i = 0; i < k; i++) {
        final_centroids[i] = initial_centroids[i];
    }

    point_t **clusters = NULL;
    point_t *old_centroids = (point_t *)malloc(k * sizeof(point_t));
    if (old_centroids == NULL) {
        fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 3.\n");
        return; 
    }

    // Exécute des itérations jusqu'à convergence
    while (1) {
        // Save old centroids
        for (int i = 0; i < k; i++) {
            old_centroids[i] = final_centroids[i];
        }

        // Assigne les points au clusters
        clusters = assign_vectors_to_centroides(final_centroids, clusters_input, num_points, k, distance_func);

        if (clusters == NULL) {
            fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 4.\n");
            free(old_centroids);
            return;
        }
        update_centroids(clusters, k);

        // Check la convergence
        int convergence = 1;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < final_centroids[i].dim; j++) {
                if (final_centroids[i].coords[j] != old_centroids[i].coords[j]) {
                    convergence = 0;
                    break;
                } // Ajout du point-virgule manquant ici
            }

            // Libère la mémoire pour les clusters
            for (int i = 0; i < k; i++) {
                free(clusters[i]);
            }
            free(clusters);

            if (convergence) {
                break;
            }
        }
    }

    // Libère les mémoire pour les old_centroids
    free(old_centroids);
}
