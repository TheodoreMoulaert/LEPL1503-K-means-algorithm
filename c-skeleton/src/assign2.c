#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
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

    if (centroids == NULL || clusters == NULL) {
      
        return result; 
    }

    cluster_t **new_clusters = (cluster_t**) malloc(K*sizeof(cluster_t*));

    if (new_clusters == NULL) {
        return result;
    }

    uint64_t npoint = 0; 
    for(uint64_t i = 0; i < K; ++i) {
        npoint += clusters[i]->size; 
    }
    for(uint32_t i = 0; i < K; i++){ // On parcourt le nombre de clusters
        new_clusters[i] = (cluster_t*)malloc(sizeof(cluster_t)); 
        if(new_clusters[i] == NULL){
            free(new_clusters[i]); 
            return result; 
        }
        new_clusters[i]->data = (point_t**) malloc(sizeof(point_t*)); 
        if(new_clusters[i]->data == NULL){
            free(new_clusters[i]->data);
            free(new_clusters[i]); 
            free(new_clusters);
            return result; 
        }
        new_clusters[i]->data[0] = (point_t*)malloc(sizeof(point_t)); 
        if(new_clusters[i]->data[0] == NULL){
            free(new_clusters[i]->data[0]); 
            free(new_clusters[i]->data);
            free(new_clusters[i]); 
            
            return result; 
        }
        new_clusters[i]->centroide.coords = (int64_t*)malloc(clusters[0]->centroide.dim *sizeof(int64_t));
        // Initialise le cluster avec des valeurs par défaut
        new_clusters[i]->size = 0;
        //new_clusters[i]->data[0]= NULL; 
        //new_clusters[i]->data = NULL; // Initialise à NULL, car il n'y a pas encore de données
        new_clusters[i]->centroide.dim = 0; // Initialise la dimension à zéro
        //new_clusters[i]->centroide.coords = NULL; // Initialise à NULL, car il n'y a pas encore de coordonnées
        
    }
    uint64_t nconv = 0; 
    printf("%d\n", 8);
    for (uint32_t current_centroid_idx = 0; current_centroid_idx < K; ++current_centroid_idx){ //K nbr_comb
     
        for (uint64_t i = 0; i < clusters[current_centroid_idx]->size; ++i){
            point_t *vector = clusters[current_centroid_idx]->data[i];
            printf("%d\n", 9);
  
            uint32_t closest_centroid_idx = 0;
            uint64_t closest_centroid_distance = UINT64_MAX;
            for (uint32_t centroid_idx = 0; centroid_idx < K; ++centroid_idx) {
                uint64_t distance = distance_func(vector, &centroids[centroid_idx]);//&
                printf("%d\n", 10);
          
                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }

            }
            printf("%d\n", 1);
            uint32_t current_idx = new_clusters[closest_centroid_idx]->size;
            point_t **temp = (point_t**) ((current_idx + 1) * sizeof(point_t *));
            if (temp == NULL) {
                free(temp); 
          
                for (uint32_t j = 0; j < K; ++j) {
                    for(uint32_t h =0; h< current_idx; h++){
                        free(new_clusters[j]->data[h]);
                    }
                    free(new_clusters[j]->data);
                    free(new_clusters[j]);
                }
                free(new_clusters);
                return result;
            }
            printf("%d\n", 2);
            for (uint32_t i = 0; i < current_idx; ++i) {
                temp[i] = (point_t*)malloc(sizeof(point_t)); 
                if(temp[i]==NULL){
                    free(temp[i]); 
                    free(temp); 
                    for (uint32_t j = 0; j < K; ++j) {
                        for(uint32_t h =0; h< current_idx; h++){
                            free(new_clusters[j]->data[h]);
                        }
                        free(new_clusters[j]->data);
                        free(new_clusters[j]);
                    }
                    free(new_clusters);
                    return result;
                    
                }
                printf("%d\n", 3);
                temp[i] = new_clusters[closest_centroid_idx]->data[i];
            }
            free(new_clusters[closest_centroid_idx]->data);        
            for (uint32_t m = 0; m < current_idx; m++){
                free(new_clusters[closest_centroid_idx]->data[m]);
                
            }
            printf("%d\n", 4);
            temp[current_idx] = (point_t*)malloc(sizeof(point_t)); 
            temp[current_idx] = vector; 
            new_clusters[closest_centroid_idx]->data = (point_t**)malloc((current_idx+1)*sizeof(point_t*)); 
            for (uint32_t m =0 ; m< current_idx+1; m++){
                new_clusters[closest_centroid_idx]->data[m]= (point_t*)malloc(sizeof(point_t)); 
                new_clusters[closest_centroid_idx]->data[m]= temp[m]; 
            }
            printf("%d\n", 5);
            new_clusters[closest_centroid_idx]->data = temp;
            new_clusters[closest_centroid_idx]->size++;
            new_clusters[closest_centroid_idx]->centroide = centroids[closest_centroid_idx];
            new_clusters[closest_centroid_idx]->centroide.dim = centroids[closest_centroid_idx].dim;
            if(current_centroid_idx == closest_centroid_idx){
                nconv += 1; 
               
            }
            if(nconv == npoint){
                 result.changes = true; 
            }
            
            for(uint32_t i = 0; i < current_idx+1; ++i){
                free(temp[i]);
            }
            free(temp); 
        }
    }
    result.result_cluster = new_clusters;
    for (uint32_t j = 0; j < K; ++j) {
        for(uint32_t h =0; h< new_clusters[j]->size; h++){
            free(new_clusters[j]->data[h]); 
        }
                 
        free(new_clusters[j]->data);
        free(new_clusters[j]);
                
                
    }           
    free(new_clusters);
    return result;

}