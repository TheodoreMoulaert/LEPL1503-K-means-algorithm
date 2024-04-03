#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"

// Initialisation de la suite de tests
int init_suite(void) {
    return 0;
}

// Nettoyage de la suite de tests
int clean_suite(void) {
    return 0;
}

// Test de la fonction update_centroids
void test_update_centroids() {
    // Initialisation des données
    uint32_t k = 2;

    // Construction des clusters
    cluster_t **clusters = malloc(k * sizeof(cluster_t *));
    CU_ASSERT_PTR_NOT_NULL_FATAL(clusters); // Vérification de l'allocation

    for (uint32_t i = 0; i < k; ++i) {
        clusters[i] = malloc(sizeof(cluster_t));
        if (clusters[i] == NULL) {
            // Si l'allocation échoue, on libère les allocations précédentes et on arrête le test
            for (uint32_t j = 0; j < i; ++j) {
                free(clusters[j]);
            }
            free(clusters);
            CU_FAIL_FATAL("Allocation échouée pour clusters[i]");
        }

        clusters[i]->size = 3; // Exemple de taille
        clusters[i]->centroide.dim = 2;
        clusters[i]->centroide.coords = malloc(2 * sizeof(int64_t));
        if (clusters[i]->centroide.coords == NULL) {
            // Si l'allocation échoue, on libère les allocations précédentes et on arrête le test
            for (uint32_t j = 0; j < i; ++j) {
                free(clusters[j]->centroide.coords);
                free(clusters[j]);
            }
            free(clusters);
            CU_FAIL_FATAL("Allocation échouée pour clusters[i]->centroide.coords");
        }

        clusters[i]->centroide.coords[0] = i * 10;
        clusters[i]->centroide.coords[1] = i * 10 + 1;
        clusters[i]->data = malloc(clusters[i]->size * sizeof(point_t *));
        if (clusters[i]->data == NULL) {
            // Si l'allocation échoue, on libère les allocations précédentes et on arrête le test
            free(clusters[i]->centroide.coords);
            for (uint32_t j = 0; j < i; ++j) {
                free(clusters[j]->data);
                free(clusters[j]->centroide.coords);
                free(clusters[j]);
            }
            free(clusters);
            CU_FAIL_FATAL("Allocation échouée pour clusters[i]->data");
        }

        for (uint64_t j = 0; j < clusters[i]->size; ++j) {
            clusters[i]->data[j] = malloc(sizeof(point_t));
            if (clusters[i]->data[j] == NULL) {
                // Si l'allocation échoue, on libère les allocations précédentes et on arrête le test
                for (uint64_t k = 0; k < j; ++k) {
                    free(clusters[i]->data[k]);
                }
                free(clusters[i]->data);
                free(clusters[i]->centroide.coords);
                for (uint32_t l = 0; l < i; ++l) {
                    for (uint64_t m = 0; m < clusters[l]->size; ++m) {
                        free(clusters[l]->data[m]->coords);
                        free(clusters[l]->data[m]);
                    }
                    free(clusters[l]->data);
                    free(clusters[l]->centroide.coords);
                    free(clusters[l]);
                }
                free(clusters);
                CU_FAIL_FATAL("Allocation échouée pour clusters[i]->data[j]");
            }

            clusters[i]->data[j]->dim = 2;
            clusters[i]->data[j]->coords = malloc(2 * sizeof(int64_t));
            if (clusters[i]->data[j]->coords == NULL) {
                // Si l'allocation échoue, on libère les allocations précédentes et on arrête le test
                for (uint64_t k = 0; k < j; ++k) {
                    free(clusters[i]->data[k]->coords);
                    free(clusters[i]->data[k]);
                }
                free(clusters[i]->data);
                free(clusters[i]->centroide.coords);
                for (uint32_t l = 0; l < i; ++l) {
                    for (uint64_t m = 0; m < clusters[l]->size; ++m) {
                        free(clusters[l]->data[m]->coords);
                        free(clusters[l]->data[m]);
                    }
                    free(clusters[l]->data);
                    free(clusters[l]->centroide.coords);
                    free(clusters[l]);
                }
                free(clusters);
                CU_FAIL_FATAL("Allocation échouée pour clusters[i]->data[j]->coords");
            }

            clusters[i]->data[j]->coords[0] = i * 10 + j;
            clusters[i]->data[j]->coords[1] = i * 10 + j + 1;
        }
    }

    // Sauvegarde des coordonnées initiales des centroïdes
    int64_t initial_coords[k][2];
    for (uint32_t i = 0; i < k; ++i) {
        initial_coords[i][0] = clusters[i]->centroide.coords[0];
        initial_coords[i][1] = clusters[i]->centroide.coords[1];
    }

    // Application de la fonction update_centroids
    update_centroids(clusters, k);

    // Vérification si les centroïdes ont été mis à jour correctement
    for (uint32_t i = 0; i < k; ++i) {
        // Calcul de la moyenne des coordonnées des points dans le cluster
        int64_t avg_x = 0, avg_y = 0;
        for (uint64_t j = 0; j < clusters[i]->size; ++j) {
            avg_x += clusters[i]->data[j]->coords[0];
            avg_y += clusters[i]->data[j]->coords[1];
        }
        avg_x /= clusters[i]->size;
        avg_y /= clusters[i]->size;

        // Vérification des nouvelles coordonnées des centroïdes
        CU_ASSERT_EQUAL(clusters[i]->centroide.coords[0], avg_x);
        CU_ASSERT_EQUAL(clusters[i]->centroide.coords[1], avg_y);

        // Vérification que les coordonnées initiales ne sont pas modifiées
        CU_ASSERT_EQUAL(clusters[i]->centroide.coords[0], initial_coords[i][0]);
        CU_ASSERT_EQUAL(clusters[i]->centroide.coords[1], initial_coords[i][1]);
    }

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
    if ((NULL == CU_add_test(pSuite, "Test de la fonction update_centroids", test_update_centroids))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Configuration de l'affichage des résultats
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
