int assign_vectors_to_centroids(double **centroids, double ***clusters, int num_centroids, int num_vectors, int dimensions) {
    int i, j;
    int unchanged = 1;

    if (LOG) {
        fprintf(stderr, "\tAssign points to centroids\n");
    }

    for (i = 0; i < num_centroids; i++) {
        for (j = 0; j < /* Size of cluster */; j++) {
            int closest_centroid_idx;
            double closest_centroid_distance = INFINITY;

            for (int centroid_idx = 0; centroid_idx < num_centroids; centroid_idx++) {
                double distance = distance_squared(clusters[i][j], centroids[centroid_idx], dimensions);

                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }

            if (LOG) {
                fprintf(stderr, "\t\t%s closest to %s (before %s)\n", clusters[i][j], centroids[closest_centroid_idx], centroids[i]);
            }
            
            memcpy(new_clusters[closest_centroid_idx][j], clusters[i][j], dimensions * sizeof(double));

            
            unchanged = unchanged && closest_centroid_idx == i;
        }
    }
}

    

    
