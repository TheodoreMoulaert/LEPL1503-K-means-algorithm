#ifndef K_MEANS_H
#define K_MEANS_H

#include <stdbool.h>

// Structure pour représenter un tuple
typedef struct {
    int x;
    int y;
} Tuple;

// Structure pour représenter une liste de tuples
typedef struct {
    Tuple *items;
    int length;
} TupleList;

// Fonction pour assigner les vecteurs aux centroids les plus proches
bool assign_vectors_to_centroids(TupleList centroids, TupleList *clusters);

// Fonction pour mettre à jour les centroids
TupleList update_centroids(TupleList *clusters);

// Fonction k_means
TupleList k_means(TupleList initial_centroids, int K);

#endif /* K_MEANS_H */
