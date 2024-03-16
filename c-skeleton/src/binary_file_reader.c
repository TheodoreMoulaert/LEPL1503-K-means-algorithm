#include "../headers/binary_file_reader.h" // Inclure le bon en-tête
#include "../headers/point.h" // Inclure si nécessaire

# include <stdlib.h>
#include <endian.h>


uint32_t get_dimension_from_binary_file(FILE *file) {
    if (!file) {
        perror("Le pointeur de fichier est nul");
        return 0;
    }

    uint32_t temp_dim;
    if (fread(&temp_dim, sizeof(uint32_t), 1, file) != 1) {
        perror("Erreur lors de la lecture de la dimension");
        fclose(file);
        return 0;
    }

    uint32_t dim = be32toh(temp_dim);
    fclose(file);
    return dim;
}

uint32_t get_nbr_vectors_from_binary_file(FILE *file) {
    if (!file) {
        perror("Le pointeur de fichier est nul");
        return 0;
    }

    uint32_t temp_vectors;
    if (fread(&temp_vectors, sizeof(uint32_t), 1, file) != 1) {
        perror("Erreur lors de la lecture du nombre de vecteurs");
        fclose(file);
        return 0;
    }

    uint32_t nbr_vectors = be32toh(temp_vectors);
    fclose(file);
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
    uint32_t nbr_vectors = get_nbr_vectors_from_binary_file(file);
    if (nbr_vectors == 0) {
        perror("Erreur lors de l'obtention du nombre de vecteurs");
        return NULL;
    }
    // Allocation de mémoire pour stocker les vecteurs
    point_t **vectors = malloc(nbr_vectors * sizeof(point_t *));
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

