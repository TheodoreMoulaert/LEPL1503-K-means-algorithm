#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "cluster.c"

//  attention : ok si on redef point_t avec *coord ??? 
typedef struct {
    int64_t *coord;
} point_t;

typedef struct {
    point_t* tuple;
} cluster_t ;

int8_t update_centroids(cluster_t* clusters){

    point_t* vector_sum = malloc(sizeof(point_t)*K);
    if (vector_sum==NULL){
        for (uint32_t i =0;i<K;i++){
            free(clusters[i].tuple->coord);
    }
    return -1;

    for (uint32_t k=0; k< K; k++){
            // A modifier en fonction de l'écriture de point_t
        vector_sum[k]->coord = calloc(dimension,sizeof(int64_t));
    
            if (vector_sum[k]->coord == NULL){
                for (uint32_t i =0; i<k;i++){
                    free(vector_sum[i]->coord);
                
                }
                for (uint32_t i =0; i<K;i++){
                    free(clusters[i].tuple->coord);
                }
                free(vector_sum);
                return -1;
                
            }
            memcpy(vector_sum[k]->coord,clusters[k].tuple->coord,sizeof(int64_t)*dimension);
            /*for (uint32_t m=0;m<dimension;m++){
                clusters[k].tuple->coord[m] =0;
            }*/
        }
        
        for (uint32_t i=0; i < K; i++){
            for (uint32_t j=0;j<dimension;j++){
                vector_sum[i]->coord[j] += ((clusters[i].tuple->coord[j])/(int64_t)strlen(clusters[i]));

            }
        }

        for (uint32_t i=0; i<K; i++){
            free(vector_sum[i]->coord);
        }
        free(vector_sum);
        return 0;
        


    
    }
/*
    if (LOG){
        fprintf(stderr, "\tUpdate centroids to {");
        for (uint32_t k=0; k < K; k++){
            fprintf(stderr, "{");
            for (uint32_t m =0; m< dimension; m++){
                if (m == 0){
                    fprintf(stderr, "%d", centroids[k].tuple.x);
                }
                else if (m == 1){
                    fprintf(stderr, "%d", centroids[k].tuple.y);
                }
                else if (m == 2){
                    fprintf(stderr, "%d", centroids[k].tuple.z);
                }
                if (m < dimension -1){
                    fprintf(stderr, ",");
                }
            }
            fprintf(stderr, "}");
            if (k < K-1){
                fprintf(stderr,",");
            }
        }
        fprintf(stderr, "}\n");

    }
    return centroids;*/

}