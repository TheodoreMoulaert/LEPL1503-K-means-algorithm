#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"

void test_update_centroids() {
    // Création de clusters factices pour le test
    cluster_list clusters;
    clusters.size = 3; // Nombre de clusters
    clusters.data = (cluster_t*)malloc(clusters.size * sizeof(cluster_t));
    
    // Initialisation des clusters factices
    for (uint32_t k = 0; k < clusters.size; k++) {
        clusters.data[k].size = 3; // Nombre de points dans chaque cluster
        clusters.data[k].data = (point_t*)malloc(clusters.data[k].size * sizeof(point_t));
        for (uint32_t i = 0; i < clusters.data[k].size; i++) {
            clusters.data[k].data[i].dim = 2; // Nombre de dimensions des points
            clusters.data[k].data[i].coords = (int64_t*)malloc(2 * sizeof(int64_t));
            clusters.data[k].data[i].coords[0] = i; // Valeurs arbitraires pour les coordonnées
            clusters.data[k].data[i].coords[1] = i + 1;
        }
    }
    
    // Appel de la fonction à tester
    cluster_t centroids = update_centroids(&clusters, clusters.size);
    
    // Vérification des résultats
    CU_ASSERT_EQUAL(centroids.size, clusters.size); // Vérifie si le nombre de centroids est correct
    
    // Vérifie si les coordonnées des centroids sont correctes
    for (uint32_t k = 0; k < centroids.size; k++) {
        for (uint32_t j = 0; j < centroids.data[k].dim; j++) {
            CU_ASSERT_EQUAL(centroids.data[k].coords[j], j); // Comparaison avec les valeurs arbitraires
        }
    }
    
    // Libération de la mémoire
    for (uint32_t k = 0; k < clusters.size; k++) {
        for (uint32_t i = 0; i < clusters.data[k].size; i++) {
            free(clusters.data[k].data[i].coords);
        }
        free(clusters.data[k].data);
    }
    free(clusters.data);
    for (uint32_t k = 0; k < centroids.size; k++) {
        free(centroids.data[k].coords);
    }
    free(centroids.data);
}

int main() {
    // Initialisation du registre des tests
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Ajout de la suite de tests
    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("Suite de tests pour update_centroids", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ajout du test à la suite
    if ((NULL == CU_add_test(pSuite, "test_update_centroids", test_update_centroids))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Exécution des tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}