#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <CUnit/Basic.h>
#include <stdint.h>
#include <string.h>
#include <getopt.h>
#include <errno.h>
#include <inttypes.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h" 
#include "../headers/binary_file_avec_cluster.h" 
#include "../headers/update_centroids.h"

void test_up_centro_f1();

void test_up_centro_f1() {
    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror(" Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    // On récupère les données du fichier binaire
    point_t **vectors = point_input(file);
    fclose(file);

    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }
    //uint64_t size_clu = size_clusters(vectors); //1
    uint32_t dim = vectors[0]->dim; //2
    uint64_t vector_count = vectors[0]->nbr_vector; //7

    //uint32_t K = (uint64_t)size_clu; //nombre de centroids à trouver
    uint32_t K = 2;
    cluster_t clusters[K];//[size_clusters];
    for (int i = 0; i < K; i++){
        //vector_count = vector_count/K;
        clusters[i].size = vector_count;
        clusters[i].data = (point_t*)malloc(vector_count* sizeof(point_t));//vector_count
        //clusters[i].size = clusters[i].data->nbr_vector;//size_clusters(clusters[i]); // Taille de chaque cluster

        if (clusters[i].data == NULL) {
            // Gestion de l'erreur : échec de l'allocation de mémoire pour les clusters
            CU_FAIL("Erreur d'allocation de mémoire pour les clusters");
            return;
        }

        for (int j = 0; j < vector_count; j++) { //vector_count
            clusters[i].data[j].dim = dim;
            clusters[i].data[j].coords = (int64_t*)malloc(dim * sizeof(int64_t));

            if (clusters[i].data[j].coords == NULL) {
                // Gestion de l'erreur : échec de l'allocation de mémoire pour les coordonnées des points
                CU_FAIL("Erreur d'allocation de mémoire pour les coordonnées des points");

                for (int k = 0; k < j; k++) {
                    free(clusters[i].data[k].coords);
                }

                free(clusters[i].data);
                return;
            }

            for (int d=0;d<dim;d++){
                clusters[i].data[j].coords[d] = vectors[i]->coords[d];
            }  
        }
    }
    // Initialisation des coordonnées avec les valeurs du test
    /*clusters[0].data[0].coords[0] = (int64_t)1;
    clusters[0].data[0].coords[1] = (int64_t)1;

    clusters[0].data[1].coords[0] = (int64_t)2;
    clusters[0].data[1].coords[1] = (int64_t)2;


    clusters[0].data[2].coords[0] = (int64_t)3;
    clusters[0].data[2].coords[1] = (int64_t)4;

    clusters[1].data[0].coords[0] = (int64_t)5;
    clusters[1].data[0].coords[1] = (int64_t)7;

    clusters[1].data[1].coords[0] = (int64_t)3;
    clusters[1].data[1].coords[1] = (int64_t)5;

    clusters[1].data[2].coords[0] = (int64_t)5;
    clusters[1].data[2].coords[1] = (int64_t)5;

    clusters[1].data[3].coords[0] = (int64_t)4;
    clusters[1].data[3].coords[1] = (int64_t)5;*/

    cluster_t result;
    result = update_centroids(clusters, K);
    //CU_ASSERT_EQUAL_FATAL(result, 0);
    fprintf(stderr, "La fonction update_centroids n'a pas d'erreurs !\n");

    // Tests sur les coordonnées des centroids
    CU_ASSERT_EQUAL(result.data[0].coords[0], (int64_t)1);
    CU_ASSERT_EQUAL(result.data[0].coords[1], (int64_t)1);
    fprintf(stderr, "Le premier centroid a les coordonnées : (%" PRId64 ",%" PRId64 ") \n", result.data[0].coords[0], result.data[0].coords[1]);
    CU_ASSERT_EQUAL(result.data[1].coords[0], (int64_t)2);
    CU_ASSERT_EQUAL(result.data[1].coords[1], (int64_t)2);
    fprintf(stderr, "Le deuxième centroid a les coordonnées : (%" PRId64 ",%" PRId64 ") \n", result.data[1].coords[0], result.data[1].coords[1]);
    //fprintf(stderr, "taille du premier centro : %" PRId64 " \n", result.size);
//clusters[i].size
    //fprintf(stderr, "Le deuxième centroid a les coordonnées : (%" PRId64 ",%" PRId64 ") \n", clusters[1].data[6].coords[0], clusters[0].data[0].coords[1]);
    //fprintf(stderr, "Le deuxième centroid a les coordonnées : (%" PRId64 ",%" PRId64 ") \n", clusters[1].data[0].coords[0], clusters[1].data[0].coords[1]);
    //fprintf(stderr, "Le deuxième centroid a les coordonnées : (%" PRId64 ",%" PRId64 ") \n", clusters[0].data[1].coords[0], clusters[0].data[1].coords[1]);
    //fprintf(stderr, "Le deuxième centroid a les coordonnées : (%" PRId64 ",%" PRId64 ") \n", clusters[1].data[1].coords[0], clusters[1].data[1].coords[1]);
    //fprintf(stderr, "clusters->data->nbr_vector : (%" PRId64 ",%" PRId64 ") \n", clusters->data->nbr_vector, clusters[1].data[1].coords[1]);
    // Vérification de la taille des centroids
    /*CU_ASSERT_EQUAL(clusters->size, 1);*/

    /*free(clusters[0].data[0].coords);
    free(clusters[0].data[1].coords);
    free(clusters[0].data);
    free(clusters[1].data[0].coords);
    free(clusters[1].data[1].coords);
    free(clusters[1].data);*/
    //free(clusters);
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < vector_count; j++) { //vector_count
            free(clusters[i].data[j].coords);
        }
        free(clusters[i].data);
    }
    //fclose(file);
}

int main() {
    // Initialisation du registre des tests
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Ajout des suites de tests
    CU_pSuite pSuite = NULL;
    pSuite = CU_add_suite("Suite de tests pour update_centroids", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Ajout des tests à la suite
    if ((NULL == CU_add_test(pSuite, "Test de la fonction update_centroids", test_up_centro_f1))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Exécution des tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
