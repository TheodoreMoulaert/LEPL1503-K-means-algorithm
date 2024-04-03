#ifndef DISTANCE_H
#define DISTANCE_H
#include <stdint.h>

#include "../headers/point.h"
#include "../headers/cluster.h"

/**
 * This typedef below defines the distance_func_t type, a function pointer type that groups all
 * functions with the following signature :
 *
 *      int64_t function_name(const point_t *, const point_t *)
 *
 * So basically, once you've implemented squared_manhatan_distance and squared_euclidean_distance,
 * you can do the following if you want:
 *
 *      squared_distance_func_t generic_func;
 *      if (some_condition) {
 *          generic_func = squared_manhattan_distance;
 *      } else {
 *          generic_func = squared_euclidean_distance;
 *      }
 *      int64_t dist = generic_func(a, b); // computes either the manhattan distance or the euclidean distance depending on the some_condition
 *
 */
typedef int64_t (*squared_distance_func_t) (const point_t *, const point_t *);

/**
 * @return the squared manhattan distance between 2 points
 */
int64_t squared_manhattan_distance(const point_t *, const point_t *);

/**
 * @return the squared euclidean distance between 2 points
 */
int64_t squared_euclidean_distance(const point_t *, const point_t *);



uint64_t distortion(cluster_t const *clusters, uint32_t num_clusters, squared_distance_func_t DISTANCE_SQUARED);
/**
 * @return la distorsion moyenne
 */

#endif //DISTANCE_H
