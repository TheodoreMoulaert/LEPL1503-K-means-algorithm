#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"

// Déclaration de la fonction de test
void test_k_means();

// Fonction pour imprimer les clusters
void print_clusters(cluster_t **clusters, int num_clusters);

// Fonction pour imprimer un seul centroïde
void print_centroid(point_t centroid);

// Fonction principale pour exécuter les tests
int main() {
    test_k_means();
    return 0;
}

void test_k_means() {
    int num_points = 4;
    int k = 2;

    point_t initial_centroids[k];
    point_t final_centroids[k];

    // Initialisation des centroids avec des valeurs arbitraires pour le test
    for (int i = 0; i < k; i++) {
        initial_centroids[i].dim = 2;
        initial_centroids[i].coords = (int64_t *) malloc(2 * sizeof(int64_t));
        final_centroids[i].dim = 2;
        final_centroids[i].coords = (int64_t *) malloc(2 * sizeof(int64_t));

        // Vérification des allocations mémoire
        if (initial_centroids[i].coords == NULL || final_centroids[i].coords == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour les coordonnées des centroids.\n");
            exit(EXIT_FAILURE);
        }

        // Les valeurs sont arbitrairement choisies pour le test
        initial_centroids[i].coords[0] = i * 10;
        initial_centroids[i].coords[1] = i * 10 + 1;
        final_centroids[i].coords[0] = i * 10 + 2;
        final_centroids[i].coords[1] = i * 10 + 3;
    }
    cluster_t *clusters_input[k];
    for (int i = 0; i < k; i++) { // Correction ici
        clusters_input[i] = malloc(sizeof(cluster_t));
        if (clusters_input[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour un cluster.\n");
            exit(EXIT_FAILURE);
        }

        // Initialisation des clusters avec des points de test (coordonnées arbitraires)
        clusters_input[i]->size = 1;
        clusters_input[i]->data = malloc(sizeof(point_t*));
        clusters_input[i]->data[0] = malloc(sizeof(point_t));

        // Vérification des allocations mémoire
        if (clusters_input[i]->data == NULL || clusters_input[i]->data[0] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour un point ou un cluster.\n");
            exit(EXIT_FAILURE);
        }

        clusters_input[i]->data[0]->dim = 2;
        clusters_input[i]->data[0]->coords = malloc(2 * sizeof(int64_t));

        // Vérification de l'allocation mémoire
        if (clusters_input[i]->data[0]->coords == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour les coordonnées d'un point.\n");
            exit(EXIT_FAILURE);
        }

        // Les valeurs sont arbitrairement choisies pour le test
        clusters_input[i]->data[0]->coords[0] = i;
        clusters_input[i]->data[0]->coords[1] = i + 10;

        // Utilisation des mêmes centroids initiaux pour tous les clusters
        clusters_input[i]->centroide.dim = 2;
        clusters_input[i]->centroide.coords = initial_centroids[i % k].coords;
    }

    // Affichage des clusters et des centroides initiaux
    printf("Clusters initiaux :\n");
    print_clusters(clusters_input, k);
    printf("\nCentroides initiaux :\n");
    for (int i = 0; i < k; ++i) {
        printf("Centroide %d: ", i);
        print_centroid(initial_centroids[i]);
    }

    // Exécution de la fonction à tester
    cluster_t **result_clusters = k_means(clusters_input, num_points, k, initial_centroids, final_centroids, squared_euclidean_distance);

    // Assertions pour vérifier le résultat de la fonction
    assert(result_clusters != NULL);

    // Affichage des clusters et des centroides finaux
    printf("\nClusters finaux :\n");
    print_clusters(result_clusters, k);
    printf("\nCentroides finaux :\n");
    // Libération de la mémoire allouée pour les clusters de départ
    for (int i = 0; i < k; i++) { // Correction ici
        free(clusters_input[i]->data[0]->coords);
        free(clusters_input[i]->data[0]);
        free(clusters_input[i]->data);
        free(clusters_input[i]);
    }

    // Libération de la mémoire allouée pour les centroids initiaux et finaux
    for (int i = 0; i < k; i++) {
        free(initial_centroids[i].coords);
        free(final_centroids[i].coords); // Vous avez oublié cette ligne
    }
}

// Fonction pour imprimer les clusters
void print_clusters(cluster_t **clusters, int num_clusters) {
    for (int i = 0; i < num_clusters; ++i) {
        printf("Cluster %d:\n", i);
        if (clusters[i]->size == 0) {
            printf("Ce cluster est vide.\n");
        } else {
            for (int j = 0; j < clusters[i]->size; ++j) {
                printf("Point %d: (%" PRId64 ", %" PRId64 ")\n", j, clusters[i]->data[j]->coords[0], clusters[i]->data[j]->coords[1]);
            }
        }
    }
}

// Fonction pour imprimer un seul centroïde
void print_centroid(point_t centroid) {
    printf("(%" PRId64 ", %" PRId64 ")\n", centroid.coords[0], centroid.coords[1]);
}
