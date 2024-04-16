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
    int num_points = 7;
    int k = 3;

    // Centroides initiaux donnés
    point_t initial_centroids[k];
    initial_centroids[0].dim = 2;
    initial_centroids[0].coords = malloc(2 * sizeof(int64_t));
    initial_centroids[0].coords[0] = 2;
    initial_centroids[0].coords[1] = 2;

    initial_centroids[1].dim = 2;
    initial_centroids[1].coords = malloc(2 * sizeof(int64_t));
    initial_centroids[1].coords[0] = 5;
    initial_centroids[1].coords[1] = 7;

    initial_centroids[2].dim = 2;
    initial_centroids[2].coords = malloc(2 * sizeof(int64_t));
    initial_centroids[2].coords[0] = 3;
    initial_centroids[2].coords[1] = 5;

    // Points pour le premier cluster donnés
    int64_t P1_coords[7][2] = {{1, 1}, {2, 2}, {5, 7}, {5, 5}, {4, 5}, {3, 5}, {3, 4}};

    // Initialisation des clusters d'entrée avec les points donnés
    cluster_t *clusters_input[k];
    for (int i = 0; i < k; i++) {
        clusters_input[i] = malloc(sizeof(cluster_t));
        if (clusters_input[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour un cluster.\n");
            exit(EXIT_FAILURE);
        }

        // Allocation de mémoire pour les points du cluster
        clusters_input[i]->data = malloc(num_points * sizeof(point_t *));
        if (clusters_input[i]->data == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour les points du cluster.\n");
            exit(EXIT_FAILURE);
        }

        // Initialisation de la taille du cluster et des points
        clusters_input[i]->size = 0;

        // Utilisation des centroids initiaux
        clusters_input[i]->centroide = initial_centroids[i];
    }

    // Assignation des points pour le premier cluster
    for (int i = 0; i < num_points; i++) {
        clusters_input[0]->data[i] = malloc(sizeof(point_t));
        if (clusters_input[0]->data[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour un point.\n");
            exit(EXIT_FAILURE);
        }
        clusters_input[0]->data[i]->dim = 2;
        clusters_input[0]->data[i]->coords = malloc(2 * sizeof(int64_t));
        if (clusters_input[0]->data[i]->coords == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour les coordonnées d'un point.\n");
            exit(EXIT_FAILURE);
        }
        clusters_input[0]->data[i]->coords[0] = P1_coords[i][0];
        clusters_input[0]->data[i]->coords[1] = P1_coords[i][1];
        clusters_input[0]->size++;
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
    cluster_t **result_clusters = k_means(clusters_input, num_points, k, initial_centroids, initial_centroids, squared_euclidean_distance);

    // Assertions pour vérifier le résultat de la fonction
    assert(result_clusters != NULL);

    // Affichage des clusters et des centroides finaux
    printf("\nClusters finaux :\n");
    print_clusters(result_clusters, k);
    printf("\nCentroides finaux :\n");
    for (int i = 0; i < k; ++i) {
        printf("Centroide %d: ", i);
        print_centroid(result_clusters[i]->centroide);
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
