#include <stdio.h>
#include <inttypes.h>
#include <stdlib.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"
#include "../headers/update_centroids.h" 

void write_centroid(FILE *file, point_t* centroid, int64_t k) {
    if (file == NULL || centroid == NULL) {
        fprintf(file, "Erreur : pointeur de fichier ou de centroïde invalide.\n");
        return;
    }

    fprintf(file, "[");
    for (int i=0;i<k;i++){
        fprintf(file, "(");
        fprintf(file, "%" PRId64 ",%" PRId64 "", centroid[i].coords[0], centroid[i].coords[1]);
        fprintf(file, ")");
        if (i<k-1){
            fprintf(file, ",");
        }
        for (int64_t i = 2; i < centroid->dim; i++) {
            fprintf(file, ",(");
            fprintf(file, "%" PRId64 ",%" PRId64 "", centroid->coords[i], centroid->coords[i + 1]); // Modification ici
            fprintf(file, ")");
            i++; // Modification ici
        }

    }
    
    fprintf(file, "]");
}


void write_cluster(FILE *file, cluster_t **cluster, int64_t k) {
    if (file == NULL || cluster == NULL) {
        fprintf(file, "Erreur : pointeur de fichier ou de cluster invalide.\n");
        return;
    }
    
    
    fprintf(file, "[");
    for (int64_t i = 0;i<k;i++){ //cluster[i] != NULL; i++) {
        fprintf(file, "[");
        /*if (i > 0) {
            fprintf(file, ",");
        }*/

        for (int64_t j = 0; j < cluster[i]->size; j++) { //cluster[i]->size ou k ?
            if (j > 0) {
                fprintf(file, ",");
            }
            fprintf(file, "(");
            if (cluster[i]->data[j] == NULL || cluster[i]->data[j]->coords == NULL || cluster[i]->data[j]->dim <= 0) {
                fprintf(file, "Erreur : point invalide dans le cluster.\n");
                continue;
            }
            fprintf(file, "%" PRId64 ",%" PRId64 "", cluster[i][0].data[j]->coords[0], cluster[i][0].data[j]->coords[1]);
            fprintf(file, ")");
        }
        if (i<k-1){
            fprintf(file, "],");
        }
    
    }
    fprintf(file, "]");
}

void write_csv(FILE *output_file, uint64_t* distortion, point_t **centroid_init_Array, point_t **centroid_final_Array, cluster_t ***clustersArray, int64_t k, int64_t dimension, int64_t nombre_comb) {
    if (output_file == NULL) {
        printf("Erreur : pointeur de fichier de sortie invalide.\n");
        return;
    }

    fprintf(output_file, "initialization centroids, distortion, centroids, clusters\n");

    for (int64_t i = 0; i < nombre_comb; i++) {
        fprintf(output_file, "\"");
        write_centroid(output_file, centroid_init_Array[i], k);
        fprintf(output_file, "\",%" PRId64 ",\"", distortion[i]);
        write_centroid(output_file, centroid_final_Array[i], k);
        fprintf(output_file, "\",\"");
        write_cluster(output_file, clustersArray[i], k);
        fprintf(output_file, "\"\n");
    }
}
