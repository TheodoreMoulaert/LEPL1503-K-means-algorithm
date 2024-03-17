#include "../headers/binary_file_reader.h" // Inclure le bon en-tête
#include "../headers/point.h" // Inclure si nécessaire

#include <stdlib.h>
#include <endian.h>
#include <stdio.h>
#include <netinet/in.h> // Pour be32toh

uint32_t get_dimension_from_binary_file(FILE *file) {
    if (!file) {
        perror("Le pointeur de fichier est nul");
        return 0;
    }

    uint32_t temp_dim;
    if (fread(&temp_dim, sizeof(uint32_t), 1, file) != 1) {
        perror("Erreur lors de la lecture de la dimension");
        
        return 0;
    }
    uint32_t dim = be32toh(temp_dim);
    return dim;
}

uint64_t get_nbr_vectors_from_binary_file(FILE *file) {
    if (!file) {
        perror("Le pointeur de fichier est nul");
        return 0;
    }
    uint32_t dimBE; // en format Big Endian
	uint64_t nbBE; // en format Big Endian
	if(fread(&dimBE, sizeof(uint32_t), 1, file) == 0)
	{
		fprintf(stderr, "Pas de dimension de point spécifiée.");
		return 0;
	}; 
	if(fread(&nbBE, sizeof(uint64_t), 1, file) == 0)
	{
		fprintf(stderr, "pas de nombre de points spécifié."); 
		return 0;
	}
	uint32_t dim = be32toh(dimBE);
	uint64_t nbr_vectors = be64toh(nbBE);
    
    return nbr_vectors;
}

point_t **select_vectors(point_t **vectors, uint64_t nbr_vectors) {
    if (!vectors) {
        perror("Le tableau de vecteurs est NULL");
        return NULL;
    }

    // Allocation de mémoire pour stocker les vecteurs sélectionnés
    point_t **selected_vectors = (point_t**) malloc(nbr_vectors * sizeof(point_t *));
    if (!selected_vectors) {
        perror("Erreur d'allocation mémoire pour les vecteurs sélectionnés");
        return NULL;
    }

    // Copie des données des vecteurs d'origine dans les nouveaux vecteurs sélectionnés
    for (uint64_t i = 0; i < nbr_vectors; i++) {
        // Allocation de mémoire pour le nouveau vecteur sélectionné
        selected_vectors[i] = (point_t*) malloc(sizeof(point_t));
        if (!selected_vectors[i]) {
            perror("Erreur d'allocation mémoire pour un vecteur sélectionné");
            // Si une erreur se produit, libérez la mémoire allouée précédemment
            for (uint64_t j = 0; j < i; j++) {
                free(selected_vectors[j]);
            }
            free(selected_vectors);
            return NULL;
        }

        // Copie de la dimension du vecteur
        selected_vectors[i]->dim = vectors[i]->dim;

        // Allocation de mémoire pour les coordonnées du nouveau vecteur
        selected_vectors[i]->coords = (int64_t*) malloc(vectors[i]->dim * sizeof(int64_t));
        if (!selected_vectors[i]->coords) {
            perror("Erreur d'allocation mémoire pour les coordonnées d'un vecteur sélectionné");
            // Si une erreur se produit, libérez la mémoire allouée précédemment
            for (uint64_t j = 0; j < i; j++) {
                free(selected_vectors[j]->coords);
                free(selected_vectors[j]);
            }
            free(selected_vectors);
            return NULL;
        }

        // Copie des coordonnées du vecteur d'origine dans le nouveau vecteur sélectionné
        for (uint32_t j = 0; j < vectors[i]->dim; j++) {
            selected_vectors[i]->coords[j] = vectors[i]->coords[j];
        }
    }

    return selected_vectors;
}


point_t **point_input(FILE *file) {
    if (!file) {
        perror("Le pointeur de fichier est nul");
        return NULL;
    }
    uint32_t dimBE; // en format Big Endian
	uint64_t nbBE; // en format Big Endian
	if(fread(&dimBE, sizeof(uint32_t), 1, file) == 0)
	{
		fprintf(stderr, "Pas de dimension de point spécifiée.");
		return NULL;
	}; 
	if(fread(&nbBE, sizeof(uint64_t), 1, file) == 0)
	{
		fprintf(stderr, "pas de nombre de points spécifié."); 
		return NULL;
	}
	uint32_t dim = be32toh(dimBE);
	uint64_t nbr_vectors = be64toh(nbBE);
    printf("Nombre de vecteurs dans le fichier binaire in : %lu\n", nbr_vectors);

	
    if (nbr_vectors <= 0) {
        perror("Erreur lors de l'obtention du nombre de vecteurs");
        return NULL;
    }

    // Allocation de mémoire pour stocker les vecteurs
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
    point_t **selected_vectors = select_vectors(vectors, nbr_vectors);

    // Libération de la mémoire allouée pour vectors, car les éléments sélectionnés sont maintenant dans selected_vectors
    free(vectors);

    return selected_vectors;
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

