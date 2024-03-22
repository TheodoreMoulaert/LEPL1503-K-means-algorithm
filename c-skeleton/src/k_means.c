#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"

cluster_t* k_means(cluster_t initial_centroids, uint32_t K, point_t **vectors, uint64_t num_vectors, uint32_t dimensions,squared_distance_func_t distance_func) {
    // Implémentation de la fonction k_means
    cluster_t* centroids = malloc(K * sizeof(cluster_t));
    if (centroids == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les centroids\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < K; i++) {
        centroids[i] = initial_centroids;
    }

    cluster_t* clusters = malloc(K * sizeof(cluster_t));
    if (clusters == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les clusters\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < K; i++) {
        clusters[i].data = malloc(num_vectors * sizeof(point_t));
        if (clusters[i].data == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les données du cluster\n");
            exit(EXIT_FAILURE);
        }
        clusters[i].size = num_vectors;
        clusters[i].center.dim = dimensions;
        clusters[i].center.coords = calloc(dimensions, sizeof(int64_t));
        if (clusters[i].center.coords == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les coordonnées du centre du cluster\n");
            exit(EXIT_FAILURE);
        }
        
    }
    // Copier les données de vectors dans les clusters
    for (uint64_t i = 0; i < num_vectors; i++) {
        for (uint32_t j = 0; j < dimensions; j++) {
            clusters[0].data[i].coords[j] = vectors[i]->coords[j];
        }
    }

    int changed = 1;
    while (changed) {
        changed = assign_vector_to_centroids(centroids, clusters, K, distance_func );
        for (uint32_t i = 0; i < K; i++) {
            centroids[i] = update_centroids(&clusters[i], 1);
        }
    }

    // Libération de la mémoire allouée pour les clusters
    for (uint32_t i = 0; i < K; i++) {
        free(clusters[i].data);
        free(clusters[i].center.coords);
    }
    free(clusters);

    return centroids;
}


/*#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"

point_t* k_means(point_t *initial_centroids, uint32_t K, point_t **vectors, uint64_t num_vectors, uint32_t dimensions) {
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
*/