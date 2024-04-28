#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
//#include "../CUnit-2.1-3/CUnit/Headers/Basic.h"

#include <stdint.h>
#include <inttypes.h>

#include "../headers/binary_file_reader.h"
#include "../headers/point.h"

// Déclaration de la fonction test_point_input
void test_point_input(); 

// Fonction de test pour point_input
void test_point_input() {
    FILE *file = fopen("../python/exemple4.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    uint32_t dim;
    uint64_t nbr_vectors;
    
    point_t **vectors = point_input(file, &dim, &nbr_vectors);
    fclose(file);
    printf("Dimension: %" PRIu32 "\n", dim);
    printf("Nombre de vecteurs: %" PRIu64 "\n", nbr_vectors);
    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }

    // Affichage de la dimension et du nombre de vecteurs
    printf("Dimension: %" PRIu32 "\n", dim);
    printf("Nombre de vecteurs: %" PRIu64 "\n", nbr_vectors);

    // Impression des coordonnées de chaque vecteur
    for (uint64_t i = 0; i < nbr_vectors; i++) {
        printf("Vecteur %" PRIu64 ":\n", i + 1);
        printf("Dimensions: %" PRIu32 "\n", vectors[i]->dim);
        printf("Coordonnées: ");
        for (uint32_t j = 0; j < vectors[i]->dim; j++) {
            printf("%" PRId64 " ", vectors[i]->coords[j]);
        }
        printf("\n");
        
        // Affichage des points repris
        printf("Points repris: ");
        for (uint32_t k = 0; k < vectors[i]->dim; k++) {
            printf("%" PRId64 " ", vectors[i]->coords[k]);
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

    CU_add_test(suite, "Test_point_input", test_point_input);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}
