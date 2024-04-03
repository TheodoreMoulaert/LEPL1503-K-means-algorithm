#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"

/*Modification du code pour que celui-ci soit plus aéré, utilisation d'un double pointeur de cluster
 afin d'avoir un pointeur vers un tableau de clusters ce sera beaucoup plus facile pour le main après*/

cluster_t** update_centroids(cluster_t *clusters[], uint32_t K) {

    for (uint32_t i = 0; i < K; i++)
    {
        cluster_t *currentCluster = clusters[i];
        uint32_t dim = currentCluster->centroide.dim;
        uint32_t *moyenne = calloc(dim, sizeof(uint32_t));

        if (moyenne == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        
        
        if (currentCluster->size < 1){
            fprintf(stderr, "Size of cluster less than 1: division by zero\n");
            return NULL;
        }

        else{

            for (uint64_t yi = 0; yi < currentCluster->size; yi++)
            {
                for (uint64_t xi = 0; xi < dim; xi++)
                {
                    moyenne[xi] += currentCluster->data[yi]->coords[xi];
                }
            }

            for (int64_t xi = 0; xi < dim; xi++)
            {
                moyenne[xi] = moyenne[xi] / currentCluster->size;
                if (currentCluster->centroide.coords[xi] != moyenne[xi])
                {
                    currentCluster->centroide.coords[xi] = moyenne[xi];
                    
                }
            }

            free(moyenne);
        }
    }
    return clusters;
}

