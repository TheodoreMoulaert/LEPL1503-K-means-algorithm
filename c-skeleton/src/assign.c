#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"
#include "../headers/cluster.h"

// Définition de la fonction assign_vectors_to_centroides
/**
 * @brief Assignation des vecteurs aux centroids les plus proches
 * 
 * @param centroids Tableau des centroids
 * @param clusters Tableau de pointeurs vers les clusters
 * @param K Nombre de clusters
 * @param distance_func Fonction de calcul de distance
 * @return Résultat de l'assignation
 */


result_t assign_vectors_to_centroides(point_t *centroids, cluster_t **clusters, uint32_t K, squared_distance_func_t distance_func) {
    result_t result;
    result.changes = false;
    result.result_cluster = NULL;
    printf("assign de Clem%d\n",1);
    if (centroids == NULL || clusters == NULL) {
        // Handle null pointer error
        printf("%d",777);
        return result; 
    }
    printf("%d",0);
    cluster_t **new_clusters = (cluster_t**) malloc(K * sizeof(cluster_t*));
    if (new_clusters == NULL) {
        // Handle memory allocation error
        return result;
    }
    printf("%d",0);
    // Initialize each new cluster
    for (uint32_t i = 0; i < K; ++i) {
        new_clusters[i] = (cluster_t*) malloc(sizeof(cluster_t));
        if (new_clusters[i] == NULL) {
            // Handle memory allocation error
            // Free previously allocated memory
            for (uint32_t j = 0; j < i; ++j) {
                free(new_clusters[j]);
            }
            free(new_clusters);
            return result;
        }
        new_clusters[i]->size = 0;
        new_clusters[i]->data = NULL; // Initialize data to NULL
        new_clusters[i]->centroide.dim = 0;
        new_clusters[i]->centroide.coords = NULL;
    }
    printf("%d",0);

    uint64_t npoint = 0; 
    for(uint64_t i = 0; i < K; ++i) {
        npoint += clusters[i]->size; 
    }
    uint64_t nconv = 0; 

    for (uint32_t current_centroid_idx = 0; current_centroid_idx < K; ++current_centroid_idx){
        for (uint64_t i = 0; i < clusters[current_centroid_idx]->size; ++i){
            point_t *vector = clusters[current_centroid_idx]->data[i]; // ne pas libérer la mémoire
            printf("%d",0);
            uint32_t closest_centroid_idx = 0;
            uint64_t closest_centroid_distance = UINT64_MAX;
            for (uint32_t centroid_idx = 0; centroid_idx < K; ++centroid_idx) {
                uint64_t distance = distance_func(vector, &centroids[centroid_idx]);
                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }
            printf("%d",1);
            uint32_t idx = new_clusters[closest_centroid_idx]->size;
            //point_t **temp = (point_t**) realloc(new_clusters[closest_centroid_idx]->data, (idx + 1) * sizeof(point_t *));
            point_t **temp = (point_t**) malloc((idx + 1) * sizeof(point_t *));
            if (temp == NULL) {
                // Handle memory allocation error
                // Free previously allocated memory
                for (uint32_t j = 0; j < K; ++j) {
                    free(new_clusters[j]->data); // Freeing data if reallocation fails
                    free(new_clusters[j]);
                }
                free(new_clusters);
                return result;
            }
            printf("%d",2);
            for (uint32_t t =0; t <(idx + 1);t++){
                temp[t]->coords = (int64_t*)malloc(new_clusters[closest_centroid_idx]->data[t]->dim*sizeof(int64_t));
                temp[t]->dim=0;
                temp[t]->nbr_vector=0;
            }
            printf("%d",3);
            for (uint32_t t =0; t <(idx + 1);t++){
                temp[t]->coords = new_clusters[closest_centroid_idx]->data[t]->coords;
                temp[t]->dim=new_clusters[closest_centroid_idx]->data[t]->dim;
                temp[t]->nbr_vector=new_clusters[closest_centroid_idx]->data[t]->nbr_vector;
            }
            printf("%d",4);
            for (uint32_t r =0; r <(idx + 1);r++){
                new_clusters[closest_centroid_idx]->data[r]->coords = (int64_t*)malloc(temp[r]->dim*sizeof(int64_t));
                new_clusters[closest_centroid_idx]->data[r]->dim=temp[r]->dim;
                new_clusters[closest_centroid_idx]->data[r]->nbr_vector=temp[r]->nbr_vector;
            }
            printf("%d",5);
            for (uint32_t r =0; r <idx;r++){
                new_clusters[closest_centroid_idx]->data[r]->coords = temp[r]->coords;
                //new_clusters[closest_centroid_idx]->data[r]->dim=temp[r]->dim;
                //new_clusters[closest_centroid_idx]->data[r]->nbr_vector=temp[r]->nbr_vector;
            }
            
            new_clusters[closest_centroid_idx]->data[idx]->coords= vector->coords;
            new_clusters[closest_centroid_idx]->data[idx]->dim= vector->dim;
            new_clusters[closest_centroid_idx]->data[idx]->nbr_vector= vector->nbr_vector;
            printf("%d",6);

            //new_clusters[closest_centroid_idx]->data = temp;
            //new_clusters[closest_centroid_idx]->data[idx] = vector;
            new_clusters[closest_centroid_idx]->size++;
            new_clusters[closest_centroid_idx]->centroide = centroids[closest_centroid_idx];
            new_clusters[closest_centroid_idx]->centroide.dim = centroids[closest_centroid_idx].dim;

            if(current_centroid_idx == closest_centroid_idx){
                nconv += 1; 
            }
            if(nconv == npoint){
                 result.changes = true; 
            }
            for (uint32_t t =0; t <(idx + 1);t++){
                free(temp[t]->coords);
                free(temp[t]);
            }
            free(temp);
        }      
    }

    result.result_cluster = new_clusters;
    return result;
}