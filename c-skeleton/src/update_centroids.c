#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/main.h"

uint64_t update_centroids(cluster_t* clusters,uint32_t K ){
    cluster_t centroids[K];
    //uint32_t K = (uint32_t)strlen(*clusters);
    /*centroids.data = (point_t*)malloc(k*sizeof(point_t));
    
    if (centroids.data == NULL){
        //for (uint32_t i =0;i<k;i++){
            //free(clusters[i].data->coords);
        //}
        return -1;
    }*/
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

        /*for (int m=0;m<dimension;m++){
            vector_sum[m] = vector_sum[m]/clusters_length;
        }
        centroids[j].data[i].coords = vector_sum;
        centroids[j].data[i].dim = dimension;*/
        //centroids[i].data[j].coords = vector_sum;
        //centroids[i].data[j].dim =  dimension;
        //free(vector_sum);
        //centroids[j].data->coords = vector_sum;
        //centroids[j].data->dim = dimension;
    }

    /*for (int i =0; i<k;i++){
        free(centroids.data[i].coords);
    }
    free(centroids.data);*/
    for (uint32_t i = 0; i < K; i++) {
        free(centroids[i].data->coords);
        free(centroids[i].data);
    }
    //return centroids;
    return 0;
}