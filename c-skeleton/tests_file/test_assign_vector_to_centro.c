#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/assign_vector_to_centro.h"

// Function to print centroids
void print_centroids(const char* title, point_t centroids[], int num_centroids) {
    printf("%s:\n", title);
    for (int i = 0; i < num_centroids; ++i) {
        printf("Centroid %d: (%ld, %ld)\n", i, centroids[i].coords[0], centroids[i].coords[1]);
    }
}

// Function to print cluster points
void print_clusters(const char* title, cluster_t **clusters, uint64_t nbr_vectors, uint32_t K) {
    printf("%s:\n", title);
    for (int i = 0; i < K; ++i) {
        printf("Cluster %d:\n", i);
        for (int j = 0; j < clusters[i]->size; ++j) {
            printf("Point %d: (%ld, %ld)\n", j, clusters[i]->data[j]->coords[0], clusters[i]->data[j]->coords[1]);
        }
    }
}

// Test case for assign_vectors_to_centroids
void test_assign_vectors_to_centroids() {
    // Define centroids
    point_t centroids[2];
    centroids[0].coords = malloc(2 * sizeof(int64_t));
    centroids[0].coords[0] = 4;
    centroids[0].coords[1] = 2;
    centroids[0].dim = 2; 

    centroids[1].coords = malloc(2 * sizeof(int64_t));
    centroids[1].coords[0] = 2;
    centroids[1].coords[1] = 0;
    centroids[1].dim = 2; 

    // Define clusters
    cluster_t *cluster1 = (cluster_t*) malloc(sizeof(cluster_t));
    cluster1->size = 3;
    cluster1->data = (point_t**) malloc(cluster1->size * sizeof(point_t *));
    for (int i = 0; i < 3; ++i) {
        cluster1->data[i] = (point_t*) malloc(sizeof(point_t));
        cluster1->data[i]->dim = 2;
        cluster1->data[i]->coords = (int64_t*) malloc(2 * sizeof(int64_t));
        cluster1->data[i]->coords[0] = i;
        cluster1->data[i]->coords[1] = i + 1;
    }

    cluster_t *cluster2 = (cluster_t*) malloc(sizeof(cluster_t));
    cluster2->size = 3;
    cluster2->data = (point_t**) malloc(cluster2->size * sizeof(point_t *));
    for (int i = 0; i < 3; ++i) {
        cluster2->data[i] = (point_t*) malloc(sizeof(point_t));
        cluster2->data[i]->dim = 2;
        cluster2->data[i]->coords = (int64_t*) malloc(2 * sizeof(int64_t));
        cluster2->data[i]->coords[0] = i + 1;
        cluster2->data[i]->coords[1] = i + 2;
    }

    cluster_t **clusters = (cluster_t**) malloc(2 * sizeof(cluster_t *));
    for (int i = 0; i < 2; ++i) {
        clusters[i] = (cluster_t*) malloc(sizeof(cluster_t));
    }
    clusters[0] = cluster1;
    clusters[1] = cluster2;

    // Print centroids and clusters before assignment
    print_centroids("Centroids", centroids, 2);
    print_clusters("Clusters", clusters, 3, 2);

    // Perform the assignment
    cluster_t **new_clusters = assign_vectors_to_centroides(centroids, clusters, 2, squared_euclidean_distance);
    // Print centroids and clusters after assignment
    print_centroids("Centroids", centroids, 2);
    print_clusters("Clusters", new_clusters, 3, 2); // Printing new_clusters

    for (uint32_t i = 0; i < 2; ++i) {
        free(clusters[i]->data);
        free(clusters[i]);
    }
    free(clusters);

    for (int i = 0; i < 2; ++i) {
        free(centroids[i].coords);
    }
    for (int i = 0; i < 3; ++i) {
        free(new_clusters[0]->data[i]->coords); 
        free(new_clusters[0]->data[i]) ;
        free(new_clusters[1]->data[i]->coords); 
        free(new_clusters[1]->data[i]) ;
 
    }
    free(new_clusters[0]);
    free(new_clusters[1]);
    free(new_clusters);
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

