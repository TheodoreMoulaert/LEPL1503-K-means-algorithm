#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include "../headers/distortion.h"

// Function to initialize test suite
int init_suite(void) {
    return 0;
}

// Function to clean up test suite
int clean_suite(void) {
    return 0;
}

// Test case for distortion function
// Test case for distortion function
void test_distortion() {
    // Define dummy data for testing
    uint32_t k = 2; // Number of clusters
    cluster_t **clusters = malloc(k * sizeof(cluster_t *));
    for (uint32_t i = 0; i < k; ++i) {
        clusters[i] = malloc(sizeof(cluster_t));
        clusters[i]->size = 3; // Example size
        clusters[i]->center.dim = 2;
        clusters[i]->center.coords = malloc(2 * sizeof(int64_t));
        clusters[i]->center.coords[0] = i * 10;
        clusters[i]->center.coords[1] = i * 10 + 1;
        clusters[i]->data = malloc(clusters[i]->size * sizeof(point_t));
        for (uint64_t j = 0; j < clusters[i]->size; ++j) {
            clusters[i]->data[j].dim = 2;
            clusters[i]->data[j].coords = malloc(2 * sizeof(int64_t));
            clusters[i]->data[j].coords[0] = i * 10 + j;
            clusters[i]->data[j].coords[1] = i * 10 + j + 1;
        }
    }

    // quelle distance on utilise pour les tests
    squared_distance_func_t dummy_func = squared_euclidean_distance;


    uint64_t result = distortion((cluster_t const **)clusters, k, dummy_func);
    printf("Result of distortion function: %lu\n", result);

  
    uint64_t expected_result = 20; 

    CU_ASSERT_EQUAL(result, expected_result);

    // cleean avec free
    for (uint32_t i = 0; i < k; ++i) {
        free(clusters[i]->center.coords);
        for (uint64_t j = 0; j < clusters[i]->size; ++j) {
            free(clusters[i]->data[j].coords);
        }
        free(clusters[i]->data);
        free(clusters[i]);
    }
    free(clusters);
}



// Main function to set up test suite and run tests
int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add a suite to the registry
    CU_pSuite pSuite = CU_add_suite("Suite", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test function to the suite
    if ((NULL == CU_add_test(pSuite, "test of distortion function", test_distortion))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run the tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    
    return CU_get_error();
}
