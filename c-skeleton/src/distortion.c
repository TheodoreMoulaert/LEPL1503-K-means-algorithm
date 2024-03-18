uint64_t distortion(cluster_t *centroids, cluster_t **clusters, uint32_t num_clusters) {
        uint64_t current_sum = 0;
        for (uint32_t k = 0; k < num_clusters; ++k) {
            for (uint64_t j = 0; j < clusters[k]->size; ++j) {
                current_sum += DISTANCE_SQUARED;
            }
        }
        return current_sum;
}

