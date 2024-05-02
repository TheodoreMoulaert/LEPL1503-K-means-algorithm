#include "../headers/binary_file_reader.h" 
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/portable_endian.h"
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h> // Pour be32toh

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

/**
 * @brief Lit les vecteurs à partir d'un fichier binaire.
 * 
 * @param file Pointeur vers le fichier binaire
 * @param dim Pointeur vers la variable où stocker la dimension lue
 * @param nbr_vectors Pointeur vers la variable où stocker le nombre de vecteurs lus
 * @return Tableau de pointeurs vers les vecteurs lus, ou NULL en cas d'erreur
 */
point_t **point_input(FILE *file, uint32_t *dim, uint64_t *nbr_vectors) { //* remplacé par&
    if (!file) {
        perror("Fonctions : Le pointeur de fichier est nul");
        return NULL;
    }
    
    uint32_t dim_endian; // en format Big Endian
    uint64_t nb_endian;  // en format Big Endian

    // Lecture de la dimension
    if (fread(&dim_endian, sizeof(uint32_t), 1, file) != 1) {
        perror("Erreur lors de la lecture de la dimension");
        return NULL;
    }
    *dim = be32toh(dim_endian);
    
    // Lecture du nombre de vecteurs
    if (fread(&nb_endian, sizeof(uint64_t), 1, file) != 1) {
        perror("Erreur lors de la lecture du nombre de points spécifié");
        return NULL;
    }
    *nbr_vectors= be64toh(nb_endian);
    
    printf("Nombre de vecteurs dans le fichier binaire in : %lu\n", *nbr_vectors);
    printf("Dimension du fichier binaire in : %u\n", *dim);

    // Allocation de la mémoire pour les vecteurs
    point_t **vectors = malloc(*nbr_vectors * sizeof(point_t *));
    if (vectors == NULL) {
        perror("Fonctions :Erreur d'allocation mémoire pour les vecteurs");
        return NULL;
    }
   
    // Lecture des coordonnées des vecteurs
    for (uint64_t i = 0; i < *nbr_vectors; i++) {
        point_t *point = malloc(*nbr_vectors*sizeof(point_t));
        if (point == NULL) {
            perror("Erreur d'allocation mémoire pour le vecteur");
            free_vectors(vectors, i); // Libérer les vecteurs déjà alloués
            return NULL;
        }

        point->dim = *dim;
        point->nbr_vector = *nbr_vectors;
        point->coords = malloc(*dim * sizeof(int64_t));
        if (point->coords == NULL) {
            perror("Erreur d'allocation mémoire pour les coordonnées du vecteur");
            free(point);
            free_vectors(vectors, i); // Libérer les vecteurs déjà alloués
            return NULL;
        }

        // Lecture des coordonnées du vecteur
        if (fread(point->coords, sizeof(int64_t), *dim, file) != *dim) {
            perror("Erreur lors de la lecture des coordonnées du vecteur");
            free(point->coords);
            free(point);
            free_vectors(vectors, i); // Libérer les vecteurs déjà alloués
            return NULL;
        }

        // Conversion des coordonnées en format Big Endian
        for (uint32_t j = 0; j < *dim; j++) {
            point->coords[j] = be64toh(point->coords[j]);
        }

        vectors[i] = point;
        
    }
    
    return vectors;
}


/**
 * @brief Libère la mémoire allouée pour un tableau de vecteurs,y compris les coordonnées de chaque vecteur et les vecteurs eux-mêmes.
 * 
 * @param vectors Tableau de pointeurs vers les vecteurs
 * @param nbr_vectors Nombre de vecteurs dans le tableau
 */   
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

