#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>  // Include stdlib.h for realloc function

#include "../headers/point.h"  // Include point.h for point_t definition
#include "../headers/cluster.h" 
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"

int main() {
    // Define sample points for clusters
    point_t cluster_point1 = {2, (int64_t[]){1, 2}};
    point_t cluster_point2 = {2, (int64_t[]){3, 4}};
    point_t cluster_point3 = {2, (int64_t[]){5, 6}};
    point_t cluster_point4 = {2, (int64_t[]){7, 8}};

    // Initialize clusters with sample points
    cluster_t clusters[2]; // Assuming 2 clusters
    clusters[0].size = 2;
    clusters[0].data = (point_t[]) {cluster_point1, cluster_point2};
    clusters[1].size = 2;
    clusters[1].data = (point_t[]) {cluster_point3, cluster_point4};

    // Define sample points for centroids
    point_t centroid_point1 = {2, (int64_t[]){10, 20}}; // Sample centroid point 1
    point_t centroid_point2 = {2, (int64_t[]){30, 40}}; // Sample centroid point 2

    // Initialize centroids with sample points
    cluster_t centroids[2];
    centroids[0].size = 1; // Assuming 1 point in centroid 0
    centroids[0].data = &centroid_point1;
    centroids[1].size = 1; // Assuming 1 point in centroid 1
    centroids[1].data = &centroid_point2;

    // Print initial assignments
    printf("Initial Assignments:\n");
    for (uint32_t i = 0; i < 2; i++) {
        printf("Cluster %d:\n", i);
        for (uint32_t j = 0; j < clusters[i].size; j++) {
            printf("(%ld, %ld) ", clusters[i].data[j].coords[0], clusters[i].data[j].coords[1]);
        }
        printf("\n");
    }

    // Call the function to assign vectors to centroids
    int unchanged = assign_vector_to_centroids(centroids, clusters, 2, squared_euclidean_distance);

    // Print assignments after function call
    printf("\nAssignments after assign_vectors_to_centroids function call:\n");
    for (uint32_t i = 0; i < 2; i++) {
        printf("Cluster %d:\n", i);
        for (uint32_t j = 0; j < clusters[i].size; j++) {
            printf("(%ld, %ld) ", clusters[i].data[j].coords[0], clusters[i].data[j].coords[1]);
        }
        printf("\n");
    }

    // Validate if the assignment remains unchanged
    if (unchanged) {
        printf("\nAssignment remains unchanged.\n");
    } else {
        printf("\nAssignment changed.\n");
    }

    // Free memory if dynamically allocated

    return 0;
}
// gcc -o test tests_file/test_assign_vector_to_centro.c src/assign_vector_to_centro.c src/distance.c -Icunit
// ./test