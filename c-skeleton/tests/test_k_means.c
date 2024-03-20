#include <stdio.h>
#include <assert.h>
#include "../headers/k_means.h"
#include "../headers/point.h"

// Fonction pour comparer deux points
void assert_equal_point(point_t expected, point_t actual, const char *message) {
    assert(expected.dim == actual.dim);
    for (uint32_t i = 0; i < expected.dim; i++) {
        assert(expected.coords[i] == actual.coords[i]);
    }
    printf("%s: Passed\n", message);
}

int main() {
    // Définition des centroids initiaux
    double initial_centroids_data[][3] = {
        {2.0, 3.0, 4.0},
        {4.0, 5.0, 6.0},
        {6.0, 7.0, 8.0}
    };
    point_t initial_centroids[3];
    for (int i = 0; i < 3; i++) {
        initial_centroids[i].dim = 3;
        initial_centroids[i].coords = initial_centroids_data[i];
    }

    // Définition des données à segmenter (vectors)
    double vectors_data[][3] = {
        {1.0, 2.0, 3.0},
        {3.0, 4.0, 5.0},
        {5.0, 6.0, 7.0},
        {7.0, 8.0, 9.0},
        {9.0, 10.0, 11.0}
    };
    point_t *vectors[5];
    for (int i = 0; i < 5; i++) {
        vectors[i] = malloc(sizeof(point_t));
        vectors[i]->dim = 3;
        vectors[i]->coords = vectors_data[i];
    }

    // Appel de la fonction k_means
    point_t *final_centroids = k_means(initial_centroids, 3, vectors, 5, 3);

    // Définition des centroids finaux attendus
    double expected_centroids_data[][3] = {
        {2.0, 3.0, 4.0},
        {4.0, 5.0, 6.0},
        {6.0, 7.0, 8.0}
    };
    point_t expected_centroids[3];
    for (int i = 0; i < 3; i++) {
        expected_centroids[i].dim = 3;
        expected_centroids[i].coords = expected_centroids_data[i];
    }

    // Comparaison des centroids finaux obtenus avec ceux attendus
    for (int i = 0; i < 3; i++) {
        assert_equal_point(expected_centroids[i], final_centroids[i], "Test centroid");
    }

    return 0;
}
