#include "../headers/binary_file_reader.h" 
#include "../headers/point.h"
#include "../headers/cluster.h"

#include <stdlib.h>
#include <endian.h>
#include <stdio.h>
#include <netinet/in.h> // Pour be32toh


uint32_t get_dimension_from_binary_file(FILE *file, uint32_t* dim, uint64_t* nbr_vector) {
    if (!file) {
        perror("Le pointeur de fichier est nul");
        return 0;
    }

    uint32_t dim_endian; // en format Big Endian
    uint64_t nb_endian; // en format Big Endian
    
    // Lecture de la dimension
    if (fread(&dim_endian, sizeof(uint32_t), 1, file) != 1) {
        perror("Erreur lors de la lecture de la dimension");
        return 0;
    }
    *dim = be32toh(dim_endian);
    
    // Lecture du nombre de vecteurs
    if (fread(&nb_endian, sizeof(uint64_t), 1, file) != 1) {
        perror("Erreur lors de la lecture du nombre de points spécifié");
        return 0;
    }
    *nbr_vector = be64toh(nb_endian);

    return 1;
}

point_t **point_input(FILE *file) {
    if (!file) {
        perror("Le pointeur de fichier est nul");
        return NULL;
    }
    uint32_t dim_endian; // en format Big Endian
	uint64_t nb_endian; // en format Big Endian
	if(fread(&dim_endian, sizeof(uint32_t), 1, file) == 0)
	{
		fprintf(stderr, "Pas de dimension de point spécifiée.");
		return NULL;
	}; 
	if(fread(&nb_endian, sizeof(uint64_t), 1, file) == 0)
	{
		fprintf(stderr, "pas de nombre de points spécifié."); 
		return NULL;
	}
	uint32_t dim = be32toh(dim_endian);
	uint64_t nbr_vectors = be64toh(nb_endian);
    printf("Nombre de vecteurs dans le fichier binaire in : %lu\n", nbr_vectors);

	
    if (nbr_vectors <= 0) {
        perror("Erreur lors de l'obtention du nombre de vecteurs");
        return NULL;
    }

    
    point_t **vectors = (point_t**) malloc(nbr_vectors * sizeof(point_t *));
    if (vectors == NULL) {
        perror("Erreur d'allocation mémoire pour les vecteurs");
        return NULL;
    }

    for (uint64_t i = 0; i < nbr_vectors; i++) {
        point_t *point = (point_t*) malloc(sizeof(point_t));
        if (point == NULL) {
            perror("Erreur d'allocation mémoire pour le vecteur");
            free_vectors(vectors, i+1);
            return NULL;
        }

        point->dim = dim;
        point-> nbr_vector = nbr_vectors; 
        point->coords = (int64_t*) malloc(dim *sizeof(int64_t));
        if (point->coords == NULL) {
            perror("Erreur d'allocation mémoire pour les coordonnées du vecteur");
            free(point);
            free_vectors(vectors, i+1);
            return NULL;
        }

        if (fread(point->coords, sizeof(int64_t), dim, file) != dim) {
            perror("Erreur lors de la lecture des coordonnées du vecteur");
            free(point->coords);
            free(point);
            free_vectors(vectors, i+1);
            return NULL;
        }

        for (uint32_t j = 0; j < dim; j++) {
            point->coords[j] = be64toh(point->coords[j]);
        }

        vectors[i] = point;
    
    }
    return vectors; // attention vector n'est pas de bonne dimension aller voir les tests pour la selection; 
}

   
void free_vectors(point_t **vectors, uint64_t nbr_vectors) {
    if (vectors == NULL) return;

    for (uint64_t i = 0; i < nbr_vectors; i++) {
        if (vectors[i] != NULL) {
            free(vectors[i]->coords);
            free(vectors[i]);
        }
    }

    free(vectors);
}

