#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
//#include "../CUnit-2.1-3/CUnit/Headers/Basic.h"
#include <stdint.h>
#include <inttypes.h>

#include "../headers/binary_file_reader.h"
#include "../headers/distance.h"
#include "../headers/point.h"

// Déclaration de la fonction de test pour les fonctions de distance (test 1).
void test_distance_functions1();

// Déclaration de la fonction de test pour les fonctions de distance (test 2).
void test_distance_functions2();

// Fonction de test pour les fonctions de distance (test 1).
void test_distance_functions1() {
    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    uint32_t dim;
    uint64_t nbr_vectors;
    point_t **vectors = point_input(file, &dim, &nbr_vectors);

    fclose(file);

    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }

    // Vérification du nombre de vecteurs
    CU_ASSERT_TRUE(nbr_vectors >= 2);

    // Sélection du premier vecteur
    point_t *first_vector = vectors[0];

    for (uint64_t i = 1; i < nbr_vectors; i++) {
        // Calcul des distances
        int64_t manhattan_dist = squared_manhattan_distance(first_vector, vectors[i]);
        int64_t euclidean_dist = squared_euclidean_distance(first_vector, vectors[i]);

        // Vérification des distances
        switch (i) {
            case 1:
                CU_ASSERT_EQUAL(manhattan_dist, 4);
                CU_ASSERT_EQUAL(euclidean_dist, 2);
                break;
            case 2:
                CU_ASSERT_EQUAL(manhattan_dist, 25);
                CU_ASSERT_EQUAL(euclidean_dist, 13);
                break;
            case 3:
                CU_ASSERT_EQUAL(manhattan_dist, 100);
                CU_ASSERT_EQUAL(euclidean_dist, 52);
                break;
            case 4:
                CU_ASSERT_EQUAL(manhattan_dist, 36);
                CU_ASSERT_EQUAL(euclidean_dist, 20);
                break;
            case 5:
                CU_ASSERT_EQUAL(manhattan_dist, 64);
                CU_ASSERT_EQUAL(euclidean_dist, 32);
                break;
            case 6:
                CU_ASSERT_EQUAL(manhattan_dist, 49);
                CU_ASSERT_EQUAL(euclidean_dist, 25);
                break;
            default:
                break;
        }
    }

    // Libération de la mémoire allouée pour le tableau de vecteurs
    free_vectors(vectors, nbr_vectors);
}

// Fonction de test pour les fonctions de distance (test 2).
void test_distance_functions2() {
    FILE *file = fopen("../python/exemple3.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    uint32_t dim;
    uint64_t nbr_vectors;
    point_t **vectors = point_input(file, &dim, &nbr_vectors);

    fclose(file);

    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }

    // Vérification du nombre de vecteurs
    CU_ASSERT_TRUE(nbr_vectors >= 2);

    // Sélection du premier vecteur
    point_t *first_vector = vectors[0];

    for (uint64_t i = 1; i < nbr_vectors; i++) {
        // Calcul des distances
        int64_t manhattan_dist = squared_manhattan_distance(first_vector, vectors[i]);
        int64_t euclidean_dist = squared_euclidean_distance(first_vector, vectors[i]);

        // Vérification des distances
        switch (i) {
            case 1:
                CU_ASSERT_EQUAL(manhattan_dist, 1);
                CU_ASSERT_EQUAL(euclidean_dist, 1);
                break;
            case 2:
                CU_ASSERT_EQUAL(manhattan_dist, 4);
                CU_ASSERT_EQUAL(euclidean_dist, 4);
                break;
            case 3:
                CU_ASSERT_EQUAL(manhattan_dist, 9);
                CU_ASSERT_EQUAL(euclidean_dist, 9);
                break;
            case 4:
                CU_ASSERT_EQUAL(manhattan_dist, 16);
                CU_ASSERT_EQUAL(euclidean_dist, 16);
                break;
            case 5:
                CU_ASSERT_EQUAL(manhattan_dist, 25);
                CU_ASSERT_EQUAL(euclidean_dist, 25);
                break;
            case 6:
                CU_ASSERT_EQUAL(manhattan_dist, 36);
                CU_ASSERT_EQUAL(euclidean_dist, 36);
                break;
            default:
                break;
        }
    }

    // Libération de la mémoire allouée pour le tableau de vecteurs
    free_vectors(vectors, nbr_vectors);
}

int main() {
    CU_initialize_registry(); // Initialisation du registre de tests

    // Ajout d'une suite de tests
    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);

    // Ajout des fonctions de test à la suite
    CU_add_test(suite, "Test_distance_functions1", test_distance_functions1);
    CU_add_test(suite, "Test_distance_functions2", test_distance_functions2);

    // Exécution des tests
    CU_basic_run_tests();

    // Nettoyage du registre de tests
    CU_cleanup_registry();

    return CU_get_error(); // Renvoie le code d'erreur des tests
}

