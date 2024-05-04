#ifndef COMBINATION_H
#define COMBINATION_H
#include <stdint.h>
#include <stdbool.h>
#include "../headers/point.h"

// Fonction qui calcule la factorielle d'un entier
uint64_t combinaison(int32_t p, uint32_t k);

// Fonction qui génère la combinaison suivante de k éléments pris parmi n
// Elle renvoie NULL si aucune combinaison suivante n'est possible
uint64_t *next_comb(uint64_t comb[], uint64_t n, uint64_t k); 

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
point_t ***generate_combinations(point_t **vectors, uint64_t n, uint64_t k, int32_t p);

#endif //COMBINATION_H