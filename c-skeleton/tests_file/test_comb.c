#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include "../headers/combinaison.h"

int main() {
    int64_t coordinates[7][2] = {
        {1, 1},
        {2, 2},
        {3, 4},
        {5, 7},
        {3, 5},
        {5, 5},
        {4, 5}
    };

    point_t **vectors = malloc(7 * sizeof(point_t *));
    if (vectors == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les points.\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 7; i++) {
        vectors[i] = malloc(sizeof(point_t));
        if (vectors[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour un point.\n");
            return EXIT_FAILURE;
        }
        vectors[i]->coords = malloc(2 * sizeof(int64_t));
        if (vectors[i]->coords == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour les coordonnées d'un point.\n");
            return EXIT_FAILURE;
        }
        vectors[i]->coords[0] = coordinates[i][0];
        vectors[i]->coords[1] = coordinates[i][1];
        vectors[i]->dim = 2;
    }

    uint64_t n = 7;
    uint32_t k = 2;
    uint32_t p = 3;

    point_t ***combinations = generate_combinations(vectors, n, k, p);
    if (combinations == NULL) {
        fprintf(stderr, "Erreur lors de la génération des combinaisons.\n");
        return EXIT_FAILURE;
    }

    printf("Combinaisons générées :\n");
    for (uint64_t i = 0; i < combinaison(p, k); i++) {
        printf("Combinaison %lu :\n", i + 1);
        for (uint32_t j = 0; j < k; j++) {
            printf("(%" PRId64 ", %" PRId64 ")\n", combinations[i][j]->coords[0], combinations[i][j]->coords[1]);
        }
        printf("\n");
    }

    // Libérer la mémoire
    for (uint64_t i = 0; i < combinaison(p, k); i++) {
        free(combinations[i]);
    }
    free(combinations);

    for (int i = 0; i < 7; i++) {
        free(vectors[i]->coords);
        free(vectors[i]);
    }
    free(vectors);

    return EXIT_SUCCESS;
}
