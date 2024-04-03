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

# define K 3

void test_centro_fonction1();
/*
//Fonction pour connaitre la taille d'un point_t** donné
uint64_t size_of_point_t_array(point_t **array) {
    uint64_t size = 0;
    while (array[size] != NULL) {
        size++;
    }
    return size;
}*/
/*
//Fonction qui crée un cluster* à partir d'un point_t** donné
cluster_t* create_cluster(point_t **points, uint64_t size) {
    //uint64_t size = size_of_point_t_array(points);
    // Allocation de mémoire pour le cluster_t
    cluster_t *cluster = (cluster_t*)malloc(sizeof(cluster_t));
    if (cluster == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le cluster\n");
        return NULL;
    }

    // Assignation de la taille et des données
    cluster->size = size;
    cluster->data = (point_t*)malloc(size * sizeof(point_t));
    if (cluster->data == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les données du cluster\n");
        free(cluster);
        return NULL;
    }

    // Copie des pointeurs vers les données point_t
    for (uint64_t i = 0; i < size; i++) {
        cluster->data[i] = points[i] != NULL ? *points[i] : (point_t){0}; // Si le point est NULL, initialiser avec des valeurs par défaut
    }

    return cluster;
}*/
/*
// Fonction pour libérer la mémoire allouée pour un cluster_t
void free_cluster(cluster_t *cluster) {
    if (cluster != NULL) {
        if (cluster->data != NULL) {
            // Libération de la mémoire allouée pour les données du cluster
            for (uint64_t i = 0; i < cluster->size; i++) {
                if (cluster->data[i].coords != NULL) {
                    free(cluster->data[i].coords);
                }
            }
            free(cluster->data);
        }
        // Libération de la mémoire allouée pour le cluster
        free(cluster);
    }
}*/

void test_centro_fonction1(){
    FILE *file = fopen("../python/exemple.bin", "rb");
    if (!file) {
        perror("Erreur lors de l'ouverture du fichier binaire");
        exit(EXIT_FAILURE);
    }

    point_t **vectors = point_input(file);
    //uint32_t dim = 
    fclose(file);

    if (vectors == NULL) {
        fprintf(stderr, "La fonction point_input a renvoyé NULL\n");
        return;
    }
    
    //uint32_t dim = vectors[0]->dim;
    uint64_t size = vectors[0]->nbr_vector;
    cluster_t *cluster = (cluster_t*)malloc(sizeof(cluster_t));
    if (cluster == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour le cluster\n");
        return;
    }

    // Assignation de la taille et des données
    cluster->size = size;
    cluster->data = (point_t*)malloc(size * sizeof(point_t));
    if (cluster->data == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire pour les données du cluster\n");
        free(cluster);
        return;
    }

    // Copie des pointeurs vers les données point_t
    for (uint64_t i = 0; i < size; i++) {
        cluster->data[i] = vectors[i] != NULL ? *vectors[i] : (point_t){0}; // Si le point est NULL, initialiser avec des valeurs par défaut
    }
    //cluster_t clusters* = create_cluster(vectors, size);

    // Appel de la fonction à tester
    uint64_t result = update_centroids(cluster);

    // Vérification du résultat
    if (result == -1) {
        printf("La mise à jour des centroids a échoué\n");
        return;
    }
    else{
        ("Les centroids ont été mis à jour !\n");
    }

    // Vous pouvez effectuer d'autres validations ici si nécessaire
    // ...

    // Libération de la mémoire allouée pour les clusters et les vecteurs
    //free_clusters(cluster, K);
    //free_vectors(vectors, size);
    if (cluster == NULL) return;
    if (cluster != NULL) {
        if (cluster->data != NULL) {
            // Libération de la mémoire allouée pour les données du cluster
            for (uint64_t i = 0; i < cluster->size; i++) {
                if (cluster->data[i].coords != NULL) {
                    free(cluster->data[i].coords);
                }
            }
            free(cluster->data);
        }
        // Libération de la mémoire allouée pour le cluster
        free(cluster);
    }

    //free_vectors(vectors, size);
    if (vectors == NULL) return;
    for (uint64_t i = 0; i < size; i++) {
        if (vectors[i] != NULL) {
            free(vectors[i]->coords);
            free(vectors[i]);
        }
    }
    free(vectors);
}

    



