#include "../headers/combinaison.h"
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h" // Assurez-vous que vous avez inclus le fichier de distance
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h> // Pour utiliser PRId64

// Définition des types sol_init_centroids, sol_centro, sol_clusters, sol_distortion, list_init_centroids, list_centro, list_clusters et list_distortion
point_t *sol_init_centroids = NULL;
point_t *sol_centro = NULL;
cluster_t **sol_clusters = NULL;
uint64_t sol_distortion = UINT64_MAX; 

point_t *list_init_centroids = NULL;
point_t *list_centro = NULL;
cluster_t **list_clusters = NULL;
uint64_t *list_distortion = NULL;

int main() {
    // Votre code pour l'allocation de mémoire et les opérations ici

    uint64_t combi = combinaison(p, program_arguments.k);
    
    // Allocation dynamique de mémoire pour les tableaux
    list_init_centroids = malloc(combi * sizeof(point_t));
    list_centro = malloc(combi * sizeof(point_t));
    list_clusters = malloc(combi * sizeof(cluster_t *));
    list_distortion = malloc(combi * sizeof(uint64_t));

    // Vérification des allocations mémoire
    if (list_init_centroids == NULL || list_centro == NULL || list_clusters == NULL || list_distortion == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des clusters initiaux
    cluster_t *centro_initial_list = malloc(combi * sizeof(cluster_t));
    if (centro_initial_list == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les clusters initiaux\n");
        exit(EXIT_FAILURE);
    }

    // Initialisation des combinaisons
    point_t **vect = malloc(combi * sizeof(point_t *));
    if (vect == NULL) {
        fprintf(stderr, "Erreur lors de l'allocation de mémoire pour les vecteurs\n");
        exit(EXIT_FAILURE);
    }

    // Boucle pour l'initialisation des vecteurs
    for (uint64_t i = 0; i < combi; i++) {
        vect[i] = vectors[i];
    }

    // Boucle principale
    for (uint64_t i = 0; i < combi; i++) {
        centro_initial_list[i].data = vect[i];

        cluster_t combi_cluster = *kmeans(centro_initial_list + i, program_arguments.k, num_points, dim, squared_euclidean_distance);

        point_t combi_centro = combi_cluster.center;

        uint64_t combi_distortion = distortion(&combi_cluster, program_arguments.k , squared_euclidean_distance);

        if (sol_distortion > combi_distortion){
            sol_distortion = combi_distortion;
            sol_centro = &combi_centro;
            sol_clusters = &combi_cluster;
            sol_init_centroids = &centro_initial_list[i].center;
        }

        list_init_centroids[i] = centro_initial_list[i].center;
        list_distortion[i] = combi_distortion;
        list_centro[i] = &combi_centro;
        list_clusters[i] = &combi_cluster;
    }

    // Libération de la mémoire
    free(centro_initial_list);
    free(vect);

    for (uint64_t i = 0; i < combi; i++) {
        free(list_clusters[i]->data);
        free(list_clusters[i]);
    }

    free(list_clusters);
    free(list_init_centroids);
    free(list_centro);
    free(list_distortion);

    // Affichage des résultats
    fprintf(stderr, "Best initialisation centroids:\n");
    for (uint64_t i = 0; i < sol_init_centroids->nbr_vector; ++i) {
        fprintf(stderr, "Centroid %lu : (%" PRId64 ", %" PRId64 ")\n", i + 1, sol_init_centroids[i].coords[0], sol_init_centroids[i].coords[1]);
    }

    fprintf(stderr, "Best centroids: (%" PRId64 ", %" PRId64 ")\n", sol_centro->coords[0], sol_centro->coords[1]);

    fprintf(stderr, "Best clusters:\n");
    for (uint64_t i = 0; i < sol_clusters->size; ++i) {
        fprintf(stderr, "Cluster %lu : (%" PRId64 ", %" PRId64 ")\n", i + 1, sol_clusters->data[i].coords[0], sol_clusters->data[i].coords[1]);
    }

    fprintf(stderr, "Minimal sum of squared distances: %" PRId64 "\n", sol_distortion);

    return 0;
}
