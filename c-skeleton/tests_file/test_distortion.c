#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // For malloc
#include <math.h>   // For pow and sqrt

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h" 
#include "../headers/distortion.h"

#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>


// Test case initialization function
int init_suite(void) {
    return 0; // Return 0 for success
}

// Test case cleanup function
int clean_suite(void) {
    return 0; // Return 0 for success
}


// Function to test distortion function
void test_distortion() {
    // Initialize dummy data for testing
    uint32_t num_clusters = 2; // Number of clusters for testing
    cluster_t *centroids = malloc(num_clusters * sizeof(cluster_t)); // Allocate memory for centroids
    cluster_t **clusters = malloc(num_clusters * sizeof(cluster_t *)); // Allocate memory for clusters
    
    // Initialize centroids
    for (uint32_t i = 0; i < num_clusters; ++i) {
        centroids[i].center.dimension = 2; // Dimension for testing
        centroids[i].center.coordinates = malloc(2 * sizeof(int64_t)); // Allocate memory for coordinates
        
        // Assigning arbitrary coordinates for centroids for testing
        centroids[i].center.coordinates[0] = i * 10;
        centroids[i].center.coordinates[1] = i * 10 + 1;
    }
    
    // Initialize clusters
    for (uint32_t i = 0; i < num_clusters; ++i) {
        clusters[i] = malloc(sizeof(cluster_t)); // Allocate memory for cluster
        clusters[i]->surrounding = 3; // Example surrounding
        clusters[i]->data = malloc(clusters[i]->surrounding * sizeof(point_t)); // Allocate memory for data
        
        // Assigning arbitrary coordinates for cluster data for testing
        for (uint64_t j = 0; j < clusters[i]->surrounding; ++j) {
            clusters[i]->data[j].dimension = 2; // Dimension for testing
            clusters[i]->data[j].coordinates = malloc(2 * sizeof(int64_t)); // Allocate memory for coordinates
            
            // Assigning arbitrary coordinates for cluster data for testing
            clusters[i]->data[j].coordinates[0] = i * 10 + j;
            clusters[i]->data[j].coordinates[1] = i * 10 + j + 1;
        }
    }
    
    // Call distortion function
    uint64_t result = distortion(centroids, clusters, num_clusters);
    
    // Define expected result based on dummy data
    uint64_t expected_result = 0; // You need to set the expected result based on your dummy data
    
    // Check if the result matches the expected result
    CU_ASSERT_EQUAL(result, expected_result);
    
    // Free allocated memory
    for (uint32_t i = 0; i < num_clusters; ++i) {
        free(centroids[i].center.coordinates);
        for (uint64_t j = 0; j < clusters[i]->surrounding; ++j) {
            free(clusters[i]->data[j].coordinates);
        }
        free(clusters[i]->data);
        free(clusters[i]);
    }
    free(clusters);
    free(centroids);
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
