#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"
#include "../headers/cluster.h"

/**
 * Affecte les vecteurs aux centroids les plus proches dans les clusters correspondants.
 * 
 * @param centroids Tableau des centroids
 * @param clusters Tableau de pointeurs vers les clusters
 * @param K Nombre de centroids
 * @param distance_func Fonction de calcul de distance entre les points
 * @return Résultat de l'affectation des vecteurs aux centroids les plus proches
 */
result_t assign_vectors_to_centroids(point_t *centroids, cluster_t **clusters, uint32_t K, squared_distance_func_t distance_func) {
    result_t result;
    result.changes = false;
    result.result_cluster = NULL;

    if (centroids == NULL || clusters == NULL) {
        // Gérer l'erreur de pointeur nul
        return result; 
    }

    cluster_t **new_clusters = (cluster_t**) malloc(K * sizeof(cluster_t*));
    if (new_clusters == NULL) {
        // Gérer l'erreur d'allocation de mémoire
        return result;
    }

    // Initialiser chaque nouveau cluster
    for (uint32_t i = 0; i < K; ++i) {
        new_clusters[i] = (cluster_t*) malloc(sizeof(cluster_t));
        if (new_clusters[i] == NULL) {
            // Gérer l'erreur d'allocation de mémoire
            // Libérer la mémoire précédemment allouée
            for (uint32_t j = 0; j < i; ++j) {
                free(new_clusters[j]);
            }
            free(new_clusters);
            return result;
        }
        new_clusters[i]->size = 0;
        new_clusters[i]->data = NULL; // Initialiser data à NULL
        new_clusters[i]->centroide.dim = 0;
        new_clusters[i]->centroide.coords = NULL;
    }

    uint64_t npoint = 0; 
    for(uint64_t i = 0; i < K; ++i) {
        npoint += clusters[i]->size; 
    }
    uint64_t nconv = 0; 

    for (uint32_t current_centroid_idx = 0; current_centroid_idx < K; ++current_centroid_idx){
        for (uint64_t i = 0; i < clusters[current_centroid_idx]->size; ++i){
            point_t *vector = clusters[current_centroid_idx]->data[i];

            uint32_t closest_centroid_idx = 0;
            uint64_t closest_centroid_distance = UINT64_MAX;
            for (uint32_t centroid_idx = 0; centroid_idx < K; ++centroid_idx) {
                uint64_t distance = distance_func(vector, &centroids[centroid_idx]);
                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }
            
            uint32_t idx = new_clusters[closest_centroid_idx]->size;
            point_t **temp = (point_t**) realloc(new_clusters[closest_centroid_idx]->data, (idx + 1) * sizeof(point_t *));
            if (temp == NULL) {
                // Gérer l'erreur d'allocation de mémoire
                // Libérer la mémoire précédemment allouée
                for (uint32_t j = 0; j < K; ++j) {
                    free(new_clusters[j]->data); // Libérer data si la réallocation échoue
                    free(new_clusters[j]);
                }
                free(new_clusters);
                return result;
            }

            new_clusters[closest_centroid_idx]->data = temp;
            new_clusters[closest_centroid_idx]->data[idx] = vector;
            new_clusters[closest_centroid_idx]->size++;
            new_clusters[closest_centroid_idx]->centroide = centroids[closest_centroid_idx];
            new_clusters[closest_centroid_idx]->centroide.dim = centroids[closest_centroid_idx].dim;

            if(current_centroid_idx == closest_centroid_idx){
                nconv += 1; 
            }
            if(nconv == npoint){
                 result.changes = true; 
            }
        }  
    }
    result.result_cluster = new_clusters;
    return result;
}


