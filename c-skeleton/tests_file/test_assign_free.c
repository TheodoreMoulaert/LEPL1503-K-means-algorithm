#include <CUnit/Basic.h>
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"
#include "../headers/cluster.h"

// Define your test cases here

void print_clusters(cluster_t **clusters, uint32_t K) {
    printf("Clusters:\n");
    for (uint32_t i = 0; i < K; ++i) {
        printf("Cluster %d:\n", i);
        for (uint32_t j = 0; j < clusters[i]->size; ++j) {
            printf("Point %d: (", j);
            for (uint32_t k = 0; k < clusters[i]->data[j]->dim; ++k) {
                printf("%lu", clusters[i]->data[j]->coords[k]);
                if (k < clusters[i]->data[j]->dim - 1) {
                    printf(", ");
                }
            }
            printf(")\n");
        }
    }
}

void test_assign_vectors_to_centroids() {
    // Create test data
    uint32_t K = 2; // Number of centroids
    uint32_t dim = 2; // Dimension of the points
    point_t centroids[K];
    centroids[0].dim = dim;
    centroids[0].coords = (uint64_t *)malloc(dim * sizeof(uint64_t));
    centroids[0].coords[0] = 4;
    centroids[0].coords[1] = 2;
    centroids[1].dim = dim;
    centroids[1].coords = (uint64_t *)malloc(dim * sizeof(uint64_t));
    centroids[1].coords[0] = 2;
    centroids[1].coords[1] = 0;

    cluster_t **clusters = (cluster_t **)malloc(K * sizeof(cluster_t *));
    for (uint32_t i = 0; i < K; ++i) {
        clusters[i] = (cluster_t *)malloc(sizeof(cluster_t));
        clusters[i]->size = 3;
        clusters[i]->data = (point_t **)malloc(3 * sizeof(point_t *));
        for (uint32_t j = 0; j < 3; ++j) {
            clusters[i]->data[j] = (point_t *)malloc(sizeof(point_t));
            clusters[i]->data[j]->dim = dim;
            clusters[i]->data[j]->coords = (uint64_t *)malloc(dim * sizeof(uint64_t));
            // Assign some random coordinates for testing
            clusters[i]->data[j]->coords[0] = rand() % 5;
            clusters[i]->data[j]->coords[1] = rand() % 5;
        }
    }

    // Print clusters before assignment
    printf("Clusters before assignment:\n");
    print_clusters(clusters, K);

    // Call the function to be tested
    result_t result = assign_vectors_to_centroides(centroids, clusters, K, squared_euclidean_distance);

    // Print clusters after assignment
    printf("\nClusters after assignment:\n");
    print_clusters(result.result_cluster, K);

    // Assert statements to check the result
    CU_ASSERT_EQUAL(result.changes, true); // Assuming there should be changes after assigning vectors

    // Free dynamically allocated memory
    for (uint32_t i = 0; i < K; ++i) {
        for (uint32_t j = 0; j < 3; ++j) {
            free(clusters[i]->data[j]->coords);
            free(clusters[i]->data[j]);
        }
        free(clusters[i]->data);
        free(clusters[i]);
        free(centroids[i].coords);
    }
    free(clusters);
}

int main() {
    // Initialize CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add a suite to the registry
    CU_pSuite pSuite = CU_add_suite("Suite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test case to the suite
    if ((NULL == CU_add_test(pSuite, "test_assign_vectors_to_centroids", test_assign_vectors_to_centroids))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run the tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
