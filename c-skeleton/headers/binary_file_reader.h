#ifndef BINARY_FILE_READER_H
#define BINARY_FILE_READER_H
#include "../headers/point.h"
#include "../headers/portable_endian.h"
#include <stdint.h>
#include <stdio.h>


/**
 * @brief Lit la dimension et le nombre de vecteurs à partir d'un fichier binaire.   
 * Elle retourne 1 en cas de succès et 0 en cas d'échec.
 * 
 * @param file Pointeur vers le fichier binaire
 * @param dim Pointeur vers la variable où stocker la dimension lue
 * @param nbr_vector Pointeur vers la variable où stocker le nombre de vecteurs lus
 * @return 1 si la lecture est réussie, sinon 0
 * 
 */
uint32_t get_dimension_from_binary_file(FILE *file, uint32_t* dim, uint64_t* nbr_vector); 

/**
 * @brief Lit les vecteurs à partir d'un fichier binaire.
 * 
 * @param file Pointeur vers le fichier binaire
 * @param dim Pointeur vers la variable où stocker la dimension lue
 * @param nbr_vectors Pointeur vers la variable où stocker le nombre de vecteurs lus
 * @return Tableau de pointeurs vers les vecteurs lus, ou NULL en cas d'erreur
 */
point_t **point_input(FILE *file, uint32_t *dim, uint64_t *nbr_vectors);

/**
 * @brief Libère la mémoire allouée pour un tableau de vecteurs,y compris les coordonnées de chaque vecteur et les vecteurs eux-mêmes.
 * 
 * @param vectors Tableau de pointeurs vers les vecteurs
 * @param nbr_vectors Nombre de vecteurs dans le tableau
 */  
void free_vectors(point_t **vectors, uint64_t nbr_vectors);

#endif // BINARY_FILE_READER_H