#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <inttypes.h>
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
    // Initialisation du premier cluster
    clusters[0].size = 3;
    clusters[0].center.dim = 2;
    clusters[0].center.coords = malloc(2 * sizeof(int64_t));
    clusters[0].center.coords[0] = 0;
    clusters[0].center.coords[1] = 1;
    clusters[0].data = malloc(3 * sizeof(point_t));
    clusters[0].data[0].dim = 2;
    clusters[0].data[0].coords = malloc(2 * sizeof(int64_t));
    clusters[0].data[0].coords[0] = 0;
    clusters[0].data[0].coords[1] = 1;
    clusters[0].data[1].dim = 2;
    clusters[0].data[1].coords = malloc(2 * sizeof(int64_t));
    clusters[0].data[1].coords[0] = 1;
    clusters[0].data[1].coords[1] = 2;
    clusters[0].data[2].dim = 2;
    clusters[0].data[2].coords = malloc(2 * sizeof(int64_t));
    clusters[0].data[2].coords[0] = 2;
    clusters[0].data[2].coords[1] = 3;

    // Initialisation du deuxième cluster
    clusters[1].size = 3;
    clusters[1].center.dim = 2;
    clusters[1].center.coords = malloc(2 * sizeof(int64_t));
    clusters[1].center.coords[0] = 0;
    clusters[1].center.coords[1] = 1;
    clusters[1].data = malloc(3 * sizeof(point_t));
    clusters[1].data[0].dim = 2;
    clusters[1].data[0].coords = malloc(2 * sizeof(int64_t));
    clusters[1].data[0].coords[0] = 2;
    clusters[1].data[0].coords[1] = 1;
    clusters[1].data[1].dim = 2;
    clusters[1].data[1].coords = malloc(2 * sizeof(int64_t));
    clusters[1].data[1].coords[0] = 0;
    clusters[1].data[1].coords[1] = 2;
    clusters[1].data[2].dim = 2;
    clusters[1].data[2].coords = malloc(2 * sizeof(int64_t));
    clusters[1].data[2].coords[0] = 1;
    clusters[1].data[2].coords[1] = 1;

    // Appel de la fonction update_centroids pour obtenir les nouveaux centres des clusters
    cluster_t new_centroids = update_centroids(clusters, taille);
    printf("Nouveaux centroïdes :\n");
    for (uint32_t i = 0; i < new_centroids.size; i++) {
        printf("Centroïde %u : (", i);
        for (uint32_t j = 0; j < new_centroids.data[i].dim; j++) {
            printf("%" PRId64, new_centroids.data[i].coords[j]);
            if (j < new_centroids.data[i].dim - 1) {
                printf(", ");
            }
        }
        printf(")\n");
    }

    // Appel de la fonction distortion avec les nouveaux centres des clusters
    squared_distance_func_t dummy_func = squared_euclidean_distance;
    uint64_t result = distortion(clusters, taille, dummy_func);
    printf("Résultat de la fonction distortion : %lu\n", result);

    // Valeur attendue en fonction des données de test
    uint64_t expected_result = 7; // Pour chaque cluster, la somme des carrés des différences entre les coordonnées des points et du centre est 0 + 1*1 + 2*2 = 5. Comme il y a deux clusters, la distorsion totale est 2 * 5 = 10.

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
