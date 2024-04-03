#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_distortion() {
    // initiation
    uint32_t k = 2; 

    // construction d'un cluster
    cluster_t *clusters = malloc(k * sizeof(cluster_t));
    for (uint32_t i = 0; i < k; ++i) {
        clusters[i].size = 3; // Example size
        clusters[i].center.dim = 2;
        clusters[i].center.coords = malloc(2 * sizeof(int64_t));
        clusters[i].center.coords[0] = i * 10;
        clusters[i].center.coords[1] = i * 10 + 1;
        clusters[i].data = malloc(clusters[i].size * sizeof(point_t));
        for (uint64_t j = 0; j < clusters[i].size; ++j) {
            clusters[i].data[j].dim = 2;
            clusters[i].data[j].coords = malloc(2 * sizeof(int64_t));
            clusters[i].data[j].coords[0] = i * 10 + j;
            clusters[i].data[j].coords[1] = i * 10 + j + 1;
        }
    }

    // quelle distance on utilise pour les tests
    squared_distance_func_t dummy_func = squared_euclidean_distance;

    // on applique la fonction distortion
    uint64_t result = distortion(clusters, k, dummy_func);
    
    // la valeur que l'on devrait obtenir
    uint64_t expected_result = 20; 

    // on test si c'est bien égale
    CU_ASSERT_EQUAL(result, expected_result);

    // clean-up
    for (uint32_t i = 0; i < k; ++i) {
        free(clusters[i].center.coords);
        for (uint64_t j = 0; j < clusters[i].size; ++j) {
            free(clusters[i].data[j].coords);
        }
        free(clusters[i].data);
    }
    free(clusters);
}

int main() {
 
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

   
    CU_pSuite pSuite = CU_add_suite("Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }


    if ((NULL == CU_add_test(pSuite, "test of distortion function", test_distortion))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

  
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_error();
}
