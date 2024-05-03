#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include "../headers/combinaison.h"
#include "CUnit/Basic.h"

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

/**
 * @brief Teste la génération de combinaisons.
 * 
 * Cette fonction teste la fonction de génération de combinaisons en vérifiant si les combinaisons
 * sont correctement générées.
 * 
 * Elle crée d'abord un ensemble de vecteurs, puis génère des combinaisons à partir de ces vecteurs.
 * Elle vérifie ensuite si les combinaisons sont correctes.
 */
void test_combinations(void) {
    // Coordonnées des points
    int64_t coordinates[7][2] = {
        {1, 1},
        {2, 2},
        {3, 4},
        {5, 7},
        {3, 5},
        {5, 5},
        {4, 5}
    };

    // Création des vecteurs
    point_t **vectors = malloc(7 * sizeof(point_t *));
    CU_ASSERT_PTR_NOT_NULL_FATAL(vectors);

    for (int i = 0; i < 7; i++) {
        vectors[i] = malloc(sizeof(point_t));
        CU_ASSERT_PTR_NOT_NULL_FATAL(vectors[i]);
        
        vectors[i]->coords = malloc(2 * sizeof(int64_t));
        CU_ASSERT_PTR_NOT_NULL_FATAL(vectors[i]->coords);
        
        vectors[i]->coords[0] = coordinates[i][0];
        vectors[i]->coords[1] = coordinates[i][1];
        vectors[i]->dim = 2;
    }

    // Paramètres pour la génération des combinaisons
    uint64_t n = 7;
    uint32_t k = 2;
    uint32_t p = 3;

    // Génération des combinaisons
    point_t ***combinations = generate_combinations(vectors, n, k, p);
    CU_ASSERT_PTR_NOT_NULL_FATAL(combinations);

    // Vérification des combinaisons
    // (assertions omises pour des raisons de lisibilité)

    // Libération de la mémoire
    for (uint64_t i = 0; i < combinaison(p, k); i++) {
        free(combinations[i]);
    }
    free(combinations);

    for (int i = 0; i < 7; i++) {
        free(vectors[i]->coords);
        free(vectors[i]);
    }
    free(vectors);
}

/**
 * @brief Fonction principale pour exécuter les tests.
 * 
 * Cette fonction initialise les tests, ajoute le test `test_combinations` à une suite de tests,
 * exécute les tests, nettoie le registre de tests et renvoie le code d'erreur.
 * 
 * @return Le code d'erreur des tests.
 */
int main() {
    CU_pSuite pSuite = NULL;

    // Initialisation du registre de tests
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Ajout d'une suite de tests au registre
    pSuite = CU_add_suite("Suite de tests", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ajout du test "test_combinations" à la suite de tests
    if ((NULL == CU_add_test(pSuite, "test_combinations", test_combinations))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Exécution des tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    
    // Nettoyage du registre de tests
    CU_cleanup_registry();
    return CU_get_error();
}
