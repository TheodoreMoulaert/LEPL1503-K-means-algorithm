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
        initial_centroids[i].coords =malloc(2 * sizeof(int64_t));
        final_centroids[i].dim = 2;
        final_centroids[i].coords = malloc(2 * sizeof(int64_t));

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

    // Création d'un tableau de clusters pour les points de test
    cluster_t *clusters_input[num_points];
    for (int i = 0; i < num_points; i++) {
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
        clusters_input[i]->data[0]->coords[1] = i + 1;

        // Utilisation des mêmes centroids initiaux pour tous les clusters
        clusters_input[i]->centroide.dim = 2;
        clusters_input[i]->centroide.coords = initial_centroids[i % k].coords;
    }

    // Exécution de la fonction à tester
    cluster_t **result_clusters = k_means(clusters_input, num_points, k, initial_centroids, final_centroids, squared_euclidean_distance);

    // Assertions pour vérifier le résultat de la fonction
    assert(result_clusters != NULL);


}

