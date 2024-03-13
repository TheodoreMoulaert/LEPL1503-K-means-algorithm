#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#include "cluster.c"


cluster_t update_centroids(cluster_t** clusters){
    cluster_t* centroids;
    for (uint32_t k=0; k< K; k++){
        // A modifier en fonction de l'écriture de point_t
        cluster_t vector_sum;
        //est ce qu'il faut faire un malloc 

        vector_sum.tuple.x = 0;
        vector_sum.tuple.y = 0;
        vector_sum.tuple.z = 0;
        for (uint32_t clusters_size=0; clusters_size < strlen(clusters[k]); clusters_size++){
            vector_sum.tuple.x += (clusters[k][clusters_size].tuple.x)/strlen(clusters[k]);
            vector_sum.tuple.y += (clusters[k][clusters_size].tuple.y)/strlen(clusters[k]);
            vector_sum.tuple.z += (clusters[k][clusters_size].tuple.z)/strlen(clusters[k]);


        }
        centroids[k] = vector_sum;


    
    }

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
    return centroids;

}