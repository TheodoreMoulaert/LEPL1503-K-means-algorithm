#include <stdio.h>
#include <stdbool.h>
#include "../headers/assign_vector_to_centro.h"

// Function to compare two arrays of points
bool compare_arrays(point_t arr1[], point_t arr2[], uint64_t size) {
    for (uint64_t i = 0; i < size; i++) {
        for (uint64_t j = 0; j < arr1[i].dim; j++) {
            if (arr1[i].coords[j] != arr2[i].coords[j]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    // Create sample cluster and centroid arrays
    cluster_t clusters[3];
    cluster_t centroids[2];

    // Initialize clusters and centroids with sample data
    // Note: This data initialization is just for testing purposes and may not represent actual cluster data
    point_t cluster1_data[] = {{{1, {1, 2}}}, {{2, {3, 4}}}};
    point_t cluster2_data[] = {{{1, {5, 6}}}, {{2, {7, 8}}}, {{3, {9, 10}}}};
    point_t cluster3_data[] = {{{1, {11, 12}}}, {{2, {13, 14}}}, {{3, {15, 16}}}, {{4, {17, 18}}}};
    point_t centroid1_data[] = {{{2, {1, 1}}}, {{2, {2, 2}}}};
    point_t centroid2_data[] = {{{2, {10, 10}}}, {{2, {12, 12}}}};


    clusters[0].size = 2;
    clusters[0].data = cluster1_data;
    clusters[1].size = 3;
    clusters[1].data = cluster2_data;
    clusters[2].size = 4;
    clusters[2].data = cluster3_data;

    centroids[0].size = 0;
    centroids[0].data = centroid1_data;
    centroids[1].size = 0;
    centroids[1].data = centroid2_data;

    // Call the function to assign vectors to centroids
    bool result = assign_vectors_to_centroids(clusters, centroids, 2, squared_euclidean_distance);

    // Print the result
    if (result) {
        printf("Vectors are already assigned to centroids.\n");
    } else {
        printf("Vectors have been reassigned to centroids.\n");
    }

    // Print the updated centroids
    printf("Updated centroids:\n");
    for (int i = 0; i < 2; i++) {
        printf("Centroid %d:\n", i + 1);
        for (int j = 0; j < centroids[i].size; j++) {
            printf("(%" PRId64 ", %" PRId64 ")\n", centroids[i].data[j].coords[0], centroids[i].data[j].coords[1]);
        }
    }

    return 0;
}
