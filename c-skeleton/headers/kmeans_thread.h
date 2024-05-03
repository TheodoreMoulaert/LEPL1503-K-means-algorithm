#ifndef KMEANS_THREAD
#define KMEANS_THREAD

#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/update_centroids.h"
#include "../headers/assign_vector_to_centro.h"
#include "../headers/kmeans_thread_args.h"
#include "../headers/distance.h"

/**
 * Execute l'algorithme des k-moyennes dans un thread.
 * 
 * @param clusters Tableau de pointeurs vers les clusters initiaux
 * @param num_points Nombre total de points à regrouper
 * @param k Nombre de clusters à former
 * @param initial_centroids Tableau des centroids initiaux
 * @param final_centroids Tableau des centroids finaux mis à jour par l'algorithme
 * @param distance_func Fonction de calcul de distance entre les points
 * @return Résultat de l'algorithme des k-moyennes encapsulé dans une structure result_thread
 */
result_thread kmeans_thread2(cluster_t** clusters, uint64_t num_points, uint32_t k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func);


/**
 * Fonction de démarrage pour le thread k_means.
 * 
 * @param args Pointeur vers une structure contenant les arguments nécessaires pour exécuter l'algorithme des k-moyennes dans un thread
 */
void *k_means_thread(void *args);

#endif //KMEANS_THREAD
