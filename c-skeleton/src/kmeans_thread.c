#include <stdbool.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <inttypes.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include "../headers/k_means.h"
#include "../headers/point.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include "../headers/kmeans_thread_args.h"

//Fonction pour le thread k_means 
void *k_means_thread(void *args) { 
    int err;
    k_means_thread_args_t *thread_args = (k_means_thread_args_t *)args;
    //cluster_t **result = k_means(thread_args->clusters, thread_args->num_points, thread_args->k,
                                 //thread_args->initial_centroids, thread_args->final_centroids,
                                 //thread_args->distance_func);
    
    err = pthread_mutex_lock(thread_args->mutex);
    if(err!=0){
        perror("pthread_mutex_lock");
    }
        
    cluster_t **result = k_means(thread_args->clusters, thread_args->num_points, thread_args->k,
                                 thread_args->initial_centroids, thread_args->final_centroids,
                                 thread_args->distance_func);
    
    //(thread_args->final_centroids) = result;
    err = pthread_mutex_unlock(thread_args->mutex);
    if(err!=0){
        perror("pthread_mutex_unlock");
    }
        

    pthread_exit(NULL);
}