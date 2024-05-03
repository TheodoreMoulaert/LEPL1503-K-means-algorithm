#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>
#include <stddef.h>
#include <errno.h>
#include "../headers/kmeans_thread.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include "../headers/kmeans_thread_args.h"
#include "../headers/write_thread.h"

/**
 * Execute l'algorithme des k-moyennes dans un thread.
 * 
 * @param clusters Tableau de pointeurs vers les clusters initiaux
 * @param num_points Nombre total de points à regrouper
 * @param k Nombre de clusters à former
 * @param initial_centroids Tableau des centroids initiaux
 * @param final_centroids Tableau des centroids finaux mis à jour par l'algorithme
 * @param distance_func Fonction de calcul de distance entre les points
 * @return Résultat de l'algorithme des k-moyennes encapsulé dans une structure result_thread
 */
result_thread kmeans_thread2(cluster_t** clusters, uint64_t num_points, uint32_t k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func) {
   
    result_t result; 
    //result_thread res_thread;
    result_thread res_thread = {0}; 

    if (clusters == NULL) {
        fprintf(stderr, "Paramètres invalides cluster null pour la fonction k_means.\n");
        return res_thread;
    }
    if(initial_centroids == NULL){
        fprintf(stderr, "Paramètres centr pour la fonction k_means.\n");
        return res_thread;

    }
    if( final_centroids == NULL){
        fprintf(stderr, "Paramètres final pour la fonction k_means.\n");
        return res_thread;
    }
    // Initialise les centroids finaux avec les centroids initiaux
    for (int i = 0; i < k; i++) { 
        clusters[i]->centroide = initial_centroids[i];
    }

    point_t *old_centroids = (point_t *)malloc(k * sizeof(point_t));
    if (old_centroids == NULL) {
        fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 3.\n");
        return res_thread;
    }


    // Exécute des itérations jusqu'à convergence
    bool convergence = false;
    uint64_t i = 0; 
    while (convergence == false) {
        // Sauvegarde les anciens centroids
        for (int j = 0; j < k; j++) {
            old_centroids[j].dim = final_centroids[j].dim;
            old_centroids[j].coords = (int64_t *)calloc(final_centroids[j].dim ,sizeof(int64_t));
            if (old_centroids[j].coords == NULL) {
                fprintf(stderr, "L'allocation de mémoire a échoué pour old_centroids.\n");
                for (int l = 0; l < j; l++) {
                    free(old_centroids[l].coords);
                }
                free(old_centroids);
                return res_thread; 
            }
            for (int m = 0; m < final_centroids[j].dim; m++) {
                old_centroids[j].coords[m] = final_centroids[j].coords[m];
            }
        }
        
        // Assigne les points aux clusters
        if (i == 0) {
            result = assign_vectors_to_centroides(final_centroids, clusters, k, distance_func);
        } else {
            result = assign_vectors_to_centroides(final_centroids, result.result_cluster, k,distance_func);
        }

        if (result.result_cluster == NULL) {
            fprintf(stderr, "L'allocation de mémoire a échoué pour result.result_cluster.\n");
            free(old_centroids);
            return res_thread;
        }

        if (clusters == NULL) {
            fprintf(stderr, "L'allocation de mémoire a échoué (/src/kmeans.c) 4.\n");
            free(old_centroids);
            return res_thread;
        }
        
        convergence = result.changes; 
    
        update_centroids(result.result_cluster, k);
        clusters = result.result_cluster; 
        // Mise à jour des centroids finaux avec les nouveaux centroids des clusters
        for (int j = 0; j < k; j++) {
            final_centroids[j] = clusters[j]->centroide;
        }
             
        // Libérer la mémoire pour les old_centroids
        for (int j = 0; j < k; j++) {
            free(old_centroids[j].coords);
        }
        i++;  
    }
    
    res_thread.temps_result_cluster = result.result_cluster;
    res_thread.final_centroids= final_centroids;
    res_thread.initial_centroids = initial_centroids;
    res_thread.temp_distorsion = distortion((cluster_t const **)res_thread.temps_result_cluster, k, distance_func);
    // Libérer la mémoire pour les old_centroids
    free(old_centroids);
    return res_thread;
}



/**
 * Fonction de démarrage pour le thread k_means.
 * 
 * @param args Pointeur vers une structure contenant les arguments nécessaires pour exécuter l'algorithme des k-moyennes dans un thread
 */
void *k_means_thread(void *args) { 
    int err;
    k_means_thread_args_t *thread_args = (k_means_thread_args_t *) args;
    result_thread res_th;
    
    while(thread_args->position < thread_args->nombre_comb){
        err = pthread_mutex_lock(thread_args->mutex);
        if(err!=0){
            perror("pthread_mutex_lock");
        }
        uint32_t j = thread_args->position;
        thread_args->position++;
        
        err = pthread_mutex_unlock(thread_args->mutex);
        if(err!=0){
            perror("pthread_mutex_unlock");
        }
        
        if( j >= thread_args->nombre_comb){
            break;
        }
        else{
            
            res_th = kmeans_thread2(thread_args->clusters, thread_args->num_points, thread_args->k, thread_args->initial_centroids[j] , thread_args->final_centroids[j],thread_args->distance_func);
            thread_args->res_thread = res_th; 

            err = pthread_mutex_lock(thread_args->mutex);
            if(err!=0){
                perror("pthread_mutex_lock");
            }

            write_thread(thread_args->output_file, res_th.temp_distorsion ,thread_args->initial_conserve[j]  ,
                                    res_th.final_centroids , res_th.temps_result_cluster , 
                                    thread_args->k, thread_args->dimension, thread_args->nombre_comb, thread_args->quiet);
            
            err = pthread_mutex_unlock(thread_args->mutex);
            if(err!=0){
                perror("pthread_mutex_unlock");
            }
        }
    }                     
    pthread_exit(NULL);
}

