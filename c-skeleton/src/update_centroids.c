#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"

cluster_t** update_centroids(cluster_t *clusters[], uint32_t K) {
    for (uint32_t i = 0; i < K; i++) {
        cluster_t *currentCluster = clusters[i];
        uint32_t dim = currentCluster->centroide.dim;
        uint32_t *moyenne = calloc(dim, sizeof(uint32_t));

        if (moyenne == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        
        if (currentCluster->size < 1) {
            fprintf(stderr, "Size of cluster less than 1: division by zero\n");
            free(moyenne); // Libérer la mémoire allouée pour moyenne
            continue; // Passer à l'itération suivante si la taille du cluster est inférieure à 1
        }

        for (uint64_t yi = 0; yi < currentCluster->size; yi++) {
            for (uint32_t xi = 0; xi < dim; xi++) {
                moyenne[xi] += currentCluster->data[yi]->coords[xi];
            }
        }

        for (uint32_t xi = 0; xi < dim; xi++) {
            moyenne[xi] /= currentCluster->size; // Calcul de la moyenne
            currentCluster->centroide.coords[xi] = moyenne[xi]; // Mise à jour du centroïde
        }

        free(moyenne); // Libérer la mémoire allouée pour moyenne
    }
    return clusters;
}
