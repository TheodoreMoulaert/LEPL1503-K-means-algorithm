<<<<<<< HEAD:c-skeleton/tests_file/test_update_centroids.c
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
//#include "../headers/main.h"


// Définition des constantes pour les tests
//est ce que je peux faire ça ? ou je dois initialiser ca comment sinon
#define K 3
#define DIMENSION 2

// Fonction de  test
void test_update_centroids() {
    // Création des clusters pour le test
    cluster_t clusters[K];
    for (int i = 0; i < K; i++) {
        clusters[i].size = 3; // Taille de chaque cluster
        clusters[i].data = (point_t*)malloc(3 * sizeof(point_t));
        if (clusters[i].data == NULL) {
            // Gestion de l'erreur : échec de l'allocation de mémoire pour les clusters
            CU_FAIL("Erreur d'allocation de mémoire pour les clusters");
            return;
        }
        for (int j = 0; j < 3; j++) {
            clusters[i].data[j].dim =DIMENSION;
            clusters[i].data[j].coords = (int64_t*)malloc(DIMENSION * sizeof(int64_t));
            if (clusters[i].data[j].coords == NULL) {
                // Gestion de l'erreur : échec de l'allocation de mémoire pour les coordonnées des points
                CU_FAIL("Erreur d'allocation de mémoire pour les coordonnées des points");
                for (int k = 0; k < j; k++) {
                    free(clusters[i].data[k].coords);
                }
                free(clusters[i].data);
                return;
            }
            // Initialisation des coordonnées avec des valeurs arbitraires pour le test
            for (int k = 0; k < DIMENSION; k++) {
                clusters[i].data[j].coords[k] = i * 10 + j;
            }
        }
    }

    // Appel de la fonction à tester
    uint64_t result = update_centroids(clusters);

    // Vérification du résultat
    CU_ASSERT_EQUAL_FATAL(result, 0); // Échoue le test si la mise à jour des centroids a échoué
    //fprintf(stderr,"Correct");
    // Nettoyage
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < 3; j++) {
            free(clusters[i].data[j].coords);
        }
        free(clusters[i].data);
    }
}

int main() {
    // Initialisation du framework de test
    CU_initialize_registry();

    // Ajout des tests à la suite de tests
    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);
    CU_add_test(suite, "test_update_centroids", test_update_centroids);

    // Exécution des tests
    CU_basic_run_tests();

    // Nettoyage
    CU_cleanup_registry();
    return 0;
=======
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <CUnit/Basic.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
//#include "../headers/main.h"


// Définition des constantes pour les tests
//est ce que je peux faire ça ? ou je dois initialiser ca comment sinon
#define K 3
#define DIMENSION 2

// Fonction de test
void test_update_centroids() {
    // Création des clusters pour le test
    cluster_t clusters[K];
    for (int i = 0; i < K; i++) {
        clusters[i].size = 3; // Taille de chaque cluster
        clusters[i].data = (point_t*)malloc(3 * sizeof(point_t));
        if (clusters[i].data == NULL) {
            // Gestion de l'erreur : échec de l'allocation de mémoire pour les clusters
            CU_FAIL("Erreur d'allocation de mémoire pour les clusters");
            return;
        }
        for (int j = 0; j < 3; j++) {
            clusters[i].data[j].dim =DIMENSION;
            clusters[i].data[j].coords = (int64_t*)malloc(DIMENSION * sizeof(int64_t));
            if (clusters[i].data[j].coords == NULL) {
                // Gestion de l'erreur : échec de l'allocation de mémoire pour les coordonnées des points
                CU_FAIL("Erreur d'allocation de mémoire pour les coordonnées des points");
                for (int k = 0; k < j; k++) {
                    free(clusters[i].data[k].coords);
                }
                free(clusters[i].data);
                return;
            }
            // Initialisation des coordonnées avec des valeurs arbitraires pour le test
            for (int k = 0; k < DIMENSION; k++) {
                clusters[i].data[j].coords[k] = i * 10 + j;
            }
        }
    }

    // Appel de la fonction à tester
    uint64_t result = update_centroids(clusters);

    // Vérification du résultat
    CU_ASSERT_EQUAL_FATAL(result, 0); // Échoue le test si la mise à jour des centroids a échoué
    //fprintf(stderr,"Correct");
    // Nettoyage
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < 3; j++) {
            free(clusters[i].data[j].coords);
        }
        free(clusters[i].data);
    }
}

int main() {
    // Initialisation du framework de test
    CU_initialize_registry();

    // Ajout des tests à la suite de tests
    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);
    CU_add_test(suite, "test_update_centroids", test_update_centroids);

    // Exécution des tests
    CU_basic_run_tests();

    // Nettoyage
    CU_cleanup_registry();
    return 0;
>>>>>>> 8d9f4c0 (test):c-skeleton/tests/test_update_centroids.c
}