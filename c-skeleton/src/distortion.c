<<<<<<< HEAD
uint64_t distortion(cluster_t *centroids, cluster_t **clusters, uint32_t num_clusters, squared_distance_func_t DISTANCE_SQUARED) {
=======
<<<<<<< HEAD
uint64_t distortion(cluster_t *centroids, cluster_t **clusters, uint32_t num_clusters) {
>>>>>>> d1d4e2d (test)
        uint64_t current_sum = 0;
        for (uint32_t k = 0; k < num_clusters; ++k) {
            for (uint64_t j = 0; j < clusters[k]->size; ++j) {
                current_sum += DISTANCE_SQUARED(clusters[k]->data[j], centroids[k].center);
            }
        }
        return current_sum;
}

=======
uint64_t distortion(cluster_t *centroids, cluster_t **clusters, uint32_t num_clusters) {
        uint64_t current_sum = 0;
        for (uint32_t k = 0; k < num_clusters; ++k) {
            for (uint64_t j = 0; j < clusters[k]->size; ++j) {
                current_sum += DISTANCE_SQUARED;
            }
        }
        return current_sum;
}

>>>>>>> 6adfe45 (test)
