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

result_t assign_vectors_to_centroides(point_t *centroids, cluster_t **clusters, int32_t K, squared_distance_func_t distance_func) {
    result_t result;
    result.changes = false;
    result.result_cluster = NULL;

    if (centroids == NULL || clusters == NULL) {
        // Gérer l'erreur de pointeur nul
        return result; 
    }

    // Allouer un nouveau tableau de clusters pour contenir les nouveaux clusters
    cluster_t **new_clusters = (cluster_t**) malloc(K*sizeof(cluster_t*));
    if (new_clusters == NULL) {
        // Gérer l'erreur d'allocation de mémoire
        return result;
    }

    // Initialiser chaque nouveau cluster
    for (int32_t i = 0; i < K; ++i) {
        new_clusters[i] = (cluster_t*) malloc(sizeof(cluster_t));
        // Gérer l'erreur d'allocation de mémoire
        if (new_clusters[i] == NULL) {
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
        new_clusters[i]->centroide.nbr_vector = 0;
    }
    
    // Parcourir tous les centroides
    uint64_t npoint = 0; 
    for(int32_t i = 0; i < K; ++i) {
        npoint += clusters[i]->size; 
    }

    uint64_t nconv = 0; 
    
    for (int32_t current_centroid_idx = 0; current_centroid_idx < K; ++current_centroid_idx){
        for (uint64_t i = 0; i < clusters[current_centroid_idx]->size; ++i){
            point_t *vector = clusters[current_centroid_idx]->data[i];

            // Trouver le centroïde le plus proche pour le vecteur
            uint32_t closest_centroid_idx = 0;
            uint64_t closest_centroid_distance = UINT64_MAX;
            for (int32_t centroid_idx = 0; centroid_idx < K; ++centroid_idx) {
                uint64_t distance = distance_func(vector, &centroids[centroid_idx]);
        
                if (distance < closest_centroid_distance) {
                    closest_centroid_idx = centroid_idx;
                    closest_centroid_distance = distance;
                }
            }

            // Ajouter le vecteur au cluster le plus proche dans le nouveau tableau de clusters
            uint32_t idx = new_clusters[closest_centroid_idx]->size;
        
            // Allouer une nouvelle zone mémoire pour temp avec la taille souhaitée
            point_t **temp = malloc((idx+1) * sizeof(point_t *)); 

            // Copier les éléments existants de l'ancienne zone mémoire vers la nouvelle
            for (uint32_t i = 0; i < idx; ++i) {
                temp[i] = new_clusters[closest_centroid_idx]->data[i];
            }
            free(new_clusters[closest_centroid_idx]->data);
            
            new_clusters[closest_centroid_idx]->data = temp;
            new_clusters[closest_centroid_idx]->data[idx] = vector;
            new_clusters[closest_centroid_idx]->size++;
            new_clusters[closest_centroid_idx]->centroide.coords = centroids[closest_centroid_idx].coords;
            new_clusters[closest_centroid_idx]->centroide.dim = centroids[closest_centroid_idx].dim;
            new_clusters[closest_centroid_idx]->centroide.nbr_vector = centroids[closest_centroid_idx].nbr_vector;
            
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

