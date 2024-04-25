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

result_thread kmeans_thread(cluster_t** clusters, uint64_t num_points, uint32_t k, point_t *initial_centroids, point_t *final_centroids, squared_distance_func_t distance_func);

// Prototype de la fonction k_means_thread
void *k_means_thread(void *args);

#endif //KMEANS_THREAD
