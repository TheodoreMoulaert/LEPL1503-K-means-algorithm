#include <stdbool.h>
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

cluster_t** k_means(cluster_t** clusters, int num_points, int k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func) {
    // Initialise les centroids finaux avec les centroids initiaux
    for (int i = 0; i < k; i++) {
        final_centroids[i].coords = initial_centroids[i].coords;
        final_centroids[i].dim = initial_centroids[i].dim;
    }
    printf("%d\n", 1);

    point_t *old_centroids = (point_t *)malloc(k * sizeof(point_t));
    if (old_centroids == NULL) {
        fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 3.\n");
        return NULL; 
    }
    printf("%d\n", 2);
    cluster_t **new_clusters;

    // Exécute des itérations jusqu'à convergence
    uint64_t convergence = 1;
    while (convergence == 1) {
        // Sauvegarde les anciens centroids
        for (int i = 0; i < k; i++) {
            old_centroids[i].coords = final_centroids[i].coords;
            old_centroids[i].dim = final_centroids[i].dim;
        }
        printf("%d\n", 3);
        // Assigne les points aux clusters
        convergence = assign_vectors_to_centroides(final_centroids, clusters, k, distance_func, new_clusters);
        printf("%d\n", 5);

        if (clusters == NULL) {
            fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 4.\n");
            free(old_centroids);
            return NULL;
        }
        printf("%d\n", 4);

        update_centroids(new_clusters, k);
        clusters = new_clusters;
        printf("%d\n", 5);

        // Vérifie la convergence
        convergence = true;
        for (int i = 0; i < k; i++) {
            for (int j = 0; j < final_centroids[i].dim; j++) {
                if (final_centroids[i].coords[j] != old_centroids[i].coords[j]) {
                    convergence = false;
                    break;
                }
            }
            if (!convergence) {
                break;
            }
        }

        // Libère la mémoire pour les clusters
        for (int i = 0; i < k; i++) {
            free(clusters[i]);
        }
        free(clusters);
    }

    // Libère la mémoire pour les old_centroids
    free(old_centroids);
    return clusters;
}