#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"

cluster_t** update_centroids(cluster_t *clusters[], uint32_t K) {
    for (uint32_t i = 0; i < K; i++) {
     
        uint32_t dim = clusters[0]->data[0]->dim;
        uint32_t *moyenne = calloc(dim, sizeof(uint32_t));

        if (moyenne == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        
        if (clusters[i]->size < 1) {
            fprintf(stderr, "Size of cluster less than 1: division by zero\n");
            free(moyenne); // Libérer la mémoire allouée pour moyenne
            continue; // Passer à l'itération suivante si la taille du cluster est inférieure à 1
        }

        for (uint64_t yi = 0; yi < clusters[i]->size; yi++) {
            for (uint32_t xi = 0; xi < dim; xi++) {
                moyenne[xi] += clusters[i]->data[yi]->coords[xi];
            }
        }

        for (uint32_t xi = 0; xi < dim; xi++) {
            moyenne[xi] /= clusters[i]->size; // Calcul de la moyenne
            clusters[i]->centroide.coords[xi] = moyenne[xi]; // Mise à jour du centroïde
            clusters[i]->centroide.dim = dim; 
        }

        free(moyenne); // Libérer la mémoire allouée pour moyenne
    }
    return clusters;
}
