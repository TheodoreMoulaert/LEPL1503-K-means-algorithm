#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>

#include "../headers/binary_file_reader.h" 
#include "../headers/point.h"

// Déclaration de la fonction test_point_input
void test_get_dimension_from_binary_file();
void test_get_nbr_vectors_from_binary_file(); 
void test_point_input1();
void test_point_input2();  
void test_point_input3(); 



// Définition de la fonction de test
void test_get_dimension_from_binary_file() {
    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    uint32_t dim = get_dimension_from_binary_file(file);
    fclose(file);

    //printf("Dimension lue depuis le fichier binaire : %u\n", dim);
    CU_ASSERT_EQUAL(dim, 2);
}

void test_get_nbr_vectors_from_binary_file() {
   
    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    uint64_t nbr_vectors = get_nbr_vectors_from_binary_file(file);
    fclose(file);
 
    //printf("Nombre de vecteurs dans le fichier binaire : %lu\n", nbr_vectors);
    CU_ASSERT_EQUAL(nbr_vectors, 7);
}

void test_point_input1() {
    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    // Appel de la fonction point_input pour obtenir les vecteurs à partir du fichier
    point_t **vectors = point_input(file);

    // Fermeture du fichier après utilisation
    fclose(file);

    // Vérification si la fonction a renvoyé un résultat valide
    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }

    // Obtention de la taille du tableau
    int vector_count =vectors[0]->nbr_vector; 

    // Impression des coordonnées de chaque vecteur
    for (int i = 0; i < vector_count; i++) {
        printf("Vecteur %d:\n", i + 1);
        printf("Dimensions: %u\n", vectors[i]->dim);
        printf("Coordonnées: ");
        for (int j = 0; j < vectors[i]->dim; j++) {
            printf("%" PRId64 " ", vectors[i]->coords[j]);
        }
        printf("\n");

        // Libération de la mémoire allouée pour le vecteur actuel
        free(vectors[i]->coords);
        free(vectors[i]);
    }

    // Libération de la mémoire allouée pour le tableau de vecteurs
    free(vectors);
}
void test_point_input2() {
    FILE *file = fopen("../python/exemple3.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    // Appel de la fonction point_input pour obtenir les vecteurs à partir du fichier
    point_t **vectors = point_input(file);

    // Fermeture du fichier après utilisation
    fclose(file);

    // Vérification si la fonction a renvoyé un résultat valide
    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }

    // Obtention de la taille du tableau
    int vector_count =vectors[0]->nbr_vector; 

    // Impression des coordonnées de chaque vecteur
    for (int i = 0; i < vector_count; i++) {
        printf("Vecteur %d:\n", i + 1);
        printf("Dimensions: %u\n", vectors[i]->dim);
        printf("Coordonnées: ");
        for (int j = 0; j < vectors[i]->dim; j++) {
            printf("%" PRId64 " ", vectors[i]->coords[j]);
        }
        printf("\n");

        // Libération de la mémoire allouée pour le vecteur actuel
        free(vectors[i]->coords);
        free(vectors[i]);
    }

    // Libération de la mémoire allouée pour le tableau de vecteurs
    free(vectors);
}

void test_point_input3() {
    FILE *file = fopen("../python/exemple4.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    // Appel de la fonction point_input pour obtenir les vecteurs à partir du fichier
    point_t **vectors = point_input(file);

    // Fermeture du fichier après utilisation
    fclose(file);

    // Vérification si la fonction a renvoyé un résultat valide
    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }

    // Obtention de la taille du tableau
    int vector_count =vectors[0]->nbr_vector; 

    // Impression des coordonnées de chaque vecteur
    for (int i = 0; i < vector_count; i++) {
        printf("Vecteur %d:\n", i + 1);
        printf("Dimensions: %u\n", vectors[i]->dim);
        printf("Coordonnées: ");
        for (int j = 0; j < vectors[i]->dim; j++) {
            printf("%" PRId64 " ", vectors[i]->coords[j]);
        }
        printf("\n");

        // Libération de la mémoire allouée pour le vecteur actuel
        free(vectors[i]->coords);
        free(vectors[i]);
    }

    // Libération de la mémoire allouée pour le tableau de vecteurs
    free(vectors);
}



// Fonction principale pour exécuter les tests
int main() {
    CU_initialize_registry(); 

    
    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);

   
    CU_add_test(suite, "Test_dim", test_get_dimension_from_binary_file);
    CU_add_test(suite, "Test_nbr_vectors", test_get_nbr_vectors_from_binary_file);
    CU_add_test(suite, "Test_point_input1", test_point_input1);  
    CU_add_test(suite, "Test_point_input2", test_point_input2);  
    CU_add_test(suite, "Test_point_input3", test_point_input3);  

    
    CU_basic_run_tests();

 
    CU_cleanup_registry();

    return CU_get_error();
}
