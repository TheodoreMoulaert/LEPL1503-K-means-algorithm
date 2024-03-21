#include <stdio.h>
#include <stdlib.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <limits.h> // For INT_MAX

// Include your headers here
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h" 
#include "../headers/cluster.h" 

// Mock distance functions for testing
int64_t squared_manhattan_distance(const int64_t *vector1, const int64_t *vector2, int64_t dimension) {
    
    return 0; // Return 0 for testing purposes
}

int64_t squared_euclidean_distance(const int64_t *vector1, const int64_t *vector2, int64_t dimension) {
    
    return 0; // Return 0 for testing purposes
}

// Test case for assign_vectors_to_centroids function
void test_assign_vectors_to_centroids() {
    // Create sample clusters and centroids
    cluster_t clusters[3]; 
    cluster_t centroids[2]; 



    // Call the function
    bool unchanged = assign_vectors_to_centroids(clusters, centroids, dimension, K, squared_manhattan_distance);

    // Check the result
    
    CU_ASSERT_TRUE(unchanged);

    
}

int main() {
   
    if (CU_initialize_registry() != CUE_SUCCESS) {
        return CU_get_error();
    }

  
    CU_pSuite suite = CU_add_suite("assign_vectors_to_centroids_tests", NULL, NULL);
    if (suite == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    
    if (CU_add_test(suite, "test_assign_vectors_to_centroids", test_assign_vectors_to_centroids) == NULL) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    /
    CU_basic_set_mode(CU_BRM_VERBOSE);

  
    CU_basic_run_tests();

    
    CU_cleanup_registry();
    return CU_get_error();
}
