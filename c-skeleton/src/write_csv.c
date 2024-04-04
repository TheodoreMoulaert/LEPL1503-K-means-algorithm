#include <stdio.h>
#include <inttypes.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"
#include "../headers/update_centroids.h" 


void write_csv(FILE *output_file, int64_t distortion, point_t **centroid_init_Array,point_t **centroid_final_Array ,cluster_t ***clustersArray, int64_t k, int64_t dimension) {

    FILE *fp = fopen("output.csv", "w"); 
    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return -1;
    }

    fprintf(fp, "initialization centroids, distortion, centroids, clusters\n");
    
}
/*int8_t create_CSV(cluster_t *clusters, cluster_t centroid_init, uint64_t distortion, uint32_t *clusterParPoint, uint32_t k) {
    FILE *fp = fopen("output.csv", "w"); 

    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return -1;
    }

    fprintf(fp, "initialization centroids, distortion, centroids, clusters\n");

    // Écrire les données pour chaque cluster
    fprintf(fp, "\"[");
    for (uint32_t i = 0; i < k; i++) {
        // Écrire les centroides initiaux
        fprintf(fp, "[");
        fprintCoordPoint(fp, centroid_init.data[i]);
        fprintf(fp, "]");
        if (i < k - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\", \"%" PRIu64 "\", \"[", distortion);

    for (uint32_t i = 0; i < k; i++) {
      
        fprintf(fp, "[");
        fprintCoordPoint(fp, clusters[i].center);
        fprintf(fp, "]");
        if (i < k - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\", \"[");

    
    for (uint32_t i = 0; i < k; i++) {
        fprintf(fp, "[");
        for (uint32_t j = 0; j < clusters[i].size; j++) {
            fprintCoordPoint(fp, clusters[i].data[j]);
            if (j < clusters[i].size - 1) {
                fprintf(fp, ",");
            }
        }
        fprintf(fp, "]");
        if (i < k - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\"\n");

    fclose(fp);
    return 0;
}


// aide de chatgpt pour ces fonctions
void fprintArrayClusters(FILE *fp, cluster_t *cluster) {
    fprintf(fp, "[");
    for (uint32_t i = 0; i < cluster->size; i++) {
        fprintCoordPoint(fp, cluster->data[i]);
        if (i < cluster->size - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]");
}

void fprintCoordPoint(FILE *fp, point_t pt) {
    fprintf(fp, "(%" PRId64 "", pt.coords[0]);
    for (uint32_t j = 1; j < pt.dim; j++) {
        fprintf(fp, ", %" PRId64 "", pt.coords[j]);
    }
    fprintf(fp, ")");
}

void fprintArrayPoints(FILE *fp, int64_t* arrayPts, uint64_t nb) {
    fprintf(fp, "[");
    fprintf(fp, "(%" PRId64 "", arrayPts[0]);
    for (uint64_t i = 1; i < nb; i++) {
        fprintf(fp, ", %" PRId64 "", arrayPts[i]);
    }
    fprintf(fp, ")");
}*/

