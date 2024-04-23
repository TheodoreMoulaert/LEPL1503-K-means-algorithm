#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"
#include "../headers/cluster.h"

// Fonction principale pour exécuter le test
int main() {
    // Définition des centroides
    point_t centroids[3];
    centroids[0].dim = 2;
    centroids[0].coords = (int64_t*) malloc(2 * sizeof(int64_t));
    centroids[0].coords[0] = 1;
    centroids[0].coords[1] = 1;

    centroids[1].dim = 2;
    centroids[1].coords = (int64_t*) malloc(2 * sizeof(int64_t));
    centroids[1].coords[0] = 5;
    centroids[1].coords[1] = 7;

    centroids[2].dim = 2;
    centroids[2].coords = (int64_t*) malloc(2 * sizeof(int64_t));
    centroids[2].coords[0] = 3;
    centroids[2].coords[1] = 5;

    // Initialisation du cluster 1 avec les points donnés
    cluster_t *cluster1 = (cluster_t*) malloc(sizeof(cluster_t));
    cluster1->size = 7;
    cluster1->data = (point_t**) malloc(7 * sizeof(point_t*));
    for (int i = 0; i < 7; ++i) {
        cluster1->data[i] = (point_t*) malloc(sizeof(point_t));
        cluster1->data[i]->dim = 2;
        cluster1->data[i]->coords = (int64_t*) malloc(2 * sizeof(int64_t));
    }
    cluster1->data[0]->coords[0] = 1;
    cluster1->data[0]->coords[1] = 1;
    cluster1->data[1]->coords[0] = 2;
    cluster1->data[1]->coords[1] = 2;
    cluster1->data[2]->coords[0] = 5;
    cluster1->data[2]->coords[1] = 7;
    cluster1->data[3]->coords[0] = 5;
    cluster1->data[3]->coords[1] = 5;
    cluster1->data[4]->coords[0] = 4;
    cluster1->data[4]->coords[1] = 5;
    cluster1->data[5]->coords[0] = 3;
    cluster1->data[5]->coords[1] = 5;
    cluster1->data[6]->coords[0] = 3;
    cluster1->data[6]->coords[1] = 4;

    // Initialisation des autres clusters (vides)
    cluster_t *cluster2 = (cluster_t*) malloc(sizeof(cluster_t));
    cluster2->size = 0;
    cluster2->data = NULL;

    cluster_t *cluster3 = (cluster_t*) malloc(sizeof(cluster_t));
    cluster3->size = 0;
    cluster3->data = NULL;

    // Création du tableau de clusters
    cluster_t **clusters = (cluster_t**) malloc(3 * sizeof(cluster_t*));
    clusters[0] = cluster1;
    clusters[1] = cluster2;
    clusters[2] = cluster3;

    // Appel de la fonction à tester
    result_t result = assign_vectors_to_centroides(centroids, clusters, 3, squared_euclidean_distance);

    // Affichage des résultats
    printf("Changements: %s\n", result.changes ? "true" : "false");
    printf("Clusters résultants:\n");
    for (int i = 0; i < 3; ++i) {
        printf("Cluster %d (Centroid: (%" PRId64 ", %" PRId64 ")):\n", i, result.result_cluster[i]->centroide.coords[0], result.result_cluster[i]->centroide.coords[1]);
        for (int j = 0; j < result.result_cluster[i]->size; ++j) {
            printf("Point %d: (%" PRId64 ", %" PRId64 ")\n", j, result.result_cluster[i]->data[j]->coords[0], result.result_cluster[i]->data[j]->coords[1]);
        }
    }

    // Nettoyage de la mémoire
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < clusters[i]->size; ++j) {
            free(clusters[i]->data[j]->coords);
            free(clusters[i]->data[j]);
        }
        free(clusters[i]->data);
        free(clusters[i]);
    }
    free(clusters);

    for (int i = 0; i < 3; ++i) {
        free(centroids[i].coords);
    }

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < result.result_cluster[i]->size; ++j) {
            free(result.result_cluster[i]->data[j]->coords);
            free(result.result_cluster[i]->data[j]);
        }
        free(result.result_cluster[i]->data);
        free(result.result_cluster[i]);
    }
    free(result.result_cluster);

    return 0;
}
