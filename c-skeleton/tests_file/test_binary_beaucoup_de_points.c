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

void test_point_input1();

void test_point_input1() {
    FILE *file = fopen("../python/exemple1000.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    uint32_t dim;
    uint64_t nbr_vectors;

    // Appel de la fonction point_input pour obtenir les vecteurs à partir du fichier
    point_t **vectors = point_input(file, &dim, &nbr_vectors);

    // Fermeture du fichier après utilisation
    fclose(file);

    // Vérification si la fonction a renvoyé un résultat valide
    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }

    // Assert pour vérifier que le nombre de vecteurs est égal à 1000
    CU_ASSERT_EQUAL(nbr_vectors, 1000);

    // Assert pour vérifier que la dimension est égale à 2
    CU_ASSERT_EQUAL(dim, 2);

    // Impression des coordonnées de chaque vecteur
    for (uint64_t i = 0; i < nbr_vectors; i++) {

        // Libération de la mémoire allouée pour les coordonnées du vecteur
        free(vectors[i]->coords);

        // Libération de la mémoire allouée pour la structure point_t du vecteur
        free(vectors[i]);
    }

    // Libération de la mémoire allouée pour le tableau de pointeurs de vecteur
    free(vectors);
}

// Fonction principale pour exécuter les tests
int main() {
    CU_initialize_registry(); 

    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);

    CU_add_test(suite, "Test_point_input1", test_point_input1);  

    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
