#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../headers/point.h"



// Fonction qui calcule la factorielle d'un entier
uint64_t combinaison(int32_t p , uint64_t k) {
    if (k > p) {
        return 0;
    }
    if (k == 0 || k == p) {
        return 1;
    }
    // Utilisation de la formule récursive pour calculer le coefficient binomial
    uint64_t res = 1;
    // Calcul du coefficient binomial en évitant le dépassement de capacité
    for (uint64_t i = 0; i < k; ++i) {
        res *= (p - i);
        res /= (i + 1);
    }
    return res;
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

/**
 * @brief Génère toutes les combinaisons possibles de k vecteurs parmi un ensemble de n vecteurs. 
 * Chaque combinaison est représentée par un tableau de pointeurs vers les vecteurs choisis.
 * 
 * @param vectors Tableau de pointeurs vers les vecteurs d'entrée
 * @param n Nombre total de vecteurs dans l'ensemble
 * @param k Taille de chaque combinaison à générer
 * @param p Nombre total de vecteurs dans l'ensemble d'entrée
 * @return Tableau de pointeurs vers les combinaisons générées, ou NULL en cas d'erreur
 */
point_t ***generate_combinations(point_t **vectors, uint64_t n, uint64_t k, int32_t p) {
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
    for (uint64_t r=0;r<total_combinations;r++){
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

        // Libération de la mémoire utilisée pour la nouvelle combinaison
        if (r == total_combinations-1){
            free(current_combination_indices);
        }
        else{
            current_combination_indices = next_comb(current_combination_indices, p, k);
        }
    }

    return combinations;
}