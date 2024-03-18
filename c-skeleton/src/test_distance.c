#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>


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
    point_t *p3 = create_point(4);
    point_t *p4 = create_point(4);
    point_t *p5 = create_point(5);
    point_t *p6 = create_point(5);

    // Affectation des coordonnées pour les points p1 et p2
    p1->coords[0] = 1; p1->coords[1] = 2; p1->coords[2] = 3;
    p2->coords[0] = 4; p2->coords[1] = 5; p2->coords[2] = 6;

    // Affectation des coordonnées pour les points p3 et p4
    p3->coords[0] = 10; p3->coords[1] = 20; p3->coords[2] = 30; p3->coords[3] = 40;
    p4->coords[0] = 40; p4->coords[1] = 50; p4->coords[2] = 60; p4->coords[3] = 70;

    // Affectation des coordonnées pour les points p5 et p6
    p5->coords[0] = -1; p5->coords[1] = -2; p5->coords[2] = -3; p5->coords[3] = -4; p5->coords[4] = -5;
    p6->coords[0] = -4; p6->coords[1] = -5; p6->coords[2] = -6; p6->coords[3] = -7; p6->coords[4] = -8;

    // Test de la fonction squared_manhattan_distance pour les points p1 et p2
    int64_t expected_manhattan_1_2 = 81; // (|1-4| + |2-5| + |3-6|)^2 = (3 + 3 + 3)**2 = 9**2 = 81
    int64_t result_manhattan_1_2 = squared_manhattan_distance(p1, p2);
    assert_equal_int64(expected_manhattan_1_2, result_manhattan_1_2, "Test de la squared_manhattan_distance pour p1 et p2");

    // Test de la fonction squared_euclidean_distance pour les points p1 et p2
    int64_t expected_euclidean_1_2 = 27; // (1-4)^2 + (2-5)^2 + (3-6)^2 = 3^2 + 3^2 + 3^2 = 9 + 9 + 9 = 27
    int64_t result_euclidean_1_2 = squared_euclidean_distance(p1, p2);
    assert_equal_int64(expected_euclidean_1_2, result_euclidean_1_2, "Test de la squared_euclidean_distance pour p1 et p2");

    // Test de la fonction squared_manhattan_distance pour les points p3 et p4
    int64_t expected_manhattan_3_4 = 14400; // (|10-40| + |20-50| + |30-60| + |40-70|)^2 = (30 + 30 + 30 + 30)**2 = 120**2 = 14400
    int64_t result_manhattan_3_4 = squared_manhattan_distance(p3, p4);
    assert_equal_int64(expected_manhattan_3_4, result_manhattan_3_4, "Test de la squared_manhattan_distance pour p3 et p4");

    // Test de la fonction squared_euclidean_distance pour les points p3 et p4
    int64_t expected_euclidean_3_4 = 3600; // (10-40)^2 + (20-50)^2 + (30-60)^2 + (40-70)^2 = 30^2 + 30^2 + 30^2 + 30^2 = 900 + 900 + 900 + 900 = 3600
    int64_t result_euclidean_3_4 = squared_euclidean_distance(p3, p4);
    assert_equal_int64(expected_euclidean_3_4, result_euclidean_3_4, "Test de la squared_euclidean_distance pour p3 et p4");

    // Test de la fonction squared_manhattan_distance pour les points p5 et p6
    int64_t expected_manhattan_5_6 = 225; // (|-1-(-4)| + |-2-(-5)| + |-3-(-6)| + |-4-(-7)| + |-5-(-8)|)^2 = (3 + 3 + 3 + 3 + 3)**2 = 15**2 = 225
    int64_t result_manhattan_5_6 = squared_manhattan_distance(p5, p6);
    assert_equal_int64(expected_manhattan_5_6, result_manhattan_5_6, "Test de la squared_manhattan_distance pour p5 et p6");

    // Test de la fonction squared_euclidean_distance pour les points p5 et p6
    int64_t expected_euclidean_5_6 = 45; // (-1-(-4))^2 + (-2-(-5))^2 + (-3-(-6))^2 + (-4-(-7))^2 + (-5-(-8))^2 = 3^2 + 3^2 + 3^2 + 3^2 + 3^2 = 9 + 9 + 9 + 9 + 9 = 45
    int64_t result_euclidean_5_6 = squared_euclidean_distance(p5, p6);
    assert_equal_int64(expected_euclidean_5_6, result_euclidean_5_6, "Test de la squared_euclidean_distance pour p5 et p6");

    // Libération de la mémoire
    free(p1->coords);
    free(p1);
    free(p2->coords);
    free(p2);
    free(p3->coords);
    free(p3);
    free(p4->coords);
    free(p4);
    free(p5->coords);
    free(p5);
    free(p6->coords);
    free(p6);

    return 0;
}