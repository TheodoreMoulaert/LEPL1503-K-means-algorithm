
#include "../headers/point.h" // Inclure si nécessaire
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>




int assign_vectors_to_centroids(double **centroids, double ***clusters, int num_centroids, int num_vectors, int dimensions) {
    int i, j;
    int unchanged = 1;

    if (LOG) {
        fprintf(stderr, "\tAssign points to centroids\n");
    }

   
    double ***new_clusters = (double ***)malloc(num_centroids * sizeof(double **));
    if (new_clusters == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (i = 0; i < num_centroids; i++) {
        new_clusters[i] = (double **)malloc(/* Size of cluster */ * sizeof(double *));
        if (new_clusters[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
    }


    for (i = 0; i < num_centroids; i++) {
        for (j = 0; j < /* Size of cluster */; j++) {
            new_clusters[i][j] = (double *)malloc(dimensions * sizeof(double));
            if (new_clusters[i][j] == NULL) {
                fprintf(stderr, "Memory allocation failed\n");
                return 1;
            }
        }
    }


    for (i = 0; i < num_centroids; i++) {
        for (j = 0; j < /* Size of cluster */; j++) {
            /* Find the closest centroid for the vector */
            int closest_centroid_idx;
            double closest_centroid_distance = INFINITY;

            for (int centroid_idx = 0; centroid_idx < num_centroids; centroid_idx++) {
                double distance = distance_squared(clusters[i][j], centroids[centroid_idx], dimensions);

                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }

            /* Add the vector to the cluster of the closest centroid */
            if (LOG) {
                fprintf(stderr, "\t\t%s closest to %s (before %s)\n", clusters[i][j], centroids[closest_centroid_idx], centroids[i]);
            }
            /* Copy the vector to the new cluster */
            memcpy(new_clusters[closest_centroid_idx][j], clusters[i][j], dimensions * sizeof(double));

            /* Observe if the current vector changes its cluster */
            unchanged = unchanged && closest_centroid_idx == i;
        }
    }


    for (i = 0; i < num_centroids; i++) {
        for (j = 0; j < /* Size of cluster */; j++) {
            free(clusters[i][j]);
        }
        free(clusters[i]);
    }
    free(clusters);


    clusters = new_clusters;

    return !unchanged;
}
