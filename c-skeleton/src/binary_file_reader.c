#include "../headers/binary_file_reader.h" // Inclure le bon en-tête
#include "../headers/point.h" // Inclure si nécessaire

# include <stdlib.h>
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

    // Déclaration d'un uint64_t temporaire pour stocker les données lues depuis le fichier
    uint64_t temp_vectors;

    // On se déplace dans le fichier pour lire les 8 octets correspondant au nombre de vecteurs
    if (fseek(file, sizeof(uint32_t), SEEK_CUR) != 0) {
        perror("Erreur lors du déplacement dans le fichier");
        return 0; // ou une autre action appropriée
    }

    // On lit les 8 octets à partir de la position actuelle du curseur dans le fichier
    if (fread(&temp_vectors, sizeof(uint64_t), 1, file) != 1) {
        perror("Erreur lors de la lecture du nombre de vecteurs");
        return 0; // ou une autre action appropriée
    }

    // On convertit l'ordre des octets si nécessaire
    uint64_t nbr_vectors = be64toh(temp_vectors);
    
    return nbr_vectors;
}
point_t** point_input(FILE* file){

    if (!file) {
        perror("Le pointeur de fichier est nul");
        return NULL;
    }

    // Obtention de la dimension des points
    uint32_t dim = get_dimension_from_binary_file(file);
    if (dim <= 0) {
        perror("Erreur lors de l'obtention de la dimension des points");
        return NULL;
    }
    // Obtention du nombre de vecteurs
    uint64_t nbr_vectors = get_nbr_vectors_from_binary_file(file);
    if (nbr_vectors == 0) {
        perror("Erreur lors de l'obtention du nombre de vecteurs");
        return NULL;
    }
    // Allocation de mémoire pour stocker les vecteurs
    point_t **vectors = malloc( nbr_vectors * sizeof(point_t *));
    if (!vectors) {
        perror("Erreur d'allocation mémoire pour les vecteurs");
        return NULL;
    }
    for (uint32_t i = 0; i < nbr_vectors; i++) {
        point_t *vector = malloc(sizeof(point_t));
        if (!vector) {
            perror("Erreur d'allocation mémoire pour le vecteur");
            return NULL;
        }

        vector->dim = dim;
        vector->coords = malloc(dim * sizeof(int64_t));
        if (!vector->coords) {
            perror("Erreur d'allocation mémoire pour les coordonnées du vecteur");
            return NULL;
        }

        if (fread(vector->coords, sizeof(int64_t), dim, file) != dim) {
            perror("Erreur lors de la lecture des coordonnées du vecteur");
            return NULL;
        }

        // Conversion de l'ordre des octets pour chaque coordonnée
        for (uint32_t j = 0; j < dim; j++) {
            vector->coords[j] = be64toh(vector->coords[j]);
        }

        vectors[i] = vector;
    }

    return vectors;
    

}

