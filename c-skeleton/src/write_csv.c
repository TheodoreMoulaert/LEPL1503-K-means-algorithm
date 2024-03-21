#include <stdio.h>
#include <inttypes.h> // Ajout de l'en-tête inttypes.h

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"

int8_t create_CSV(cluster_t *clusters, uint64_t distortion, uint32_t *clusterParPoint, uint32_t k) {
    FILE *fp = fopen("output.csv", "w"); // Ouvrir le fichier CSV en écriture

    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return -1;
    }

    // Écrire les noms des colonnes
    fprintf(fp, "initialization centroids, distortion, centroids, clusters\n");

    // Écrire les données pour tous les clusters
    fprintf(fp, "\"[");
    for (uint32_t i = 0; i < k; i++) {
        // Écrire les centroïdes finaux
        fprintCoordPoint(fp, clusters[i].center);
        if (i < k - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\", %" PRIu64 ", \"[", distortion);

    // Écrire les clusters
    for (uint32_t i = 0; i < k; i++) {
        fprintArrayClusters(fp, &(clusters[i]));
        if (i < k - 1) {
            fprintf(fp, ",");
        }
    }
    fprintf(fp, "]\"\n");

    fclose(fp);
    return 0;
}

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
