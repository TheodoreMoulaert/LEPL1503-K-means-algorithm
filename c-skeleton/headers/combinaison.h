#ifndef COMBINATION_H
#define COMBINATION_H
#include <stdint.h>
#include <stdbool.h>
#include "../headers/point.h"

/**-
* Calcule le nombre de combinaison de k parmi p => C(p,k) 
*/
uint64_t factorial(uint64_t n);

uint64_t combinaison(uint64_t p, uint32_t k);

uint64_t *next_comb(uint64_t comb[], uint64_t n, uint64_t k); 

point_t ***generate_combinations(point_t **vectors, uint64_t n, uint64_t k) ;

#endif //COMBINATION_H