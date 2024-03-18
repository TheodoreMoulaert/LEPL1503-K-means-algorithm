#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <limits.h>

#define MAX_DIMENSION 1000
#define MAX_VECTORS 10000
#define MAX_CLUSTERS 100

typedef struct {
    int coordinates[MAX_DIMENSION];
} Vector;

typedef struct {
    Vector vectors[MAX_VECTORS];
    int size;
} Cluster;

typedef enum {
    MANHATTAN,
    EUCLIDEAN
} DistanceType;

void parse_arguments(int argc, char *argv[], FILE **input_file, FILE **output_file, DistanceType *distance, int *K, int *picking_limit, bool *quiet_mode) {
    // Analyse des arguments de ligne de commande
    if (argc < 2) {
        printf("Usage: %s input_file [options]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    *input_file = fopen(argv[1], "rb");
    if (*input_file == NULL) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    *output_file = stdout;
    *distance = MANHATTAN;
    *K = 0;
    *picking_limit = 0;
    *quiet_mode = false;

    for (int i = 2; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0 || strcmp(argv[i], "--output-file") == 0) {
            if (i + 1 < argc) {
                *output_file = fopen(argv[i + 1], "w");
                if (*output_file == NULL) {
                    perror("Error opening output file");
                    exit(EXIT_FAILURE);
                }
                i++;
            } else {
                fprintf(stderr, "Output file path not provided.\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--distance") == 0) {
            if (i + 1 < argc) {
                if (strcmp(argv[i + 1], "euclidean") == 0) {
                    *distance = EUCLIDEAN;
                } else if (strcmp(argv[i + 1], "manhattan") == 0) {
                    *distance = MANHATTAN;
                } else {
                    fprintf(stderr, "Invalid distance type. Use 'euclidean' or 'manhattan'.\n");
                    exit(EXIT_FAILURE);
                }
                i++;
            } else {
                fprintf(stderr, "Distance type not provided.\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-k") == 0) {
            if (i + 1 < argc) {
                *K = atoi(argv[i + 1]);
                if (*K <= 0) {
                    fprintf(stderr, "Invalid value for K.\n");
                    exit(EXIT_FAILURE);
                }
                i++;
            } else {
                fprintf(stderr, "Value for K not provided.\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-p") == 0 || strcmp(argv[i], "--picking_limit") == 0) {
            if (i + 1 < argc) {
                *picking_limit = atoi(argv[i + 1]);
                if (*picking_limit <= 0) {
                    fprintf(stderr, "Invalid value for picking limit.\n");
                    exit(EXIT_FAILURE);
                }
                i++;
            } else {
                fprintf(stderr, "Value for picking limit not provided.\n");
                exit(EXIT_FAILURE);
            }
        } else if (strcmp(argv[i], "-q") == 0) {
            *quiet_mode = true;
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }
}

void read_binary_file(FILE *input_file, Vector vectors[], int *dimension, int *nbr_vectors) {
    // Lecture du fichier binaire d'entrée
    fread(dimension, sizeof(int), 1, input_file);
    fread(nbr_vectors, sizeof(int), 1, input_file);
    for (int i = 0; i < *nbr_vectors; i++) {
        fread(vectors[i].coordinates, sizeof(int), *dimension, input_file);
    }
}

int euclidean_distance_squared(Vector a, Vector b, int dimension) {
    int distance = 0;
    for (int i = 0; i < dimension; i++) {
        int diff = a.coordinates[i] - b.coordinates[i];
        distance += diff * diff;
    }
    return distance;
}
int manhattan_distance_squared(Vector a, Vector b, int dimension) {
    int distance = 0;
    for (int i = 0; i < dimension; i++) {
        distance += abs(a.coordinates[i] - b.coordinates[i]);
    }
    return distance;
}


void update_centroids(Cluster clusters[], int centroids[][MAX_DIMENSION], int dimension, int K) {
    for (int k = 0; k < K; k++) {
        for (int m = 0; m < dimension; m++) {
            int sum = 0;
            for (int i = 0; i < clusters[k].size; i++) {
                sum += clusters[k].vectors[i].coordinates[m];
            }
            centroids[k][m] = sum / clusters[k].size;
        }
    }
}


bool assign_vectors_to_centroids(Cluster clusters[], int centroids[][MAX_DIMENSION], int dimension, int K, DistanceType distance_type) {
    bool unchanged = true;
    int assigned_indices[MAX_CLUSTERS][MAX_VECTORS] = {0}; // Tableau temporaire pour stocker les indices des vecteurs assignés

    for (int k = 0; k < K; k++) {
        for (int i = 0; i < clusters[k].size; i++) {
            int closest_centroid_idx = -1;
            int closest_distance = INT_MAX;
            for (int j = 0; j < K; j++) {
                int distance;
                if (distance_type == MANHATTAN) {
                    distance = manhattan_distance_squared(clusters[k].vectors[i], clusters[j].vectors[0], dimension);
                } else {
                    distance = euclidean_distance_squared(clusters[k].vectors[i], clusters[j].vectors[0], dimension);
                }
                if (distance < closest_distance) {
                    closest_distance = distance;
                    closest_centroid_idx = j;
                }
            }
            if (closest_centroid_idx != k) {
                unchanged = false;
            }
            // Stocker l'index du vecteur assigné dans le tableau temporaire
            assigned_indices[closest_centroid_idx][clusters[closest_centroid_idx].size++] = i;
        }
    }

    // Réassigner les vecteurs aux clusters en fonction des indices stockés
    for (int k = 0; k < K; k++) {
        for (int i = 0; i < clusters[k].size; i++) {
            clusters[k].vectors[i] = clusters[k].vectors[assigned_indices[k][i]];
        }
    }

    return unchanged;
}



void k_means(Vector vectors[], int dimension, int nbr_vectors, int K, DistanceType distance_type, int picking_limit, bool quiet_mode, FILE *output_file) {
    Cluster clusters[MAX_CLUSTERS];
    for (int i = 0; i < K; i++) {
        clusters[i].size = 0;
    }
    for (int i = 0; i < nbr_vectors; i++) {
        clusters[0].vectors[clusters[0].size++] = vectors[i];
    }
    int centroids[MAX_CLUSTERS][MAX_DIMENSION];
    for (int i = 0; i < K; i++) {
        for (int j = 0; j < dimension; j++) {
            centroids[i][j] = vectors[i].coordinates[j];
        }
    }
    bool changed = true;
    while (changed) {
        changed = !assign_vectors_to_centroids(clusters, centroids, dimension, K, distance_type);
        update_centroids(clusters, centroids, dimension, K);
    }

    // Écriture des résultats dans le fichier de sortie
    if (!quiet_mode) {
        fprintf(output_file, "Clusters:\n");
        for (int k = 0; k < K; k++) {
            fprintf(output_file, "Cluster %d:\n", k + 1);
            for (int i = 0; i < clusters[k].size; i++) {
                fprintf(output_file, "(");
                for (int j = 0; j < dimension; j++) {
                    fprintf(output_file, "%d", clusters[k].vectors[i].coordinates[j]);
                    if (j < dimension - 1) {
                        fprintf(output_file, ", ");
                    }
                }
                fprintf(output_file, ")\n");
            }
            fprintf(output_file, "\n");
        }
    }
}

int main(int argc, char *argv[]) {
    FILE *input_file, *output_file;
    DistanceType distance;
    int K, picking_limit, dimension, nbr_vectors;
    bool quiet_mode;
    Vector vectors[MAX_VECTORS];

    parse_arguments(argc, argv, &input_file, &output_file, &distance, &K, &picking_limit, &quiet_mode);
    read_binary_file(input_file, vectors, &dimension, &nbr_vectors);
    k_means(vectors, dimension, nbr_vectors, K, distance, picking_limit, quiet_mode, output_file);

    fclose(input_file);
    if (output_file != stdout) {
        fclose(output_file);
    }
    return 0;
}
  
