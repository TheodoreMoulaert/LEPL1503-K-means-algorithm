#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>



int64_t update_centroids( cluster_t* clusters){
    cluster_t centroids;
    centroids->data = (point_t*)malloc(K*sizeof(point_t));
    
    if (centroids->data == NULL){
        for (uint32_t i =0;i<K;i++){
            free(clusters[i]->data->coord);
        }
        return -1;
    }

    for (int k=0;k < K;k++){
        int64_t clusters_length = (int64_t)strlen(clusters[k]);
        uint32_t dimension = clusters[k]->data.dim;
        int64_t* vector_sum = (int64_t *)calloc(dimension,sizeof(int64_t)); //un tuple
        
        if (vector_sum == NULL){
            free(vector_sum);
            for (uint32_t i =0;i<k;i++){
                free(clusters[i]->data->coord);
            }
            return -1;
        }

        for (uint32_t i=0; i <clusters_length;i++){
            for (uint32_t m =0;m<dimension;m++){
                vector_sum[m] += clusters[k].data[i].coord[m];
            }
        }

        for (int m=0;m<dimension;m++){
            vector_sum[m] = vector_sum[m]/clusters_length;
        }

        centroids.data[k] = vector_sum;
        //free(vector_sum);
    }

    for (int i =0; i<K;i++){
        free(centroids.data[i]);
    }
    free(centroids);
    
    return 0;

}