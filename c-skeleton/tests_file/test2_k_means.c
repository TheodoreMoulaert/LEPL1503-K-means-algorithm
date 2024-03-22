#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <stdbool.h>
#include <stdio.h>
//#include <assert.h>
#include <stdlib.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"

void test_k_means() {
    // Définir les valeurs initiales pour le test
    /*cluster_t initial_centroids = {
        .size = 2,
        .data = (point_t[]){
            {.dim = 2, .coords = (int64_t[]){1, 1}},
            {.dim = 2, .coords = (int64_t[]){5, 5}}
        }
    };*/
    cluster_t initial_centroids;
    
    initial_centroids.size = 2; // Nombre de points dans chaque cluster
    initial_centroids.data = (point_t*)malloc(2 * sizeof(point_t));
    if (initial_centroids.data == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les données initiales des centroids\n");
        exit(EXIT_FAILURE);
    }
    for (uint32_t i = 0; i < 2; i++) {
        initial_centroids.data[i].dim = 2; // Nombre de dimensions des points
        initial_centroids.data[i].coords = (int64_t*)malloc(2 * sizeof(int64_t));
        if (initial_centroids.data[i].coords == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les coordonnées des centroids\n");
            exit(EXIT_FAILURE);
        }
        initial_centroids.data[i].coords[0] = i; // Valeurs arbitraires pour les coordonnées
        initial_centroids.data[i].coords[1] = i + 1;
    }
    

    point_t *vectors[3];
    for (int i = 0; i < 3; i++) {
        vectors[i] = (point_t *)malloc(sizeof(point_t));
        if (vectors[i] == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour le vecteur %d\n", i);
            exit(EXIT_FAILURE);
        }
        vectors[i]->dim = 2;
        vectors[i]->coords = (int64_t *)malloc(2 * sizeof(int64_t));
        if (vectors[i]->coords == NULL) {
            fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les coordonnées du vecteur %d\n", i);
            exit(EXIT_FAILURE);
        }
        vectors[i]->coords[0] = i;
        vectors[i]->coords[1] = i;
    }

    uint32_t dimensions = 2;
    uint64_t num_vectors = 3;
    uint32_t K = 2;
    squared_distance_func_t distance_func = squared_euclidean_distance;
     

    // Appel de la fonction à tester
    cluster_t *clusters = k_means(initial_centroids, K, vectors, num_vectors, dimensions,distance_func);
    fprintf(stderr, "Best clusters: :\n");
    for (uint64_t i = 0; i < sol_clusters->size; ++i) {
        fprintf(stderr, "Cluster %d : (%" PRId64 ",%" PRId64 ")\n", i + 1, sol_clusters->data[i].coords[0], sol_clusters->data[i].coords[1]);
    }
    // Vérifier les résultats
    CU_ASSERT_PTR_NOT_NULL(clusters);

    // Nettoyage de la mémoire
    /*for (int i = 0; i < K; i++) {
        for (uint64_t j = 0; j < clusters[i].size; j++) {
            free(clusters[i].data[j].coords);
        }
        free(clusters[i].data);
    }
    free(clusters);*/
    
    for (int i = 0; i < num_vectors; i++) {
        free(vectors[i]->coords);
        free(vectors[i]);
    }
    free(initial_centroids.data);
    free(clusters);
}
int main() {
    // Initialiser le registre de tests
    CU_initialize_registry();

    // Ajouter une suite de tests
    CU_pSuite suite = CU_add_suite("Suite de tests pour k_means", NULL, NULL);
    CU_add_test(suite, "Test de k_means", test_k_means);

    // Exécuter les tests
    CU_basic_run_tests();

    // Nettoyer le registre de tests
    CU_cleanup_registry();

    return 0;
}
/*void test_k_means() {
    // Définir les valeurs initiales pour le test
    cluster_t initial_centroids = {
        .size = 2,
        .data = (point_t[]){
            {.dim = 2, .coords = (int64_t[]){1, 1}},
            {.dim = 2, .coords = (int64_t[]){5, 5}}
        }
    };

    point_t *vectors[3];
    for (int i = 0; i < 3; i++) {
        vectors[i] = (point_t *)malloc(sizeof(point_t));
        vectors[i]->dim = 2;
        vectors[i]->coords = (int64_t *)malloc(2 * sizeof(int64_t));
        vectors[i]->coords[0] = i;
        vectors[i]->coords[1] = i;
    }

    uint32_t dimensions = 2;
    uint64_t num_vectors = 3;
    uint32_t K = 2;
    squared_distance_func_t distance_func = squared_euclidean_distance;
     

    // Appel de la fonction à tester
    cluster_t *clusters = k_means(initial_centroids, K, vectors, num_vectors, dimensions,distance_func);

    // Vérifier les résultats
    CU_ASSERT_PTR_NOT_NULL(clusters);

    for (int i = 0; i < K; i++) {
        free(clusters[i].data->coords);
    }
    free(clusters);

    // Nettoyage de la mémoire
    for (int i = 0; i < K; i++) {
        free(clusters[i].data);
        free(clusters[i].center.coords);
    }
    free(clusters);
    for (int i = 0; i < num_vectors; i++) {
        free(vectors[i]->coords);
        free(vectors[i]);
    }
}

int main() {
    // Initialiser le registre de tests
    CU_initialize_registry();

    // Ajouter une suite de tests
    CU_pSuite suite = CU_add_suite("Suite de tests pour k_means", NULL, NULL);
    CU_add_test(suite, "Test de k_means", test_k_means);

    // Exécuter les tests
    CU_basic_run_tests();

    // Nettoyer le registre de tests
    CU_cleanup_registry();

    return 0;
}*/


//test_k_means : tests_file/test2_k_means.c src/k_means.o src/update_centroids.o src/distance.o src/assign_vector_to_centro.o
	//$(CC) $(INCLUDE_HEADERS_DIRECTORY) $(CFLAGS) -o $@ $^ $(LIBS)

