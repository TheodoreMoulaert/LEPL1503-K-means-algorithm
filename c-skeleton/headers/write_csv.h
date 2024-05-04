#ifndef WRITE_CSV_H
#define WRITE_CSV_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> 
#include "../headers/point.h"
#include "../headers/cluster.h"
/**
 * Écrit les centroïdes dans un fichier au format spécifié.
 * 
 * @param file Pointeur vers le fichier dans lequel écrire les centroïdes.
 * @param centroid Tableau contenant les centroïdes des clusters.
 * @param k Nombre total de centroïdes à écrire.
 * @param dimension Dimension des points dans les centroïdes.
 */
void write_centroid(FILE *file, point_t* centroid, int32_t k, uint32_t dimension);

/**
 * Écrit les clusters dans un fichier au format spécifié.
 * 
 * @param file Pointeur vers le fichier dans lequel écrire les clusters.
 * @param cluster Tableau de pointeurs vers les clusters.
 * @param k Nombre total de clusters.
 * @param dimension Dimension des points dans les clusters.
 */
void write_cluster(FILE *file, cluster_t **cluster, int32_t k, uint32_t dimension); 

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
void write_csv(FILE *output_file, uint64_t* distortion, point_t **centroid_init_Array, point_t **centroid_final_Array, cluster_t ***clustersArray, int32_t k, uint32_t dimension, int64_t nombre_comb, bool quiet_mode ); 
#endif //WRITE_CSV_H
