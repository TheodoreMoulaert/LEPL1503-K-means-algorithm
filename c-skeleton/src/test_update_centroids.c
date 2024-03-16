#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
//#include "unity.h"

#include <CUnit/Basic.h>
#include "../headers/update_centroids.h"

// Définition de la constante K
#define K 3

// Déclaration de la fonction à tester
int64_t update_centroids(cluster_t *clusters);

// Fonction de configuration des tests
void setUp(void) {}

// Fonction de nettoyage des tests
void tearDown(void) {}

// Test de la fonction update_centroids
void test_update_centroids(void) {
    // Création des données de test
    cluster_t clusters[K];
    for (int i = 0; i < K; i++) {
        clusters[i].data = (point_t *)malloc(sizeof(point_t));
        clusters[i].data->dim = 2;
        clusters[i].data->coord = (int64_t *)malloc(2 * sizeof(int64_t));
        clusters[i].data->coord[0] = i;
        clusters[i].data->coord[1] = i + 1;
    }

    // Appel de la fonction à tester
    int64_t result = update_centroids(clusters);

    // Vérification du résultat
    TEST_ASSERT_EQUAL_INT64(0, result);

    // Libération de la mémoire allouée
    for (int i = 0; i < K; i++) {
        free(clusters[i].data->coord);
        free(clusters[i].data);
    }
}

int main(void) {
    
    UNITY_BEGIN();
    RUN_TEST(test_update_centroids);
    return UNITY_END();
} 