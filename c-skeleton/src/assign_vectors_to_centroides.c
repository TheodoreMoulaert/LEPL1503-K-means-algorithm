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
    //uint32_t final_cl=0;
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
            for (uint32_t p = 0; p < idx; ++p) {
                printf("%d\n",44);
                temp[p] = new_clusters[closest_centroid_idx]->data[p];
                //memcpy(temp[i],new_clusters[closest_centroid_idx]->data[i],sizeof(point_t)) ;
                printf("%d\n",444);
                //free(new_clusters[closest_centroid_idx]->data[i]);
               // printf("temp[idx]->coords[0] = %ld\n",temp[idx]->coords[0]);
            }
            //memcpy(temp,new_clusters[closest_centroid_idx]->data,idx*sizeof(point_t*)) ;//temp = new_clusters[closest_centroid_idx]->data;
            printf("%d\n",5);
            //temp[idx]=NULL;
            
            //printf("temp[idx]->coords[0] = %ld\n",temp[idx]->coords[0]);
            /*if (closest_centroid_idx!=0 && current_centroid_idx!=0){
                free(temp[idx]);
            }*/
            //if ( (i !=0) && (K-1!=   ){ //K-1 != current_centroid_idx &&
            /*if ((current_centroid_idx != K-1) && (i != clusters[current_centroid_idx]->size-1)){
                printf("%d\n",55);
                for (uint32_t t = 0; t < idx; ++t) {
            
                // Libérer l'ancienne zone mémoire
                    free(new_clusters[closest_centroid_idx]->data[t]);
                    printf("%d\n",555);
                }
            }*/
            //free(new_clusters[closest_centroid_idx]->data);
            
            printf("%d\n",6);
            //free(new_clusters[closest_centroid_idx]->centroide.coords);
            
            /*if ((current_centroid_idx != K-1) && (i != clusters[current_centroid_idx]->size-1)){//&& (i!= idx-1)
                //free(temp);
                  
            }*/
            //new_clusters[closest_centroid_idx]->data = NULL;
            printf("%d\n",7);

            // Affecter temp à la nouvelle zone mémoire
            new_clusters[closest_centroid_idx]->data = temp;
            
            //printf("new_clusters[closest_centroid_idx]->data[idx]->coords[0] = %ld\n",new_clusters[closest_centroid_idx]->data[idx]->coords[0]);
            printf("%d\n",8);
            //free(temp);
            new_clusters[closest_centroid_idx]->data[idx] = vector;
            //free(vector);
            new_clusters[closest_centroid_idx]->size++;
            new_clusters[closest_centroid_idx]->centroide = centroids[closest_centroid_idx];
            new_clusters[closest_centroid_idx]->centroide.dim = centroids[closest_centroid_idx].dim;
            //new_clusters[closest_centroid_idx]->centroide.nbr_vector = centroids[closest_centroid_idx].nbr_vector;
            if(current_centroid_idx == closest_centroid_idx){
                nconv += 1; 
               
            }
            printf("%d\n",9);
            if(nconv == npoint){
                 result.changes = true; 
            }
            /*for(uint32_t i = 0; i < idx+1; ++i){
                free(temp[i]);
            }
            free(temp);*/
            //free(temp[idx]);
            /*if (i== clusters[current_centroid_idx]->size-1){
                //free(temp);
                //temp = NULL;
                //free(temp);
            }*/
            /*for (uint32_t f = 0; f< idx; ++f) {
                free(temp[f]);
            }*/
            
            printf("%d\n",10);
        }
        //free(new_clusters[current_centroid_idx-1]);
        

    }
    printf("%d\n",12);
    result.result_cluster = new_clusters;
    return result;
}


