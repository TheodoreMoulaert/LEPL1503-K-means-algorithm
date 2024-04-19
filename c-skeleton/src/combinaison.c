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
uint64_t combinaison(uint64_t p, uint32_t k) {
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

point_t ***generate_combinations(point_t **vectors, uint64_t n, uint64_t k, uint32_t p) {
    // Vérification des paramètres
    if (n < k || k <= 0 || p < k) {
        return NULL;
    }

    // Calcul du nombre total de combinaisons
    uint64_t total_combinations = combinaison(p, k);
     
    // Allocation de la mémoire pour stocker les combinaisons
    point_t ***combinations = malloc(total_combinations * sizeof(point_t **));
    if (combinations == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        return NULL;
    }
    
    // Allocation de la mémoire pour stocker les indices de la combinaison actuelle
    uint64_t *current_combination_indices = malloc(k * sizeof(uint64_t));
    if (current_combination_indices == NULL) {
        // Gestion de l'erreur d'allocation mémoire
        free(combinations);
        return NULL;
    }

    // Initialisation de la première combinaison d'indices
    for (uint64_t i = 0; i < k; i++) {
        current_combination_indices[i] = i;
    }

    // Génération de toutes les combinaisons
    uint64_t combination_index = 0;
    while (current_combination_indices != NULL) {
        // Allocation de la mémoire pour stocker la nouvelle combinaison de points
        point_t **new_combination = malloc(k * sizeof(point_t *));
        if (new_combination == NULL) {
            // Gestion de l'erreur d'allocation mémoire
            for (uint64_t i = 0; i < combination_index; i++) {
                free(combinations[i]);
            }
            free(combinations);
            free(current_combination_indices);
            return NULL;
        }

        // Copie des points correspondant aux indices dans la nouvelle combinaison
        for (uint64_t i = 0; i < k; i++) {
            new_combination[i] = vectors[current_combination_indices[i]];
        }

        // Stockage de la nouvelle combinaison dans le tableau de combinaisons
        combinations[combination_index] = new_combination;
        combination_index++;

        // Génération de la prochaine combinaison d'indices
        current_combination_indices = next_comb(current_combination_indices, p, k);
        for (uint64_t i = 0; i < k; i++) {
            free(new_combination[i]); 
        }
        free(new_combination);
    }

    // Libération de la mémoire utilisée pour stocker les indices de la combinaison actuelle
    free(current_combination_indices);

    return combinations;
}