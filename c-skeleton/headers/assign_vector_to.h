#ifndef ASSIGN_VECTOR_TO_H
#define ASSIGN_VECTOR_TO_H
#include "../headers/point.h" // Inclure si nécessaire
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"


#include <stdint.h>
#include <stdio.h> // Inclure pour FILE *

int assign_vectors_to_centroids(double **centroids, double ***clusters, int num_centroids, int num_vectors, int dimensions); 


#endif // BINARY_FILE_READER_H