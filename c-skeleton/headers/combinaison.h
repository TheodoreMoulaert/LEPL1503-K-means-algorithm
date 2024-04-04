#ifndef COMBINATION_H
#define COMBINATION_H
#include <stdint.h>
#include <stdbool.h>

/**-
* Calcule le nombre de combinaison de k parmi p => C(p,k) 
*/
uint64_t factorial(uint64_t n) ; 

uint64_t comb(uint64_t p, uint32_t k);

uint64_t *next_comb(uint64_t comb[], uint64_t n, uint64_t k); 

bool has_duplicates(int64_t comb[], int64_t k); 

#endif //COMBINATION_H