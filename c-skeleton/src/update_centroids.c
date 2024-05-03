#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"

/**
 * @brief Met à jour les centroids des clusters en calculant la moyenne des points de chaque cluster.
 * 
 * @param clusters Tableau de pointeurs vers les clusters
 * @param K Nombre de clusters
 * @return Tableau de pointeurs vers les clusters mis à jour
 */

cluster_t** update_centroids(cluster_t *clusters[], uint32_t K) {
    for (uint32_t i = 0; i < K; i++) {
     
        uint32_t dim = clusters[0]->data[0]->dim;
        int64_t *moyenne = calloc(dim, sizeof(int64_t));

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
        printf("%d\n", 6);

        for (uint32_t xi = 0; xi < dim; xi++) {
            moyenne[xi] /= clusters[i]->size; // Calcul de la moyenne
            clusters[i]->centroide.coords[xi] = moyenne[xi]; // Mise à jour du centroïde
            clusters[i]->centroide.dim = dim; 
        }

        free(moyenne); // Libérer la mémoire allouée pour moyenne
    }
    return clusters;
}
