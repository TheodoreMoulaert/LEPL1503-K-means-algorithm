#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// Inclure les fonctions à tester
#include "../headers/binary_file_reader.h" // Inclure le bon en-tête
#include "../headers/distance.h" // Inclure si nécessaire

// Déclaration de la fonction test_point_input
void test_get_dimension_from_binary_file();
void test_get_nbr_vectors_from_binary_file(); 
void test_point_input(); 

// Définition des variables globales nécessaires pour les tests
FILE *test_file;

// Fonction de configuration des tests
void setUp(void) {
    // Ouvrir un fichier test binaire
    /*test_file = fopen("../python/exemple.bin", "wb");
    if (!test_file) {
        perror("Erreur lors de l'ouverture du fichier de test");
        exit(EXIT_FAILURE);
    }
    // Écrire des données de test dans le fichier binaire
    uint32_t dim = 3;
    uint32_t dim_be = htobe32(dim);
    fwrite(&dim_be, sizeof(uint32_t), 1, test_file); // Écrire la dimension
    uint64_t nbr_vectors = 2;
    uint64_t nbr_vectors_be = htobe64(nbr_vectors);
    fwrite(&nbr_vectors_be, sizeof(uint64_t), 1, test_file); // Écrire le nombre de vecteurs
    int64_t coords1[] = {1, 2, 3};
    int64_t coords2[] = {4, 5, 6};
    for (int i = 0; i < dim; i++) {
        coords1[i] = htobe64(coords1[i]);
        coords2[i] = htobe64(coords2[i]);
    }
    fwrite(coords1, sizeof(int64_t), dim, test_file); // Écrire les coordonnées du premier vecteur
    fwrite(coords2, sizeof(int64_t), dim, test_file); // Écrire les coordonnées du deuxième vecteur
    fclose(test_file);*/
    test_file = fopen("../python/exemple.bin", "rb");
    if (!test_file) {
        perror("Erreur lors de l'ouverture du fichier de test");
        exit(EXIT_FAILURE);
    }
}
/*
// Fonction de nettoyage des tests
void tearDown(void) {
    // Fermer le fichier de test
    fclose(test_file);
    // Supprimer le fichier de test
    remove("test_input.bin");
}*/

// Test de la fonction get_dimension_from_binary_file
void test_get_dimension_from_binary_file(void) {
    TEST_ASSERT_EQUAL_UINT32(3, get_dimension_from_binary_file(test_file));
}

// Test de la fonction get_nbr_vectors_from_binary_file
void test_get_nbr_vectors_from_binary_file(void) {
    TEST_ASSERT_EQUAL_UINT64(2, get_nbr_vectors_from_binary_file(test_file));
}

// Test de la fonction point_input
void test_point_input(void) {
    point_t **vectors = point_input(test_file);
    TEST_ASSERT_NOT_NULL(vectors);
    TEST_ASSERT_NOT_NULL(vectors[0]);
    TEST_ASSERT_NOT_NULL(vectors[1]);
    TEST_ASSERT_EQUAL_INT64(1, vectors[0]->coords[0]);
    TEST_ASSERT_EQUAL_INT64(2, vectors[0]->coords[1]);
    TEST_ASSERT_EQUAL_INT64(3, vectors[0]->coords[2]);
    TEST_ASSERT_EQUAL_INT64(4, vectors[1]->coords[0]);
    TEST_ASSERT_EQUAL_INT64(5, vectors[1]->coords[1]);
    TEST_ASSERT_EQUAL_INT64(6, vectors[1]->coords[2]);
    free(vectors[0]->coords);
    free(vectors[0]);
    free(vectors[1]->coords);
    free(vectors[1]);
    free(vectors);
}

// Ajoutez d'autres tests si nécessaire

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_get_dimension_from_binary_file);
    RUN_TEST(test_get_nbr_vectors_from_binary_file);
    RUN_TEST(test_point_input);
    return UNITY_END();
}