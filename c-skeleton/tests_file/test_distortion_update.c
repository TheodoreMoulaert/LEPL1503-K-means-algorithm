#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include "../headers/distortion.h"
#include "../headers/update_centroids.h"

void test_distortion_with_update_centroids() ; 
int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_distortion_with_update_centroids() {
    // Initialisation des clusters avec des données de test
    uint32_t taille = 2;
    cluster_t *clusters = malloc(taille * sizeof(cluster_t));
    for (uint32_t i = 0; i < taille; ++i) {
        clusters[i].size = 3; // Taille arbitraire pour le test
        clusters[i].center.dim = 2;
        clusters[i].center.coords = malloc(2 * sizeof(int64_t));
        // Centre arbitraire pour le test
        clusters[i].center.coords[0] = i * 10;
        clusters[i].center.coords[1] = i * 10 + 1;
        // Données arbitraires pour le test
        clusters[i].data = malloc(clusters[i].size * sizeof(point_t));
        for (uint64_t j = 0; j < clusters[i].size; ++j) {
            clusters[i].data[j].dim = 2;
            clusters[i].data[j].coords = malloc(2 * sizeof(int64_t));
            clusters[i].data[j].coords[0] = i * 10 + j;
            clusters[i].data[j].coords[1] = i * 10 + j + 1;
        }
    }

    // Appel de la fonction update_centroids pour obtenir les nouveaux centres des clusters
    cluster_t new_centroids = update_centroids(clusters, taille);

    // Appel de la fonction distortion avec les nouveaux centres des clusters
    squared_distance_func_t dummy_func = squared_euclidean_distance;
    uint64_t result = distortion(clusters, taille, dummy_func);

    // Valeur attendue en fonction des données de test
    // Vous devez ajuster cette valeur en fonction de vos données de test réelles
    uint64_t expected_result = 20;

    // Vérification du résultat
    CU_ASSERT_EQUAL(result, expected_result);

    // Nettoyage de la mémoire
    for (uint32_t i = 0; i < taille; ++i) {
        free(clusters[i].center.coords);
        for (uint64_t j = 0; j < clusters[i].size; ++j) {
            free(clusters[i].data[j].coords);
        }
        free(clusters[i].data);
    }
    free(clusters);
    free(new_centroids.data);
}

// Le reste de votre code de test reste inchangé

int main() {
    // Initialisation des tests
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Ajout de votre suite de tests
    CU_pSuite pSuite = CU_add_suite("Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test of distortion function with update_centroids", test_distortion_with_update_centroids))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Exécution des tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_error();
}
