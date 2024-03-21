#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/main.h"

cluster_t update_centroids( cluster_t *clusters, uint32_t K) {
    uint64_t position = 0; 
    cluster_t centroid;
    centroid.size = K;
    centroid.data = (point_t*)malloc(K * sizeof(point_t));
    if (centroid.data == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (uint32_t k = 0; k < K; k++) {
        point_t vector_sum;
        vector_sum.dim = clusters[k].data[position].dim;
        vector_sum.coords = (int64_t*)calloc(vector_sum.dim, sizeof(int64_t));
        if (vector_sum.coords == NULL) {
            
            fprintf(stderr, "Erreur lors de l'allocation de mémoire\n"); 
            exit(EXIT_FAILURE);
        }

        for (uint32_t  i = 0; i < clusters[k].size; i++) {
            for (uint32_t j = 0; j < clusters[k].data[i].dim; j++) {
                vector_sum.coords[j] += clusters[k].data[i].coords[j];

            }
        }

        for (uint32_t j = 0; j < vector_sum.dim; j++) {
            vector_sum.coords[j] /= clusters[k].size;
             
        }

        centroid.data[k] = vector_sum;

        position +=1; 
        

    }
    return centroid;
}

/*uint64_t update_centroids(cluster_t* clusters, uint32_t K) {
    cluster_t centroids[K];

    for (uint32_t j = 0; j < K; j++) {
        centroids[j].size = clusters[j].size;
        centroids[j].data = (point_t*)malloc(clusters[j].size * sizeof(point_t));

        if (centroids[j].data == NULL) {
            // Gestion de l'erreur : échec de l'allocation de mémoire pour centroids[j].data
            for (uint32_t i = 0; i < j; i++) {
                free(centroids[i].data);
            }
            return -1;
        }

        uint32_t clusters_length = clusters[j].size;
        uint32_t dimension = clusters[j].data[0].dim;

        int64_t* vector_sum = (int64_t*)calloc(dimension, sizeof(int64_t)); // Initialisation du vecteur somme

        if (vector_sum == NULL) {
            for (uint32_t i = 0; i < j; i++) {
                free(centroids[i].data);
            }
            return -1;
        }

        for (uint32_t i = 0; i < clusters_length; i++) {
            for (uint32_t m = 0; m < dimension; m++) {
                vector_sum[m] += clusters[j].data[i].coords[m];
            }
        }

        for (uint32_t m = 0; m < dimension; m++) {
            vector_sum[m] = vector_sum[m] / clusters_length;
        }

        for (uint32_t i = 0; i < clusters_length; i++) {
            centroids[j].data[i].coords = (int64_t*)malloc(dimension * sizeof(int64_t));
            if (centroids[j].data[i].coords == NULL) {
                for (uint32_t k = 0; k < i; k++) {
                    free(centroids[j].data[k].coords);
                }
                free(centroids[j].data);
                free(vector_sum);
                return -1;
            }
            memcpy(centroids[j].data[i].coords, vector_sum, dimension * sizeof(int64_t));
            centroids[j].data[i].dim = dimension;
        }

        free(vector_sum);
    }

    for (uint32_t i = 0; i < K; i++) {
        for (uint32_t j = 0; j < clusters[i].size; j++) {
            free(clusters[i].data[j].coords);
        }
        free(clusters[i].data);
    }

    return 0;
}*/
/*uint64_t update_centroids(cluster_t* clusters,uint32_t K ){
    cluster_t centroids[K];
    //uint32_t K = (uint32_t)strlen(*clusters);
    
    for (uint32_t j = 0; j < K; j++) {
        centroids[j].data = (point_t*)malloc(clusters[j].size * sizeof(point_t));

        if (centroids[j].data == NULL) {
            // Gestion de l'erreur : échec de l'allocation de mémoire pour centroids[j].data
            for (uint32_t i = 0; i < j; i++) {
                free(centroids[i].data);
            }
            return -1;
        }
    
        uint64_t clusters_length = clusters[j].size;
        uint32_t dimension = clusters[j].data->dim;
        int64_t* vector_sum =(int64_t *)calloc(dimension,sizeof(int64_t)); //un tuple
        
        if (vector_sum == NULL){
            //free(vector_sum);
            free(centroids->data);
            for (uint32_t i =0;i<j;i++){
                //free(clusters[i].data->coords);
                //free(clusters[i].data[j].coords);
                free(centroids[i].data);
            }
            return -1;
        }

        for (uint32_t i=0; i <clusters_length;i++){
            for (uint32_t m =0;m<dimension;m++){
                vector_sum[m] += clusters[j].data[i].coords[m];
            }
            for (int m=0;m<dimension;m++){
            vector_sum[m] = vector_sum[m]/clusters_length;
            }
            centroids[j].data[i].coords = vector_sum;
            centroids[j].data[i].dim = dimension;
    
        }

    
        //centroids[i].data[j].coords = vector_sum;
        //centroids[i].data[j].dim =  dimension;
        //free(vector_sum);
        //centroids[j].data->coords = vector_sum;
        //centroids[j].data->dim = dimension;
    }

    
    for (uint32_t i = 0; i < K; i++) {
        free(centroids[i].data->coords);
        free(centroids[i].data);
    }
    //return centroids;
    return 0;
}*/

/*#include "../headers/update_centroids.h"
#include <stdlib.h>

cluster_t update_centroids(cluster_list *clusters, uint32_t K) {
    uint64_t position = 0; 
    cluster_t centroid;
    centroid.size = K;
    centroid.data = (point_t*)malloc(K * sizeof(point_t));
    if (centroid.data == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    for (uint32_t k = 0; k < K; k++) {
        point_t vector_sum;
        vector_sum.dim = clusters[k].data[position].dim;
        vector_sum.coords = (int64_t*)calloc(vector_sum.dim, sizeof(int64_t));
        if (vector_sum.coords == NULL) {
            
            fprintf(stderr, "Erreur lors de l'allocation de mémoire\n"); 
            exit(EXIT_FAILURE);
        }

        for (uint32_t i = 0; i < clusters[k].size; i++) {
            for (uint32_t j = 0; j < clusters[k].data[i].dim; j++) {
                v_sum.elements[j] += clusters[k].data[i].coord[j];

            }
        }

        for (uint32_t j = 0; j < vector_sum.dim; j++) {
            vector_sum.dim[j] /= clusters[k].size;
             
        }

        centroid.data[k] = v_sum;

        position +=1; 

    }
    return centroid;
}*/