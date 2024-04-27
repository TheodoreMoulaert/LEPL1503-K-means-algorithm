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

    if (centroids == NULL || clusters == NULL) {
        // Gérer l'erreur de pointeur nul
        return result; 
    }

    // Allouer un nouveau tableau de clusters pour contenir les nouveaux clusters
    cluster_t **new_clusters = (cluster_t**) malloc(K*sizeof(cluster_t*));//K * 
    if (new_clusters == NULL) {
        // Gérer l'erreur d'allocation de mémoire
        return result;
    }
    

    // Initialiser chaque nouveau cluster
    for (uint32_t i = 0; i < K; ++i) {
        new_clusters[i] = (cluster_t*) malloc(sizeof(cluster_t));
        if (new_clusters[i] == NULL) {
            // Gérer l'erreur d'allocation de mémoire
            // Libérer la mémoire allouée pour les nouveaux clusters déjà initialisés
            for (uint32_t j = 0; j < i; ++j) {
                free(new_clusters[j]->data);
                free(new_clusters[j]);
            }
            free(new_clusters);
            return result;
        }
        // Initialise le cluster avec des valeurs par défaut
        new_clusters[i]->size = 0;
        new_clusters[i]->data = NULL; // Initialise à NULL, car il n'y a pas encore de données
        new_clusters[i]->centroide.dim = 0; // Initialise la dimension à zéro
        new_clusters[i]->centroide.coords = NULL; // Initialise à NULL, car il n'y a pas encore de coordonnées


        
    }
    // Parcourir tous les centroides
    uint64_t npoint = 0; 
    for(uint64_t i = 0; i < K; ++i) {
        npoint += clusters[i]->size; 
    }
    uint64_t nconv = 0; 
   
    for (uint32_t current_centroid_idx = 0; current_centroid_idx < K; ++current_centroid_idx){ //K nbr_comb
        printf("%d\n",0);
        // Parcourir tous les vecteurs du cluster actuel
        for (uint64_t i = 0; i < clusters[current_centroid_idx]->size; ++i){
            point_t *vector = clusters[current_centroid_idx]->data[i];
            printf("%d\n",1);
            // Trouver le centroïde le plus proche pour le vecteur
            uint32_t closest_centroid_idx = 0;
            uint64_t closest_centroid_distance = UINT64_MAX;
            for (uint32_t centroid_idx = 0; centroid_idx < K; ++centroid_idx) {
                printf("%d\n",2);
                uint64_t distance = distance_func(vector, &centroids[centroid_idx]);//&
                //printf("distance: %ld\n",distance);
                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }

            }
            printf("%d\n",3);
            
            // Ajouter le vecteur au cluster le plus proche dans le nouveau tableau de clusters
            uint32_t idx = new_clusters[closest_centroid_idx]->size;
            //uint32_t idx = result.result_cluster[closest_centroid_idx]->size;
        
            // Allouer une nouvelle zone mémoire pour temp avec la taille souhaitée
            point_t **temp = malloc((idx+1) * sizeof(point_t *)); //(idx + 1)
            
            printf("%d\n",4);
            if (temp == NULL){
                // Gérer l'erreur d'allocation de mémoire
                // Libérer la mémoire allouée pour les nouveaux clusters déjà initialisés
                for (uint32_t j = 0; j < K; ++j) {
                    free(new_clusters[j]->data);
                    free(new_clusters[j]);
                }
                free(new_clusters);
                return result;
            }
            printf(" idx = %d\n",idx);
            printf("closest_centroid_idx=%d\n",closest_centroid_idx);
            printf("current_centroid_idx=%d, K-1=%d\n",current_centroid_idx,K-1);
            printf("clusters[current_centroid_idx]->size-1=%ld, i= %ld\n",clusters[current_centroid_idx]->size-1,i);

            // Copier les éléments existants de l'ancienne zone mémoire vers la nouvelle
            /*for (uint32_t p = 0; p < idx; ++p) {
                printf("%d\n",44);
                temp[p] = new_clusters[closest_centroid_idx]->data[p];
                printf("%d\n",444);
       
            }*/
            printf("%d\n",5);
            uint32_t d = vector->dim;
            
            for (uint32_t t =0; t <(idx + 1);t++){
                printf("%d\n",555);
                temp[t] = (point_t*)malloc(sizeof(point_t));
                temp[t]->coords = (int64_t*)malloc(d*sizeof(int64_t));
                printf("%d\n",5555);
                temp[t]->dim=d;
                temp[t]->nbr_vector=0;
                
            }
            printf("%d\n",6);
            for (uint32_t t =0; t <(idx);t++){
                temp[t]->coords = new_clusters[closest_centroid_idx]->data[t]->coords;
                temp[t]->dim=d;//new_clusters[closest_centroid_idx]->data[t]->dim;
                temp[t]->nbr_vector=new_clusters[closest_centroid_idx]->data[t]->nbr_vector;
            }
            temp[idx]->coords = NULL;
            temp[idx]->dim=0;//new_clusters[closest_centroid_idx]->data[t]->dim;
            temp[idx]->nbr_vector=0;
            printf("%d\n",66);
            /*for (uint32_t r =0; r <(idx+1);r++){
                new_clusters[closest_centroid_idx]->data[r]->coords = (int64_t*)malloc(d*sizeof(int64_t));
                
                //new_clusters[closest_centroid_idx]->data[r]->dim=d;
                //new_clusters[closest_centroid_idx]->data[r]->nbr_vector=temp[r]->nbr_vector;
            }*/
            printf("%d\n",666);
            /*for (uint32_t r =0; r <idx;r++){
                new_clusters[closest_centroid_idx]->data[r]->coords = temp[r]->coords;
                new_clusters[closest_centroid_idx]->data[r]->dim=temp[r]->dim;
                new_clusters[closest_centroid_idx]->data[r]->nbr_vector=temp[r]->nbr_vector;
            }
            printf("%d\n",6666);
            if(idx !=0){

            }
            new_clusters[closest_centroid_idx]->data[idx]->coords= vector->coords;
            printf("%d\n",61);
            new_clusters[closest_centroid_idx]->data[idx]->dim= vector->dim;
            printf("%d\n",62);
            new_clusters[closest_centroid_idx]->data[idx]->nbr_vector= vector->nbr_vector;
            */
            new_clusters[closest_centroid_idx]->data = temp;
            new_clusters[closest_centroid_idx]->data[idx] = vector;
            new_clusters[closest_centroid_idx]->size++;
            new_clusters[closest_centroid_idx]->centroide = centroids[closest_centroid_idx];
            new_clusters[closest_centroid_idx]->centroide.dim = centroids[closest_centroid_idx].dim;
            
            

            if(current_centroid_idx == closest_centroid_idx){
                nconv += 1; 
               
            }
            printf("%d\n",7);
            if(nconv == npoint){
                 result.changes = true; 
            }
            for (uint32_t t =0; t <(idx + 1);t++){
                free(temp[t]->coords);
                free(temp[t]);
            }
            //free(temp);
            printf("%d\n",8);
        }      

    }
    printf("%d\n",12);
    result.result_cluster = new_clusters;
    
    return result;
}




/*#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/assign_vector_to_centro.h"
#include "../headers/distance.h"
#include "../headers/cluster.h"

// Définition de la fonction assign_vectors_to_centroides

 * @brief Assignation des vecteurs aux centroids les plus proches
 * 
 * @param centroids Tableau des centroids
 * @param clusters Tableau de pointeurs vers les clusters
 * @param K Nombre de clusters
 * @param distance_func Fonction de calcul de distance
 * @return Résultat de l'assignation
 


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
}*/