#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>

#include "../headers/binary_file_reader.h" // Inclure le bon en-tête
#include "../headers/distance.h" // Inclure si nécessaire



// Déclaration de la fonction test_point_input
void test_get_dimension_from_binary_file();
void test_get_nbr_vectors_from_binary_file(); 




// Définition de la fonction de test
void test_get_dimension_from_binary_file() {
    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    uint32_t dim = get_dimension_from_binary_file(file);
    fclose(file);

    printf("Dimension lue depuis le fichier binaire : %u\n", dim);
}

void test_get_nbr_vectors_from_binary_file() {
    // Ouverture du fichier binaire
    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    // Lecture du nombre de vecteurs à partir du fichier
    uint64_t nbr_vectors = get_nbr_vectors_from_binary_file(file);
    fclose(file);

    // Affichage du nombre de vecteurs
    printf("Nombre de vecteurs dans le fichier binaire : %lu\n", nbr_vectors);
}

// Fonction principale pour exécuter les tests
int main() {
    CU_initialize_registry(); // Initialisation du registre de tests

    // Création d'une suite de tests
    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);

    // Ajout des tests à la suite
    CU_add_test(suite, "Test_dim", test_get_dimension_from_binary_file);
    CU_add_test(suite, "Test_nbr_vectors", test_get_nbr_vectors_from_binary_file);

    // Exécution des tests
    CU_basic_run_tests();

    // Nettoyage du registre de tests
    CU_cleanup_registry();

    return CU_get_error();
}
