#ifndef BINARY_FILE_READER_H
#define BINARY_FILE_READER_H

#include "point.h"

#include <stdint.h>
#include <stdio.h> // Inclure pour FILE *

// Déclaration de la fonction pour obtenir la dimension des points et le nombre de vecteurs à partir du fichier binaire


uint32_t get_dimension_from_binary_file(FILE* file);


// Déclaration de la fonction pour obtenir le nombre de vecteurs à partir du fichier binaire

uint32_t get_nbr_vectors_from_binary_file(FILE *file);

//// Déclaration de la fonction pour obtenir les informations sur les coordonnées des points

point_t** point_input(FILE* file)

#endif // BINARY_FILE_READER_H