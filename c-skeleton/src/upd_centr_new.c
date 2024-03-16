#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

typedef struct{
    int64_t* coord; // (1,1)
} point_t;

typedef struct {
    point_t tuples; // (1,1)
} cluster_t;

int64_t update_centroids( cluster_t* clusters){
    cluster_t centroids;
    centroids.tuples = (point_t*)malloc(K*sizeof(point_t));
    
    if (centroids.tuples == NULL){
        for (uint32_t i =0;i<K;i++){
            free(clusters[i]->tuples->coord);
        }
        return -1;
    }

    for (int k=0;k < K;k++){
        int64_t clusters_length = (int64_t)strlen(clusters[k]);
        point_t vector_sum;
        vector_sum->coord = (int64_t *)calloc(dimension,sizeof(int64_t)); //un tuple
        
        if (vector_sum->coord == NULL){
            free(vector_sum->coord);
            for (uint32_t i =0;i<k;i++){
                free(clusters[i].tuples->coord);
            }
            return -1;
        }

        for (uint32_t i=0; i <clusters_length;i++){
            for (uint32_t m =0;m<dimension;m++){
                vector_sum.coord[m] += clusters[k].tuples[i].coord[m];
            }
        }

        for (int m=0;m<dimension;m++){
            vector_sum.coord[m] = vector_sum.coord[m]/clusters_length;
        }

        centroids.tuples[k] = vector_sum;
    }

    for (int i =0; i<K;i++){
        free(centroids.tuples[i]);
    }
    //free(centroids);
    free(vector_sum);
    return 0;

}
