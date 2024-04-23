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

// Prototype de la fonction k_means_thread
void *k_means_thread(void *args);

#endif //KMEANS_THREAD
