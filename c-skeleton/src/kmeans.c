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
    if (clusters == NULL || initial_centroids == NULL || final_centroids == NULL) {
        fprintf(stderr, "Paramètres invalides pour la fonction k_means.\n");
        return NULL;
    }
    // Initialise les centroids finaux avec les centroids initiaux
    for (int i = 0; i < k; i++) {
        clusters[i]->centroide = initial_centroids[i];
    }

    point_t *old_centroids = (point_t *)malloc(k * sizeof(point_t));
    if (old_centroids == NULL) {
        fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 3.\n");
        return NULL; 
    }
    //printf("%d\n", 2);
    result_t result; 

    // Exécute des itérations jusqu'à convergence
    bool convergence = false;
    uint64_t i = 0; 
    while (!convergence) {
        // Sauvegarde les anciens centroids

        for (int i = 0; i < k; i++) {
            old_centroids[i].coords = final_centroids[i].coords;
            old_centroids[i].dim = final_centroids[i].dim;
        }
        //printf("%d\n", 3);
        // Assigne les points aux clusters
        if (i == 0) {
            result = assign_vectors_to_centroides(final_centroids, clusters, k, distance_func);
        } else {
            result = assign_vectors_to_centroides(final_centroids, result.result_cluster, k, distance_func);
        }

        if (result.result_cluster == NULL) {
            fprintf(stderr, "L'allocation de mémoire a échoué pour result.result_cluster.\n");
            free(old_centroids);
            return NULL;
        }

        convergence = result.changes; 
        //printf("%d\n", 5);

        if (clusters == NULL) {
            fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 4.\n");
            free(old_centroids);
            return NULL;
        }
        //printf("%d\n", 4);
    
        update_centroids(result.result_cluster, k);
        //printf("%d\n", 5);
        i++;  
    }

    // Libérer la mémoire pour les old_centroids
    free(old_centroids);
    return result.result_cluster;

}