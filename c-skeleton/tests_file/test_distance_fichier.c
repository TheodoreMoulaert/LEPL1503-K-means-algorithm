#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>


#include "../headers/distance.h" 
#include "../headers/point.h" 
#include "../headers/binary_file_reader.h" 

// déclaration
void test_distance_functions();

void test_distance_functions() {


    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }
    // on récupère les données du fichier binaires

    point_t **vectors = point_input(file);

   
    fclose(file);

   
    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }



    uint64_t vector_count = vectors[0]->nbr_vector;


    if (vector_count < 2) {
        fprintf(stderr, "Il n'y a pas suffisamment de vecteurs pour tester les distances\n");
        return;
    }

    CU_ASSERT_TRUE(vector_count >= 2);

   
    point_t *first_vector = vectors[0];

    for (int i = 1; i < vector_count; i++) {


        int64_t manhattan_dist = squared_manhattan_distance(first_vector, vectors[i]);
        int64_t euclidean_dist = squared_euclidean_distance(first_vector, vectors[i]);

        // printf pour voir où se situe les erreurs éventuelles

        printf("Distance de Manhattan au carré entre le premier vecteur et le vecteur %d : %" PRId64 "\n", i + 1, manhattan_dist);
        printf("Distance euclidienne au carré entre le premier vecteur et le vecteur %d : %" PRId64 "\n", i + 1, euclidean_dist);

        // assert équal en fonction des distance calculées
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
    free_vectors(vectors, vector_count);
}

int main() {
    CU_initialize_registry(); 

    CU_pSuite suite = CU_add_suite("Suite_de_tests", NULL, NULL);

    CU_add_test(suite, "Test_distance_functions", test_distance_functions);

    CU_basic_run_tests();

    CU_cleanup_registry();

    return CU_get_error();
}