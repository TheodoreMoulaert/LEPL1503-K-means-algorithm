#include <stdint.h>
#include "../headers/combinaison.h"

#include <stdint.h>
#include "../headers/combinaison.h"

// Fonction pour calculer la factorielle d'un entier
uint64_t factorial(uint64_t n) {
    if (n == 0) {
        return 1;
    }
    uint64_t result = 1;
    for (uint64_t i = 1; i <= n; ++i) {
        result *= i;
    }
    return result;
}

// Fonction pour calculer le coefficient binomial en utilisant des  : La fonction comb calcule le coefficient binomial (combinaison) de p éléments choisis k à la fois. 

uint64_t comb(uint64_t p, uint32_t k) {
    if (k > p) {
        return 0;
    }
    uint64_t numerator = factorial(p);
    uint64_t denominator = factorial(k) * factorial(p - k);
    return numerator / denominator;
}
