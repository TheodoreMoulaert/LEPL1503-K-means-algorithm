#include <stdio.h>

#include "../headers/point.h"
#include "../headers/cluster.h"

// vraiment pas sur écrit très rapidement avec aide de chatgpt

int8_t create_CSV(point_t* inits, cluster_t *clusters, uint64_t distortion, uint32_t *clusterParPoint) {
    FILE *fp = fopen("output.csv", "w"); // Ouvrir le fichier CSV en écriture

    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return -1;
    }

    // Écrire les centroïdes initiaux et la distortion
    fprintf(fp, "Centroïdes initiaux,");
    fprintArrayPoints(fp, inits, k);
    fprintf(fp, ",%" PRIu64 "\n", distortion);

    // Écrire les centroïdes finaux et les points associés à chaque cluster
    for (uint32_t i = 0; i < k; i++) {
        fprintf(fp, "Cluster %d,", i+1);
        fprintCoordPoint(fp, clusters[i].center);
        fprintf(fp, ",\"");
        fprintArrayPoints(fp, clusters[i].data, clusters[i].size);
        fprintf(fp, "\"\n");
    }

    fclose(fp); 
    return 0;
}


void fprintCoordPoint(FILE *fp, point_t pt) {
    fprintf(fp, "(%" PRId64 "", pt.coords[0]);
    for (uint32_t j = 1; j < pt.dim; j++) {
        fprintf(fp, ", %" PRId64 "", pt.coords[j]);
    }
    fprintf(fp, ")");
}


void fprintArrayPoints(FILE *fp, point_t* arrayPts, uint64_t nb) {
    fprintCoordPoint(fp, arrayPts[0]);
    for (uint64_t i = 1; i < nb; i++) {
        fprintf(fp, ", ");
        fprintCoordPoint(fp, arrayPts[i]);
    }
}
