#include <stdio.h>
#include <stdlib.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"

int main() {
    FILE *output_file = fopen("output.csv", "w");
    if (output_file == NULL) {
        printf("Erreur lors de l'ouverture du fichier de sortie.\n");
        return EXIT_FAILURE;
    }

    int64_t distortion[] = {10, 20, 30}; // Exemple de tableau de distorsion
    int64_t k = 3; // Exemple de nombre de clusters
    int64_t dimension = 2; // Exemple de dimension des points
    int64_t nombre_comb = 3; // Exemple de nombre de combinaisons

    // Exemple de tableaux de points initiaux et finaux
    point_t **centroid_init_Array = (point_t **)malloc(nombre_comb * sizeof(point_t *));
    point_t **centroid_final_Array = (point_t **)malloc(nombre_comb * sizeof(point_t *));
    // Exemple de tableau de tableaux de clusters
    cluster_t ***clustersArray = (cluster_t ***)malloc(nombre_comb * sizeof(cluster_t **));

    // Vérification si l'allocation dynamique a réussi
    if (centroid_init_Array == NULL || centroid_final_Array == NULL || clustersArray == NULL) {
        printf("Erreur lors de l'allocation de mémoire.\n");
        return EXIT_FAILURE;
    }

    // Initialisation des tableaux avec des valeurs factices pour le test
    for (int64_t i = 0; i < nombre_comb; i++) {
        centroid_init_Array[i] = (point_t *)malloc(sizeof(point_t));
        centroid_final_Array[i] = (point_t *)malloc(sizeof(point_t));
        clustersArray[i] = (cluster_t **)malloc((k + 1) * sizeof(cluster_t *));

        // Vérification si l'allocation dynamique a réussi
        if (centroid_init_Array[i] == NULL || centroid_final_Array[i] == NULL || clustersArray[i] == NULL) {
            printf("Erreur lors de l'allocation de mémoire.\n");
            return EXIT_FAILURE;
        }

        centroid_init_Array[i]->dim = dimension;
        centroid_init_Array[i]->coords = (int64_t *)malloc(dimension * sizeof(int64_t));
        centroid_final_Array[i]->dim = dimension;
        centroid_final_Array[i]->coords = (int64_t *)malloc(dimension * sizeof(int64_t));

        // Vérification si l'allocation dynamique a réussi
        if (centroid_init_Array[i]->coords == NULL || centroid_final_Array[i]->coords == NULL) {
            printf("Erreur lors de l'allocation de mémoire.\n");
            return EXIT_FAILURE;
        }

        for (int64_t j = 0; j < dimension; j++) {
            centroid_init_Array[i]->coords[j] = i * j; // Valeurs factices
            centroid_final_Array[i]->coords[j] = i * j + 5; // Valeurs factices
        }

        clustersArray[i][0] = (cluster_t *)malloc(sizeof(cluster_t));
        clustersArray[i][0]->size = 3;
        clustersArray[i][0]->data = (point_t **)malloc(clustersArray[i][0]->size * sizeof(point_t *));

        // Vérification si l'allocation dynamique a réussi
        if (clustersArray[i][0] == NULL || clustersArray[i][0]->data == NULL) {
            printf("Erreur lors de l'allocation de mémoire.\n");
            return EXIT_FAILURE;
        }

        for (int64_t j = 0; j < clustersArray[i][0]->size; j++) {
            clustersArray[i][0]->data[j] = (point_t *)malloc(sizeof(point_t));

            // Vérification si l'allocation dynamique a réussi
            if (clustersArray[i][0]->data[j] == NULL) {
                printf("Erreur lors de l'allocation de mémoire.\n");
                return EXIT_FAILURE;
            }

            clustersArray[i][0]->data[j]->dim = dimension;
            clustersArray[i][0]->data[j]->coords = (int64_t *)malloc(dimension * sizeof(int64_t));

            // Vérification si l'allocation dynamique a réussi
            if (clustersArray[i][0]->data[j]->coords == NULL) {
                printf("Erreur lors de l'allocation de mémoire.\n");
                return EXIT_FAILURE;
            }

            for (int64_t d = 0; d < dimension; d++) {
                clustersArray[i][0]->data[j]->coords[d] = i * j * d; // Valeurs factices
            }
        }
    }

    // Appel de la fonction write_csv
    write_csv(output_file, distortion, centroid_init_Array, centroid_final_Array, clustersArray, k, dimension, nombre_comb);

    // Libération de la mémoire allouée
    for (int64_t i = 0; i < nombre_comb; i++) {
        free(centroid_init_Array[i]->coords);
        free(centroid_init_Array[i]);
        free(centroid_final_Array[i]->coords);
        free(centroid_final_Array[i]);

        for (int64_t j = 0; j < clustersArray[i][0]->size; j++) {
            free(clustersArray[i][0]->data[j]->coords);
            free(clustersArray[i][0]->data[j]);
        }
        free(clustersArray[i][0]->data);
        free(clustersArray[i][0]);
        free(clustersArray[i]);
    }
    free(centroid_init_Array);
    free(centroid_final_Array);
    free(clustersArray);

    fclose(output_file);
    return EXIT_SUCCESS;
}
