#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_thread.h"
#include "../headers/update_centroids.h" 
#include "../headers/kmeans_thread_args.h"

/**
 * Écrit les centroïdes dans un fichier au format spécifié.
 * 
 * @param file Pointeur vers le fichier dans lequel écrire les centroïdes.
 * @param centroid Tableau contenant les centroïdes des clusters.
 * @param k Nombre total de centroïdes à écrire.
 * @param dimension Dimension des points dans les centroïdes.
 */

void write_centro_thread(FILE *file, point_t *centroid, int32_t k, uint32_t dimension) {
    if (file == NULL || centroid == NULL) {
        fprintf(file, "Erreur : pointeur de fichier ou de centroïde invalide.\n");
        return;
    }

    fprintf(file, "[");
    for (int32_t i = 0; i < k; i++){
        fprintf(file, "(");
        for (uint32_t j = 0; j < dimension; j++) {
            fprintf(file, "%" PRId64, centroid[i].coords[j]);
            if (j < dimension - 1) {
                fprintf(file, ",");
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

void write_clu_thread(FILE *file, cluster_t **cluster, int32_t k, uint32_t dimension) {
    if (file == NULL || cluster == NULL) {
        fprintf(file, "Erreur : pointeur de fichier ou de cluster invalide.\n");
        return;
    }
    
    fprintf(file, "[");
    for (int32_t i = 0; i < k; i++) {
        fprintf(file, "[");
        for (int64_t j = 0; j < cluster[i]->size; j++) {
            if (j > 0) {
                fprintf(file, ",");
            }
            fprintf(file, "(");
            if (cluster[i]->data[j] == NULL || cluster[i]->data[j]->coords == NULL) {
                fprintf(file, "Erreur : point invalide dans le cluster.\n");
                continue;
            }
            for (uint32_t l = 0; l < dimension; l++) {
                fprintf(file, "%" PRId64, cluster[i]->data[j]->coords[l]);
                if (l < dimension - 1) {
                    fprintf(file, ",");
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
 * @param centroid_init Tableau des centroids initiaux pour chaque combinaison
 * @param centroid_final Tableau des centroids finaux pour chaque combinaison
 * @param clusters Tableau de tableaux de pointeurs vers les clusters pour chaque combinaison
 * @param k Nombre de clusters
 * @param dimension Nombre de dimensions des données
 * @param nombre_comb Nombre total de combinaisons
 * @param quiet_mode Si false les clusters sont également écrits
 */
void write_thread(FILE *output_file, uint64_t distortion, point_t *centroid_init, point_t *centroid_final, cluster_t **clusters, int32_t k, uint32_t dimension, int64_t nombre_comb, bool quiet ) {
    if (output_file == NULL) {
        printf("Erreur : pointeur de fichier de sortie invalide.\n");
        return;
    }
    if(quiet == true){
        fprintf(output_file, "\"");
        write_centro_thread(output_file, centroid_init, k, dimension);
        fprintf(output_file, "\",%" PRId64 ",\"", distortion);
        write_centro_thread(output_file, centroid_final, k, dimension);
        fprintf(output_file, "\"\n");
        
    }
    else{
        fprintf(output_file, "\"");
        write_centro_thread(output_file, centroid_init, k, dimension);
        fprintf(output_file, "\",%" PRId64 ",\"", distortion);
        write_centro_thread(output_file, centroid_final, k, dimension);
        fprintf(output_file, "\",\"");
        write_clu_thread(output_file, clusters, k, dimension);
        fprintf(output_file, "\"\n");
    }
    
    
}
