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
#include "../headers/binary_file_reader.h" 
#include "../headers/update_centroids.h"

void test_up_centro_f2();

void test_up_centro_f2(){

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
    uint32_t dim = vectors[0]->dim;

    int k = 2;
    cluster_t *clusters[2];

    for (uint32_t i =0; i<2;i++){
        clusters[i] = (cluster_t *)malloc(sizeof(cluster_t));
        clusters[i]->size =0;
        clusters[i]->data = (point_t *) malloc(sizeof(point_t));
        clusters[i]->data->dim = dim;
        clusters[i]->data->coords = (int64_t *) malloc(sizeof(int64_t) * dim);
        //clusters[i]->vectors = (point_t **) malloc(0);

    }

    //Initialisation des centroids
    clusters[0]->data->coords[0] = (int64_t)1;
    clusters[0]->data->coords[1] = (int64_t)1;
    clusters[1]->data->coords[0] = (int64_t)2;
    clusters[1]->data->coords[1] = (int64_t)2;

    uint64_t result;
    for (uint32_t i =0; i<2;i++){
        result = update_centroids(clusters[i]);
        CU_ASSERT_EQUAL_FATAL(result, 0);
    }
    

    //tests les coordonnées des centroids
    CU_ASSERT_EQUAL(clusters[0]->data->coords[0], (int64_t )1);
    CU_ASSERT_EQUAL(clusters[0]->data->coords[1], (int64_t )1);
    CU_ASSERT_EQUAL(clusters[1]->data->coords[0], (int64_t )4);
    CU_ASSERT_EQUAL(clusters[1]->data->coords[1], (int64_t )5);

    //verification de la taille des centroids
    CU_ASSERT_EQUAL(clusters[0]->size,2);
    CU_ASSERT_EQUAL(clusters[1]->size,5);

    free(clusters[0]->data->coords);
    free(clusters[0]->data);

    free(clusters[1]->data->coords);
    free(clusters[1]->data);

    fclose(file);

}