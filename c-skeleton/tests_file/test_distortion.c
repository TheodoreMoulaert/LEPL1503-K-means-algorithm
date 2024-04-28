#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"

// Initialisation de la suite de tests
int init_suite(void) {
    return 0;
}

// Nettoyage de la suite de tests
int clean_suite(void) {
    return 0;
}

// Test de la fonction distortion
void test_distortion() {
    // Initialisation des données
    uint32_t k = 2;

    // Construction des clusters
    cluster_t **clusters = malloc(k * sizeof(cluster_t *));
    for (uint32_t i = 0; i < k; ++i) {
        clusters[i] = malloc(sizeof(cluster_t));
        clusters[i]->size = 3; 
        clusters[i]->centroide.dim = 2;
        clusters[i]->centroide.coords = malloc(2 * sizeof(int64_t));
        clusters[i]->centroide.coords[0] = i * 10;
        clusters[i]->centroide.coords[1] = i * 10 + 1;
        clusters[i]->data = malloc(clusters[i]->size * sizeof(point_t *));
        for (uint64_t j = 0; j < clusters[i]->size; ++j) {
            clusters[i]->data[j] = malloc(sizeof(point_t));
            clusters[i]->data[j]->dim = 2;
            clusters[i]->data[j]->coords = malloc(2 * sizeof(int64_t));
            clusters[i]->data[j]->coords[0] = i * 10 + j;
            clusters[i]->data[j]->coords[1] = i * 10 + j + 1;
        }
    }

    // Choix de la fonction de distance pour les tests
    squared_distance_func_t dummy_func = squared_euclidean_distance;

    // Application de la fonction distortion
    uint64_t result = distortion((const cluster_t **) clusters, k, dummy_func);

    // La valeur attendue
    uint64_t expected_result = 20;

    // Test si les résultats correspondent
    CU_ASSERT_EQUAL(result, expected_result);

    // Nettoyage
    for (uint32_t i = 0; i < k; ++i) {
        free(clusters[i]->centroide.coords);
        for (uint64_t j = 0; j < clusters[i]->size; ++j) {
            free(clusters[i]->data[j]->coords);
            free(clusters[i]->data[j]);
        }
        free(clusters[i]->data);
        free(clusters[i]);
    }
    free(clusters);
}

int main() {
    // Initialisation du registre CUnit
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Ajout d'une suite de tests
    CU_pSuite pSuite = CU_add_suite("Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ajout du test à la suite
    if ((NULL == CU_add_test(pSuite, "Test de la fonction distortion", test_distortion))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Configuration de l'affichage des résultats
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
