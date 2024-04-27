#ifndef BINARY_FILE_READER_H
#define BINARY_FILE_READER_H
#include "../headers/point.h"
#include "../headers/portable_endian.h"
#include <stdint.h>
#include <stdio.h>

// Déclaration de la fonction pour obtenir la dimension des points et le nombre de vecteurs à partir du fichier binaire
uint32_t get_dimension_from_binary_file(FILE *file, uint32_t* dim, uint64_t* nbr_vector); 

// Déclaration de la fonction pour obtenir les informations sur les coordonnées des points
point_t **point_input(FILE *file, uint32_t *dim, uint64_t *nbr_vectors);

// Déclaration de la fonction pour free
void free_vectors(point_t **vectors, uint64_t nbr_vectors);

#endif // BINARY_FILE_READER_H