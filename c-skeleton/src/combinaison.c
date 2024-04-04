#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Structure pour représenter un point dans l'espace
typedef struct {
    int64_t *coordinates;  // Coordonnées du point
    uint32_t dimension;    // Nombre de dimensions
} point_t;

// Fonction qui calcule la factorielle d'un entier
uint64_t factorial(uint64_t n) {
    if (n <= 1)
        return 1;
    else
        return n * factorial(n - 1);
}

// Fonction qui calcule le nombre de combinaisons de p éléments pris k par k
uint64_t combination(uint64_t p, uint32_t k) {
    if (k > p) {
        return 0;
    }
    uint64_t numerator = factorial(p);
    uint64_t denominator = factorial(k) * factorial(p - k);
    return numerator / denominator;
}

// Fonction qui génère la combinaison suivante de k éléments pris parmi n
// Elle renvoie NULL si aucune combinaison suivante n'est possible
uint64_t *next_comb(uint64_t comb[], uint64_t n, uint64_t k) {
    // Recherche de l'indice de l'élément à modifier
    uint64_t index = k - 1;
    while (index > 0 && comb[index] == n - k + index) {
        index--;
    }

    // Si aucun élément ne peut être incrémenté, c'est la dernière combinaison
    if (index == 0 && comb[index] == n - k) {
        return NULL;
    }

    // Incrémentation de l'élément trouvé
    comb[index]++;

    // Mise à jour des éléments suivants
    for (uint64_t i = index + 1; i < k; i++) {
        comb[i] = comb[i - 1] + 1;
    }

    return comb;
}

// Fonction qui génère toutes les combinaisons possibles de k éléments parmi les n premiers éléments d'un tableau de pointeurs
uint64_t **generate_combinations(point_t **vectors, uint64_t n, uint64_t k) {
    // Vérification des paramètres
    if (n < k || k <= 0) {
        return NULL;
    }

    // Calcul du nombre total de combinaisons
    uint64_t total_combinations = combination(n, k);
    
    // Allocation de la mémoire pour stocker les combinaisons
    uint64_t **combinations = malloc(total_combinations * sizeof(uint64_t *));
    if (combinations == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        return NULL;
    }
    
    // Initialisation du premier ensemble de combinaisons
    uint64_t *current_combination = malloc(k * sizeof(uint64_t));
    if (current_combination == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        free(combinations);
        return NULL;
    }
    for (uint64_t i = 0; i < k; i++) {
        current_combination[i] = i;
    }

    // Génération de toutes les combinaisons
    uint64_t combination_index = 0;
    combinations[combination_index] = current_combination;
    combination_index++;
    uint64_t *next;
    while ((next = next_comb(current_combination, n, k)) != NULL) {
        uint64_t *new_combination = malloc(k * sizeof(uint64_t));
        if (new_combination == NULL) {
            // Gestion de l'erreur d'allocation mémoire
            for (uint64_t i = 0; i < combination_index; i++) {
                free(combinations[i]);
            }
            free(combinations);
            return NULL;
        }
        memcpy(new_combination, next, k * sizeof(uint64_t));
        combinations[combination_index] = new_combination;
        combination_index++;
    }

    return combinations;
}
