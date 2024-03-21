#include <stdio.h>
#include <inttypes.h> // Ajout de l'en-tête inttypes.h

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/write_csv.h"

int8_t create_CSV(point_t* inits, cluster_t *clusters, uint64_t distortion, uint32_t *clusterParPoint, uint32_t k) {
    FILE *fp = fopen("output.csv", "w"); // Ouvrir le fichier CSV en écriture

    if (fp == NULL) {
        perror("Erreur lors de l'ouverture du fichier CSV");
        return -1;
    }

    // Écrire les noms des colonnes
    fprintf(fp, "initialization centroids, distortion, centroids, clusters\n");

    // Écrire les données pour chaque cluster
    for (uint32_t i = 0; i < k; i++) {
        // Écrire les centroïdes initiaux
        fprintf(fp, "\"");
        fprintArrayPoints(fp, inits, k);
        fprintf(fp, "\", %" PRIu64 ", \"", distortion);

        // Écrire les centroïdes finaux
        fprintArrayPoints(fp, &(clusters[i].center), 1);
        fprintf(fp, "\", \"");

        // Écrire les points associés à chaque cluster
        fprintArrayClusters(fp, &(clusters[i]));
        fprintf(fp, "\"");

        // Si ce n'est pas le dernier cluster, ajouter une virgule pour séparer les lignes
        if (i < k - 1) {
            fprintf(fp, ", ");
        } else { // Sinon, passer à la ligne suivante
            fprintf(fp, "\n");
        }
    }

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


void fprintArrayPoints(FILE *fp, point_t* arrayPts, uint64_t nb) {
    fprintf(fp, "[");
    fprintCoordPoint(fp, arrayPts[0]);
    for (uint64_t i = 1; i < nb; i++) {
        fprintf(fp, ", ");
        fprintCoordPoint(fp, arrayPts[i]);
    }
    fprintf(fp, "]");
}
