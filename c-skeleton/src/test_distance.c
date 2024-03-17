#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>

#include "../headers/binary_file_reader.h" // Inclure le bon en-tête
#include "../headers/distance.h" // Inclure si nécessaire
#include "../headers/point.h" // Inclure si nécessaire

void assert_equal_int64();
point_t* create_point(); 



// Fonction de comparaison pour les tests
void assert_equal_int64(int64_t expected, int64_t actual, const char *message) {
    if (expected == actual) {
        printf("%s : SUCCÈS\n", message);
    } else {
        printf("%s : ÉCHEC\n", message);
        printf("  Attendu : %ld\n", expected);
        printf("  Reçu : %ld\n", actual);
    }
}

// Crée un point de la dimension donnée et initialise ses coordonnées à zéro
point_t *create_point(uint32_t dim) {
    point_t *point = (point_t *)malloc(sizeof(point_t));
    if (point == NULL) {
        perror("Erreur d'allocation mémoire pour le point");
        return NULL;
    }

    point->dim = dim;
    point->coords = (int64_t *)calloc(dim, sizeof(int64_t));
    if (point->coords == NULL) {
        perror("Erreur d'allocation mémoire pour les coordonnées du point");
        free(point);
        return NULL;
    }

    return point;
}

int main() {
    // Création de deux points de dimension 3
    point_t *p1 = create_point(3);
    point_t *p2 = create_point(3);

    // Affectation des coordonnées
    p1->coords[0] = 1; p1->coords[1] = 2; p1->coords[2] = 3;
    p2->coords[0] = 4; p2->coords[1] = 5; p2->coords[2] = 6;

    // Test de la fonction squared_manhattan_distance
    int64_t expected_manhattan = 81; // (|1-4| + |2-5| + |3-6|)^2 = (3 + 3 + 3)**2 = 9**2 = 81
    int64_t result_manhattan = squared_manhattan_distance(p1, p2);
    assert_equal_int64(expected_manhattan, result_manhattan, "Test de la squared_manhattan_distance");

    // Test de la fonction squared_euclidean_dSistance
    int64_t expected_euclidean = 27; // (1-4)^2 + (2-5)^2 + (3-6)^2 = 3^2 + 3^2 + 3^2 = 9 + 9 + 9 = 27
    int64_t result_euclidean = squared_euclidean_distance(p1, p2);
    assert_equal_int64(expected_euclidean, result_euclidean, "Test de la squared_euclidean_distance");

    // Libération de la mémoire
    free(p1->coords);
    free(p1);
    free(p2->coords);
    free(p2);

    return 0;
}