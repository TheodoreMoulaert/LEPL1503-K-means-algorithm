#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../headers/cluster.h" 
#include "../headers/point.h" 
#include "../headers/update_centroids.h" 
#include "../headers/main.h"

// Définition des constantes K et dimension
#define K 10



// Fonction pour afficher les données d'un cluster
void print_cluster(cluster_t cluster) {
    printf("Cluster:\n");
    for (int i = 0; i < k; i++) {
        printf("\tData %d: ", i);
        for (uint32_t j = 0; j < cluster.data[i].dim; j++) {
            printf("%ld ", cluster.data[i].coords[j]);
        }
        printf("\n");
    }
}

int main() {
    // Création de clusters de données de test
    cluster_t clusters[K];
    for (int i = 0; i < K; i++) {
        clusters[i].data = (point_t *)malloc(sizeof(point_t));
        clusters[i].data[0].dim = 3;
        clusters[i].data[0].coords = (int64_t *)malloc(3 * sizeof(int64_t));
        for (int j = 0; j < 3; j++) {
            clusters[i].data[0].coords[j] = (i + 1) * (j + 1);
        }
    }

    // Appel de la fonction update_centroids
    cluster_t centroids = update_centroids(clusters);

    // Affichage des centroids
    print_cluster(centroids);

    // Libération de la mémoire allouée
    for (int i = 0; i < K; i++) {
        free(clusters[i].data[0].coords);
        free(clusters[i].data);
    }
    free(centroids.data);

    return 0;
}