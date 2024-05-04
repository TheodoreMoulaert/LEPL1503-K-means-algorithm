#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"

/**
 * @brief Applique l'algorithme de K-means pour regrouper les points en k clusters.
 * 
 * @param clusters Tableau de pointeurs vers les clusters initiaux
 * @param num_points Nombre total de points à regrouper
 * @param k Nombre de clusters à former
 * @param initial_centroids Tableau des centroids initiaux
 * @param final_centroids Tableau des centroids finaux mis à jour par l'algorithme
 * @param distance_func Fonction de calcul de distance entre les points
 * @return Tableau de pointeurs vers les clusters finaux, ou NULL en cas d'erreur
 */
cluster_t** k_means(cluster_t** clusters, uint64_t num_points, uint32_t k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func) {
    if (clusters == NULL || initial_centroids == NULL || final_centroids == NULL) {
        fprintf(stderr, "Paramètres invalides pour la fonction k_means.\n");
        return NULL;
    }
    // Initialise les centroids finaux avec les centroids initiaux
    for (uint32_t i = 0; i < k; i++) {
        clusters[i]->centroide = initial_centroids[i];
    }

    result_t result;
    result.result_cluster = NULL;
    result.changes= false;

    // Exécute des itérations jusqu'à convergence
    bool convergence = false;
    uint64_t i = 0; 
    while (convergence == false) {
        // Assigne les points aux clusters
        if (i == 0) {
            result = assign_vectors_to_centroides(final_centroids, clusters, k, distance_func);
        } else {
            result = assign_vectors_to_centroides(final_centroids, result.result_cluster, k,distance_func);
        }
        
        if (result.result_cluster == NULL) {
            fprintf(stderr, "L'allocation de mémoire a échoué pour result.result_cluster.\n");
            free(final_centroids);
            return NULL;
        }

        if (clusters == NULL) {
            fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 4.\n");
            free(final_centroids);
            return NULL;
        }
        convergence = result.changes; 
    
        update_centroids(result.result_cluster, k);
        clusters = result.result_cluster;

        // Mise à jour des centroids finaux avec les nouveaux centroids des clusters
        for (uint32_t j = 0; j < k; j++) {
            if (clusters[j]->size >=1){
                final_centroids[j] = clusters[j]->centroide;
            }
        }
        i++;  
    }
    return result.result_cluster;
}