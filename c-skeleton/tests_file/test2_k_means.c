#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/cluster.h"

void test_k_means() {
    // Définir les valeurs initiales pour le test
    cluster_t initial_centroids = {
        .size = 2,
        .data = (point_t[]){
            {.dim = 2, .coords = (int64_t[]){1, 1}},
            {.dim = 2, .coords = (int64_t[]){5, 5}}
        }
    };

    point_t *vectors[3];
    for (int i = 0; i < 3; i++) {
        vectors[i] = (point_t *)malloc(sizeof(point_t));
        vectors[i]->dim = 2;
        vectors[i]->coords = (int64_t *)malloc(2 * sizeof(int64_t));
        vectors[i]->coords[0] = i;
        vectors[i]->coords[1] = i;
    }

    uint32_t dimensions = 2;
    uint64_t num_vectors = 3;
    uint32_t K = 2;

    // Appel de la fonction à tester
    cluster_t *centroids = k_means(initial_centroids, K, vectors, num_vectors, dimensions);

    // Vérifier les résultats
    CU_ASSERT_PTR_NOT_NULL(centroids);

    // Nettoyage de la mémoire
    for (int i = 0; i < K; i++) {
        free(centroids[i].data);
        free(centroids[i].center.coords);
    }
    free(centroids);
    for (int i = 0; i < num_vectors; i++) {
        free(vectors[i]->coords);
        free(vectors[i]);
    }
}

int main() {
    // Initialiser le registre de tests
    CU_initialize_registry();

    // Ajouter une suite de tests
    CU_pSuite suite = CU_add_suite("Suite de tests pour k_means", NULL, NULL);
    CU_add_test(suite, "Test de k_means", test_k_means);

    // Exécuter les tests
    CU_basic_run_tests();

    // Nettoyer le registre de tests
    CU_cleanup_registry();

    return 0;
}