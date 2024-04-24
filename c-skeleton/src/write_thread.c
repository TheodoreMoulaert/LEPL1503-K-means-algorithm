#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"
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

void write_centro_thread(FILE *file, point_t *centroid, int64_t k, int64_t dimension) {
    if (file == NULL || centroid == NULL) {
        fprintf(file, "Erreur : pointeur de fichier ou de centroïde invalide.\n");
        return;
    }

    fprintf(file, "[");
    for (int i = 0; i < k; i++){
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

void write_clu_thread(FILE *file, cluster_t *cluster, int64_t k, int64_t dimension) {
    if (file == NULL || cluster == NULL) {
        fprintf(file, "Erreur : pointeur de fichier ou de cluster invalide.\n");
        return;
    }
    
    fprintf(file, "[");
    for (int64_t i = 0; i < k; i++) {
        fprintf(file, "[");
        for (int64_t j = 0; j < cluster->size; j++) {
            if (j > 0) {
                fprintf(file, ", ");
            }
            fprintf(file, "(");
            if (cluster->data[j] == NULL || cluster->data[j]->coords == NULL) {
                fprintf(file, "Erreur : point invalide dans le cluster.\n");
                continue;
            }
            for (int64_t l = 0; l < dimension; l++) {
                fprintf(file, "%" PRId64, cluster->data[j]->coords[l]);
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
 */
void write_thread(FILE *output_file, uint64_t distortion, point_t *centroid_init, point_t *centroid_final, cluster_t **clusters, int64_t k, int64_t dimension, int64_t nombre_comb) {
    if (output_file == NULL) {
        printf("Erreur : pointeur de fichier de sortie invalide.\n");
        return;
    }

    fprintf(output_file, "initialization centroids,distortion,centroids,clusters\n"); //A mettre dans le main ??? 

    
    fprintf(output_file, "\"");
    write_centroid(output_file, centroid_init, k, dimension);
    fprintf(output_file, "\",%" PRId64 ",\"", distortion);
    write_centroid(output_file, centroid_final, k, dimension);
    fprintf(output_file, "\",\"");
    write_cluster(output_file, clusters, k, dimension);
    fprintf(output_file, "\"\n");
    
}
