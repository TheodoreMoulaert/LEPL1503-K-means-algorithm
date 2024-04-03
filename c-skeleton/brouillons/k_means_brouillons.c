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

/*cluster_t* k_means(cluster_t initial_centroids, uint32_t K, point_t **vectors, uint64_t num_vectors, uint32_t dimensions,squared_distance_func_t distance_func) {
    // Implémentation de la fonction k_means
    cluster_t* centroids = malloc(K * sizeof(cluster_t));
    cluster_t* clusters = malloc(K * sizeof(cluster_t));

    if (centroids == NULL || clusters == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les centroids ou les clusters\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des centroids en copiant les valeurs de initial_centroids
    for (uint32_t i = 0; i < K; i++) {
        centroids[i] = initial_centroids;
    }

    // Initialisation des clusters en copiant les données de vectors dans chaque cluster
    for (uint32_t i = 0; i < K; i++) {
        clusters[i].size = num_vectors;
        clusters[i].data = malloc(num_vectors * sizeof(point_t));

        if (clusters[i].data == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les données du cluster\n");
            exit(EXIT_FAILURE);
        }

        for (uint64_t j = 0; j < num_vectors; j++) {
            clusters[i].data[j].dim = dimensions;
            clusters[i].data[j].coords = malloc(dimensions * sizeof(int64_t));

            if (clusters[i].data[j].coords == NULL) {
                fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les coordonnées du centre du cluster\n");
                exit(EXIT_FAILURE);
            }

            for (uint32_t k = 0; k < dimensions; k++) {
                clusters[i].data[j].coords[k] = vectors[j]->coords[k];
            }
        }

        // Initialisation des coordonnées du centre à zéro pour chaque cluster
        clusters[i].center.dim = dimensions;
        clusters[i].center.coords = calloc(dimensions, sizeof(int64_t));

        if (clusters[i].center.coords == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les coordonnées du centre du cluster\n");
            exit(EXIT_FAILURE);
        }
    }

    //uint64_t changed = 1;
    uint64_t changed = 2;
    //while (changed>0) { //while (changed)
    while (changed){
        //changed = assign_vector_to_centroids(centroids, clusters, K, distance_func);
        changed--;
        
        for (uint32_t i = 0; i < K; i++) {
            centroids[i] = update_centroids(clusters, 1); //& [i]
        }
    }

    // Libération de la mémoire allouée pour les clusters
    for (uint32_t i = 0; i < K; i++) {
        for (uint64_t j = 0; j < num_vectors; j++) {
            free(clusters[i].data[j].coords);
        }
        free(clusters[i].data);
        free(clusters[i].center.coords);
    }
    free(clusters);

    return centroids;
}*/
