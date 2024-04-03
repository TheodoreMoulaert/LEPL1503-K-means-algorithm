#ifndef COMBINATION_H
#define COMBINATION_H
#include <stdint.h>

/**-
* Calcule le nombre de combinaison de k parmi p => C(p,k) 
*/
uint64_t factorial(uint64_t n) ; 

uint64_t comb(uint64_t p, uint32_t k);

#endif //COMBINATION_H