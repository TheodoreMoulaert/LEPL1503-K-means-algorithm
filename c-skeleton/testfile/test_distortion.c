#include <stdio.h>
#include <stdint.h>
#include <stdlib.h> // For malloc
#include <math.h>   // For pow and sqrt

// Definition of point_t structure
typedef struct {
    int64_t *coordinates;
    uint32_t dimension;
} point_t;

// Definition of cluster_t structure
typedef struct {
    point_t center;
    uint64_t surrounding;
    point_t *data;
} cluster_t;

// Function to calculate squared distance between two points
uint64_t distance_squared(point_t p1, point_t p2) {
    uint64_t sum = 0;
    for (uint32_t i = 0; i < p1.dimension; ++i) {
        sum += pow(p1.coordinates[i] - p2.coordinates[i], 2);
    }
    return sum;
}

// Function to calculate distortion
uint64_t distortion(cluster_t *centroids, cluster_t **clusters, uint32_t num_clusters) {
    uint64_t current_sum = 0;
    for (uint32_t k = 0; k < num_clusters; ++k) {
        for (uint64_t j = 0; j < clusters[k]->surrounding; ++j) {
            current_sum += distance_squared(clusters[k]->data[j], centroids[k].center);
        }
    }
    return current_sum;
}

// Function to test distortion function
void test_distortion() {
    uint32_t num_clusters = 2; // Number of clusters for testing
    cluster_t *centroids = malloc(num_clusters * sizeof(cluster_t)); // Allocate memory for centroids
    cluster_t **clusters = malloc(num_clusters * sizeof(cluster_t *)); // Allocate memory for clusters
    
    // Initialize centroids and clusters with some data for testing
    for (uint32_t i = 0; i < num_clusters; ++i) {
        centroids[i].center.dimension = 2; // Dimension for testing
        centroids[i].center.coordinates = malloc(2 * sizeof(int64_t)); // Allocate memory for coordinates
        
        // Assigning some arbitrary coordinates for centroids for testing
        centroids[i].center.coordinates[0] = i * 10;
        centroids[i].center.coordinates[1] = i * 10 + 1;
        
        // Initializing surrounding and data for clusters for testing
        clusters[i] = malloc(sizeof(cluster_t)); // Allocate memory for cluster
        clusters[i]->surrounding = 3; // Example surrounding
        clusters[i]->data = malloc(clusters[i]->surrounding * sizeof(point_t)); // Allocate memory for data
        
        // Assigning some arbitrary coordinates for cluster data for testing
        for (uint64_t j = 0; j < clusters[i]->surrounding; ++j) {
            clusters[i]->data[j].dimension = 2; // Dimension for testing
            clusters[i]->data[j].coordinates = malloc(2 * sizeof(int64_t)); // Allocate memory for coordinates
            
            // Assigning some arbitrary coordinates for cluster data for testing
            clusters[i]->data[j].coordinates[0] = i * 10 + j;
            clusters[i]->data[j].coordinates[1] = i * 10 + j + 1;
        }
    }
    
    // Call distortion function for testing
    uint64_t result = distortion(centroids, clusters, num_clusters);
    
    // Output the result
    printf("Distortion Test Result: %lu\n", result);
    
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

int main() {
    // Call test function
    test_distortion();
    return 0;
}
