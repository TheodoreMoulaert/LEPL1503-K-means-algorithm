#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"

int main() {
    // Define sample points and clusters
    point_t point1 = {2, (int64_t[]){1, 2}};
    point_t point2 = {2, (int64_t[]){3, 4}};
    point_t point3 = {2, (int64_t[]){5, 6}};
    point_t point4 = {2, (int64_t[]){7, 8}};

    cluster_t clusters[2]; // Assuming 2 clusters
    cluster_t centroids[2]; // Assuming 2 centroids

    // Initialize clusters with sample points
    clusters[0].size = 2;
    clusters[0].data = (point_t[]) {point1, point2};

    clusters[1].size = 2;
    clusters[1].data = (point_t[]) {point3, point4};

    // Print initial assignments
    printf("Initial Assignments:\n");
    printf("Cluster 0:\n");
    for (uint32_t i = 0; i < clusters[0].size; i++) {
        printf("(%ld, %ld) ", clusters[0].data[i].coords[0], clusters[0].data[i].coords[1]);
    }
    printf("\n");

    printf("Cluster 1:\n");
    for (uint32_t i = 0; i < clusters[1].size; i++) {
        printf("(%ld, %ld) ", clusters[1].data[i].coords[0], clusters[1].data[i].coords[1]);
    }
    printf("\n");

    // Call the function to assign vectors to centroids
    uint64_t unchanged = assign_vector_to_centroids(centroids, clusters, 2, squared_euclidean_distance);

    // Print assignments after function call
    printf("\nAssignments after assign_vectors_to_centroids function call:\n");
    printf("Cluster 0:\n");
    for (uint32_t i = 0; i < clusters[0].size; i++) {
        printf("(%ld, %ld) ", clusters[0].data[i].coords[0], clusters[0].data[i].coords[1]);
    }
    printf("\n");

    printf("Cluster 1:\n");
    for (uint32_t i = 0; i < clusters[1].size; i++) {
        printf("(%ld, %ld) ", clusters[1].data[i].coords[0], clusters[1].data[i].coords[1]);
    }
    printf("\n");

    // Validate if the assignment remains unchanged
    if (unchanged) {
        printf("\nAssignment remains unchanged.\n");
    } else {
        printf("\nAssignment changed.\n");
    }

    return 0;
}
