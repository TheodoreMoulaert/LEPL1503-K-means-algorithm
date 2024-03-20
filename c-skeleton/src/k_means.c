TupleList k_means(TupleList initial_centroids, int K) {
    // Implémentation de la fonction k_means
    TupleList centroids = initial_centroids;
    TupleList clusters[K];

    // Initialisation des clusters
    for (int i = 0; i < K; i++) {
        clusters[i].items = NULL;
        clusters[i].length = 0;
    }
    clusters[0] = vectors; // Suppose que vectors est une variable contenant les données à segmenter

    bool changed = true;
    while (changed) {
        changed = assign_vectors_to_centroids(centroids, clusters);
        centroids = update_centroids(clusters);
    }

    return centroids;
}
