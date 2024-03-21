bool assign_vectors_to_centroids(Cluster clusters[], int centroids[][MAX_DIMENSION], int dimension, int K, DistanceType distance_type) {
    bool unchanged = true;
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < clusters[k].size; i++) {
            int closest_centroid_idx = -1;
            int closest_distance = INT_MAX;
            for (int j = 0; j < K; j++) {
                int distance;
                if (distance_type == MANHATTAN) {
                    distance = manhattan_distance_squared(clusters[k].vectors[i], clusters[j].vectors[0], dimension);
                } else {
                    distance = euclidean_distance_squared(clusters[k].vectors[i], clusters[j].vectors[0], dimension);
                }
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest_centroid_idx = j;
                }
            }
            if (closest_centroid_idx != k) {
                unchanged = false;
            }
            clusters[closest_centroid_idx].vectors[clusters[closest_centroid_idx].size++] = clusters[k].vectors[i];
        }
    }
    return unchanged;
}
