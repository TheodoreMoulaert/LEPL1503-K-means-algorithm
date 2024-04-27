#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <assert.h>
#include <inttypes.h>
#include "../headers/assign3.h"

// Mock function for squared distance calculation
int64_t mock_distance_func(const point_t *p1, const point_t *p2) {
    // Simple mock implementation: Euclidean distance squared
    int64_t distance = 0;
    for (uint32_t i = 0; i < p1->dim; i++) {
        int64_t diff = p1->coords[i] - p2->coords[i];
        distance += diff * diff;
    }
    return distance;
}

int main() {
    // Define sample data
    point_t p1 = {3, {1, 2, 3}};
    point_t p2 = {3, {4, 5, 6}};
    point_t p3 = {3, {7, 8, 9}};
    point_t *points[] = {&p1, &p2, &p3};
    uint64_t num_points = 3;

    point_t centroid1 = {3, {0, 0, 0}};
    point_t centroid2 = {3, {10, 10, 10}};
    cluster_t cluster1 = {centroid1, NULL, 0};
    cluster_t cluster2 = {centroid2, NULL, 0};
    cluster_t *clusters[] = {&cluster1, &cluster2};
    uint32_t num_clusters = 2;

    // Array to store cluster index for each point
    int point_cluster_indices[] = {0, 0, 0}; // Initially, all points are assigned to cluster 0

    // Test the function
    bool changed = assign_points_to_clusters(points, clusters, num_points, num_clusters, point_cluster_indices, mock_distance_func);

    // Assert that at least one point's cluster assignment has changed
    assert(changed == true);

    // Print the new cluster assignments
    printf("New cluster assignments:\n");
    for (uint64_t i = 0; i < num_points; i++) {
        printf("Point %" PRIu64 " is assigned to cluster %" PRId32 "\n", i, point_cluster_indices[i]);
    }

    return 0;
}
