#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"

// Définir une fonction main de test
int main() {
    // Créer un fichier de sortie
    FILE *output_file = fopen("output_write.csv", "w");
    if (output_file == NULL) {
        perror("Erreur lors de l'ouverture du fichier de sortie");
        return EXIT_FAILURE;
    }

    // Définir les données de test
    uint64_t distortion[] = {10, 15, 20};
    int64_t k = 3;
    int64_t dimension = 2;
    int64_t nombre_comb = 3;

    // Allouer et initialiser des tableaux de points et de clusters pour le test
    point_t **centroid_init_Array = malloc(nombre_comb * sizeof(point_t *));
    point_t **centroid_final_Array = malloc(nombre_comb * sizeof(point_t *));
    cluster_t ***clustersArray = malloc(nombre_comb * sizeof(cluster_t **));

    for (int i = 0; i < nombre_comb; i++) {
        centroid_init_Array[i] = malloc(k * sizeof(point_t));
        centroid_final_Array[i] = malloc(k * sizeof(point_t));
        clustersArray[i] = malloc(k * sizeof(cluster_t *));

        for (int j = 0; j < k; j++) {
            centroid_init_Array[i][j].dim = dimension;
            centroid_init_Array[i][j].coords = malloc(dimension * sizeof(int64_t));
            centroid_final_Array[i][j].dim = dimension;
            centroid_final_Array[i][j].coords = malloc(dimension * sizeof(int64_t));

            for (int d = 0; d < dimension; d++) {
                centroid_init_Array[i][j].coords[d] = i + j + d; // Valeurs arbitraires pour le test
                centroid_final_Array[i][j].coords[d] = i * j * d; // Valeurs arbitraires pour le test
            }

            clustersArray[i][j] = malloc(sizeof(cluster_t));
            clustersArray[i][j]->size = j + 1; // Taille arbitraire pour le test
            clustersArray[i][j]->data = malloc((j + 1) * sizeof(point_t *));
            for (int l = 0; l <= j; l++) {
                clustersArray[i][j]->data[l] = &centroid_init_Array[i][j]; // Utilisation des mêmes points pour le test
            }
        }
    }

    // Appeler la fonction à tester
    write_csv(output_file, distortion, centroid_init_Array, centroid_final_Array, clustersArray, k, dimension, nombre_comb);

    // Libérer la mémoire allouée
    for (int i = 0; i < nombre_comb; i++) {
        for (int j = 0; j < k; j++) {
            free(centroid_init_Array[i][j].coords);
            free(centroid_final_Array[i][j].coords);
            free(clustersArray[i][j]->data);
            free(clustersArray[i][j]);
        }
        free(centroid_init_Array[i]);
        free(centroid_final_Array[i]);
        free(clustersArray[i]);
    }
    free(centroid_init_Array);
    free(centroid_final_Array);
    free(clustersArray);

    // Fermer le fichier de sortie
    fclose(output_file);

    return EXIT_SUCCESS;
}
