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
    uint64_t size_clusters = vectors[0]->nbr_vector;
    uint32_t dim = vectors[0]->dim; //2


    uint32_t K = 1; //nombre de centroids à trouver

    cluster_t clusters[size_clusters];
    for (int i = 0; i < size_clusters; i++) {
        clusters[i].size = size_clusters; // Taille de chaque cluster
        clusters[i].data = (point_t*)malloc(dim * sizeof(point_t));
        if (clusters[i].data == NULL) {
            // Gestion de l'erreur : échec de l'allocation de mémoire pour les clusters
            CU_FAIL("Erreur d'allocation de mémoire pour les clusters");
            return;
        }
        for (int j = 0; j < dim; j++) {
            clusters[i].data[j].dim =dim;
            clusters[i].data[j].coords = (int64_t*)malloc(dim* sizeof(int64_t));
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
            /*for (int k = 0; k < dim; k++) {
                clusters[i].data[j].coords[k] = i * 10 + j;
            }*/
            clusters[0].data[0].coords[0] = (int64_t)1;
            clusters[0].data[0].coords[1] = (int64_t)1;
            clusters[0].data[1].coords[0] = (int64_t)2;
            clusters[0].data[1].coords[1] = (int64_t)2;
        }
    }

    /*cluster_t *clusters;//*clusters[2];
    //clusters = (cluster_t)malloc(sizeof(cluster_t));
    for (uint32_t i =0; i<1;i++){
        clusters = (point_t*)malloc(sizeof(cluster_t));
        if (clusters == NULL){
            free(clusters);
            return ;
        }
        clusters->size = 2;
        clusters->data = (point_t *) malloc(sizeof(point_t));
        if (clusters->data == NULL){
            free(clusters->data);
            free(clusters);
            return ;
        }
        clusters->data->dim = dim;
        clusters->data->coords = (int64_t *) malloc(sizeof(int64_t) * dim);
        if (clusters->data->coords ==NULL){
            free(clusters->data->coords);
            free(clusters->data);
            free(clusters);
            return ;
        }
        //clusters[i]->vectors = (point_t **) malloc(0);
    }*/



    //Création du clusters
    /*clusters->data->coords[0] = (int64_t)1;
    clusters->data->coords[1] = (int64_t)1;
    clusters->data->coords[0] = (int64_t)2;
    clusters->data->coords[1] = (int64_t)2;*/
    //Initialisation des centroids
    /*clusters[0]->data->coords[0] = (int64_t)1;
    clusters[0]->data->coords[1] = (int64_t)1;
    clusters[1]->data->coords[0] = (int64_t)2;
    clusters[1]->data->coords[1] = (int64_t)2;*/
    
    /*for (uint32_t i =0; i<2;i++){
        result = update_centroids(clusters[i]);
        CU_ASSERT_EQUAL_FATAL(result, 0);
    }*/
    uint64_t result;
    result = update_centroids(clusters);
    CU_ASSERT_EQUAL_FATAL(result, 0);
    fprintf(stderr, "La fonction update_centroids n'a pas d'erreurs !\n");

    //tests les coordonnées des centroids
    CU_ASSERT_EQUAL(clusters->data->coords[0], (int64_t)1);
    CU_ASSERT_EQUAL(clusters->data->coords[1], (int64_t)1);
    fprintf(stderr, "Le premier centroids a les coordonnées : (1,1) \n");

    //CU_ASSERT_EQUAL(clusters->data[1]->coords[0], (int64_t )4);
    //CU_ASSERT_EQUAL(clusters->data[1]->coords[1], (int64_t )5);

    //verification de la taille des centroids
    CU_ASSERT_EQUAL(clusters->size,1);
    //CU_ASSERT_EQUAL(clusters[1]->size,5);

    free(clusters->data->coords);
    //free(clusters->data[0]);
    free(clusters->data);
    //free(clusters->data->coords);
    //free(clusters->data[1]);
    fclose(file);

}