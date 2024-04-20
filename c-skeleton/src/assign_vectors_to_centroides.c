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
        // Gérer l'erreur de pointeur nul
        return result; 
    }

    // Allouer un nouveau tableau de clusters pour contenir les nouveaux clusters
    printf("%d\n", 1);
    cluster_t **new_clusters = (cluster_t**) malloc(K*sizeof(cluster_t*));//K * 
    if (new_clusters == NULL) {
        // Gérer l'erreur d'allocation de mémoire
        return result;
    }
    printf("%d\n", 2);
    uint64_t npoint = 0; 
    for(uint64_t i = 0; i < K; ++i) {
        npoint += clusters[i]->size; 
    }

    // Initialiser chaque nouveau cluster
    printf("%d\n", 3);
    for (uint32_t i = 0; i < K; ++i) {
        new_clusters[i] = (cluster_t*) malloc(sizeof(cluster_t));
        printf("%d\n", 4);
        new_clusters[i]->data = (point_t**)malloc(sizeof(point_t*)); 
        new_clusters[i]->data[0]= (point_t*)malloc(sizeof(point_t));
        printf("%d\n", 5);
        if (new_clusters[i] == NULL) {
    
            for (uint32_t j = 0; j < i; ++j) {
                free(new_clusters[j]->data);
                free(new_clusters[j]);
            }
            free(new_clusters);
            return result;
        }
        printf("%d\n", 6);

        // Initialise le cluster avec des valeurs par défaut
        new_clusters[i]->size = 0;
        new_clusters[i]->data[0]= NULL; 
        new_clusters[i]->data = NULL; // Initialise à NULL, car il n'y a pas encore de données
        new_clusters[i]->centroide.dim = 0; // Initialise la dimension à zéro
        new_clusters[i]->centroide.coords = NULL; // Initialise à NULL, car il n'y a pas encore de coordonnées
        printf("%d\n", 7);
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
            printf("%d\n", 11);
            
  
            uint32_t idx = new_clusters[closest_centroid_idx]->size;
            printf("%d\n", 12);
            
            
            point_t **temp = malloc((idx + 1) * sizeof(point_t *));
            printf("%d\n", 13);
            if (temp == NULL) {
          
                for (uint32_t j = 0; j < K; ++j) {
                    free(new_clusters[j]->data);
                    free(new_clusters[j]);
                }
                free(new_clusters);
                return result;
            }
            printf("%d\n", 14);
            if(idx != 0){
                for (uint32_t i = 0; i < idx; ++i) {
                    temp[i] = new_clusters[closest_centroid_idx]->data[i];
                }
                for (uint32_t m = 0; m < idx; m++){
                    free(new_clusters[closest_centroid_idx]->data[m]);
                    free(new_clusters[closest_centroid_idx]->data[m]);
                
                }

            }
            printf("%d\n", 15);
     
            temp[idx] = vector; 

            for (uint32_t m =0 ; m< idx+1; m++){
                new_clusters[closest_centroid_idx]->data = (point_t**)malloc(sizeof(point_t*));
                new_clusters[closest_centroid_idx]->data[m]= (point_t*)malloc(sizeof(point_t)); 
                new_clusters[closest_centroid_idx]->data[m]= temp[m]; 
            }
            printf("%d\n", 16);
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
         
            if (i== clusters[current_centroid_idx]->size-1){
                for(uint32_t i = 0; i < idx; ++i){
                    free(temp[i]);
                }
                free(temp);
            }
            printf("%d\n", 17);
            
            
             
        }

        
        
    }
    

    result.result_cluster = new_clusters;

    return result;
}
