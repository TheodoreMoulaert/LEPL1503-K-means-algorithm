#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"
#include "../headers/update_centroids.h" 

/**
 * Écrit les centroïdes dans un fichier au format spécifié.
 * 
 * @param file Pointeur vers le fichier dans lequel écrire les centroïdes.
 * @param centroid Tableau contenant les centroïdes des clusters.
 * @param k Nombre total de centroïdes à écrire.
 * @param dimension Dimension des points dans les centroïdes.
 */

void write_centroid(FILE *file, point_t* centroid, int32_t k, uint32_t dimension) {
    if (file == NULL || centroid == NULL) {
        fprintf(file, "Erreur : pointeur de fichier ou de centroïde invalide.\n");
        return;
    }

    fprintf(file, "["); 
    for (int32_t i = 0; i < k; i++){
        fprintf(file, "(");
        for (int j = 0; j < dimension; j++) {
            fprintf(file, "%" PRId64, centroid[i].coords[j]);
            if (j < dimension - 1) {
                fprintf(file, ", ");
            }
        }
        fprintf(file, ")");
        if (i < k - 1){
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]");
}

/**
 * Écrit les clusters dans un fichier au format spécifié.
 * 
 * @param file Pointeur vers le fichier dans lequel écrire les clusters.
 * @param cluster Tableau de pointeurs vers les clusters.
 * @param k Nombre total de clusters.
 * @param dimension Dimension des points dans les clusters.
 */

void write_cluster(FILE *file, cluster_t **cluster, int32_t k, uint32_t dimension) {
    if (file == NULL || cluster == NULL) {
        fprintf(file, "Erreur : pointeur de fichier ou de cluster invalide.\n");
        return;
    }
    
    fprintf(file, "[");
    for (int32_t i = 0; i < k; i++) {
        fprintf(file, "[");
        for (int64_t j = 0; j < cluster[i]->size; j++) {
            if (j > 0) {
                fprintf(file, ", ");
            }
            fprintf(file, "(");
            if (cluster[i]->data[j] == NULL || cluster[i]->data[j]->coords == NULL) {
                fprintf(file, "Erreur : point invalide dans le cluster.\n");
                continue;
            }
            for (int64_t l = 0; l < dimension; l++) {
                fprintf(file, "%" PRId64, cluster[i]->data[j]->coords[l]);
                if (l < dimension - 1) {
                    fprintf(file, ", ");
                }
            }
            fprintf(file, ")");
        }
        fprintf(file, "]");
        if (i < k - 1) {
            fprintf(file, ", ");
        }
    }
    fprintf(file, "]");
}


/**
 * @brief Écrit les données de clustering dans un fichier CSV.
 * 
 * @param output_file Pointeur vers le fichier de sortie
 * @param distortion Tableau des valeurs de distorsion
 * @param centroid_init_Array Tableau des centroids initiaux pour chaque combinaison
 * @param centroid_final_Array Tableau des centroids finaux pour chaque combinaison
 * @param clustersArray Tableau de tableaux de pointeurs vers les clusters pour chaque combinaison
 * @param k Nombre de clusters
 * @param dimension Nombre de dimensions des données
 * @param nombre_comb Nombre total de combinaisons
 * @param quiet_mode Si false les clusters sont également écrits
 */
void write_csv(FILE *output_file, uint64_t* distortion, point_t **centroid_init_Array, point_t **centroid_final_Array, cluster_t ***clustersArray, int32_t k, uint32_t dimension, int64_t nombre_comb, bool quiet_mode ) {
    if (output_file == NULL) {
        printf("Erreur : pointeur de fichier de sortie invalide.\n");
        return;
    }
    if(quiet_mode == true){
        fprintf(output_file, "initialization centroids,distortion,centroids\n");
        for (int64_t i = 0; i < nombre_comb; i++) {
            fprintf(output_file, "\"");
            write_centroid(output_file, centroid_init_Array[i], k, dimension);
            fprintf(output_file, "\",%" PRId64 ",\"", distortion[i]);
            write_centroid(output_file, centroid_final_Array[i], k, dimension);
            fprintf(output_file, "\"\n");
        }

    }
    else{
        fprintf(output_file, "initialization centroids,distortion,centroids,clusters\n");

        for (int64_t i = 0; i < nombre_comb; i++) {
            fprintf(output_file, "\"");
            write_centroid(output_file, centroid_init_Array[i], k, dimension);
            fprintf(output_file, "\",%" PRId64 ",\"", distortion[i]);
            write_centroid(output_file, centroid_final_Array[i], k, dimension);
            fprintf(output_file, "\",\"");
            write_cluster(output_file, clustersArray[i], k, dimension);
            fprintf(output_file, "\"\n");
        }

    }
}
