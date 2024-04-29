/*#include <stdbool.h>
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
#include "../headers/write_thread.h"*/


/*result_thread kmeans_thread(cluster_t** clusters, uint64_t num_points, uint32_t k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func) {
   
    result_t result; 
    result_thread res_thread;

    if (clusters == NULL || initial_centroids == NULL || final_centroids == NULL) {
        fprintf(stderr, "Paramètres invalides pour la fonction k_means.\n");
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
        // Affichage des centroids finaux
        printf("Centroids finaux à l'itération %ld:\n", i + 1);
        for (int j = 0; j < k; j++) {
            printf("Centroid %d: (%" PRId64 ", %" PRId64 ")\n", j, final_centroids[j].coords[0], final_centroids[j].coords[1]);
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
}*/



/*//Fonction pour le thread k_means 
void *k_means_thread(void *args) { 
    int err;
    k_means_thread_args_t *thread_args = (k_means_thread_args_t*) args;
    result_thread res_th;
    
    for (uint32_t r = 0; r < 1; r++){
        if (thread_args->position >= thread_args->nombre_comb ){
            err = pthread_mutex_lock(thread_args->mutex);
            if(err!=0){
                perror("pthread_mutex_lock");
            }
            thread_args->position++;
            err = pthread_mutex_unlock(thread_args->mutex);
                if(err!=0){
                    perror("pthread_mutex_unlock");
                }
        }
        else if ((thread_args->position == thread_args->n_thread-2) && (thread_args->position < thread_args->nombre_comb-1)){ 
            uint32_t j = thread_args->position;
            while ( thread_args->position < thread_args->nombre_comb){
                err = pthread_mutex_lock(thread_args->mutex);
                if(err!=0){
                    perror("pthread_mutex_lock");
                }

                res_th = kmeans_thread(thread_args->clusters, thread_args->num_points, thread_args->k,
                                            thread_args->initial_centroids[j] , thread_args->final_centroids[j],
                                            thread_args->distance_func);
                thread_args->res_thread = res_th;                            
                
                write_thread(thread_args->output_file, res_th.temp_distorsion ,thread_args->initial_conserve[j]  ,
                                res_th.final_centroids , res_th.temps_result_cluster , 
                                thread_args->k, thread_args->dimension, thread_args->nombre_comb);
                thread_args->position++;
                err = pthread_mutex_unlock(thread_args->mutex);
                if(err!=0){
                    perror("pthread_mutex_unlock");
                } 
            
            
            }
        }
        else {
            err = pthread_mutex_lock(thread_args->mutex);
            if(err!=0){
                perror("pthread_mutex_lock");
            }

            res_th = kmeans_thread(thread_args->clusters, thread_args->num_points, thread_args->k,
                                        thread_args->initial_centroids[thread_args->position] , thread_args->final_centroids[thread_args->position],
                                        thread_args->distance_func);

            thread_args->res_thread = res_th; 

            write_thread(thread_args->output_file, res_th.temp_distorsion ,thread_args->initial_conserve[thread_args->position] ,
                             res_th.final_centroids , res_th.temps_result_cluster, 
                             thread_args->k, thread_args->dimension, thread_args->nombre_comb);
            
            thread_args->position++;

            err = pthread_mutex_unlock(thread_args->mutex);
            if(err!=0){
                perror("pthread_mutex_unlock");
            } 
        } 
        
    }                       
    pthread_exit(NULL);
}*/