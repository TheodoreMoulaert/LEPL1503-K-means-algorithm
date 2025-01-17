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

/**
 * @brief Fonction de test pour point_input
 * 
 * Cette fonction teste la fonction point_input en lisant des vecteurs à partir d'un fichier binaire.
 * Elle vérifie également si les vecteurs sont correctement lus et affiche leurs coordonnées.
 */
void test_point_input() {
    // Ouverture du fichier binaire
    FILE *file = fopen("exemple.bin", "rb");
    if (!file) {
        // Gestion de l'erreur si le fichier ne peut pas être ouvert
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    uint32_t dim;
    uint64_t nbr_vectors;
    
    // Appel de la fonction point_input pour obtenir les vecteurs à partir du fichier
    point_t **vectors = point_input(file, &dim, &nbr_vectors);
    fclose(file);
    
    // Assertions
    CU_ASSERT_EQUAL(dim, 2);
    CU_ASSERT_EQUAL(nbr_vectors, 7);

    // Vérification si la fonction a renvoyé un résultat valide
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

/**
 * @brief Fonction principale pour exécuter les tests
 * 
 * Cette fonction initialise les tests, ajoute le test `test_point_input` à une suite de tests,
 * exécute les tests, nettoie le registre de tests et renvoie le code d'erreur.
 * 
 * @return Le code d'erreur des tests.
 */
int main() {
    // Initialisation du registre de tests
    CU_initialize_registry(); 

    // Ajout d'une suite de tests au registre
    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);

    // Ajout du test "Test_point_input" à la suite de tests
    CU_add_test(suite, "Test_point_input", test_point_input);

    // Exécution des tests
    CU_basic_run_tests();

    // Nettoyage du registre de tests
    CU_cleanup_registry();

    return CU_get_error();
}
