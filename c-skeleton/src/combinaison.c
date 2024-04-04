
#include "../headers/combinaison.h"
#include "../headers/combinaison.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>


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
// Elle renvoie nullptr si aucune combinaison suivante n'est possible
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



bool has_duplicates(int64_t comb[], int64_t k) {
    for (int64_t i = 0; i < k - 1; i++) {
        for (int64_t j = i + 1; j < k; j++) {
            if (comb[i] == comb[j]) {
                return true;
            }
        }
    }
    return false;
}

