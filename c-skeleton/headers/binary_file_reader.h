#ifndef BINARY_FILE_READER_H
#define BINARY_FILE_READER_H
#include "../headers/point.h" // Inclure si nécessaire


#include <stdint.h>
#include <stdio.h> // Inclure pour FILE *

// Déclaration de la fonction pour obtenir la dimension des points et le nombre de vecteurs à partir du fichier binaire


uint32_t get_dimension_from_binary_file(FILE *file, uint32_t* dim, uint64_t* nbr_vector); 

// Déclaration de la fonction pour obtenir les informations sur les coordonnées des points

point_t** point_input(FILE* file);

//Déclaration de la fonction pour obtenir le nombre de clusters 

//uint64_t size_clusters( point_t** clusters);

// Déclaration de la fonction pour free

void free_vectors(point_t **vectors, uint64_t nbr_vectors);

#endif // BINARY_FILE_READER_H