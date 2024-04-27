#ifndef DISTANCE_H
#define DISTANCE_H
#include <stdint.h>

#include "../headers/point.h"
#include "../headers/cluster.h"

/**
 * Ce typedef ci-dessous définit le type distance_func_t, un type de pointeur de fonction qui regroupe toutes
 * les fonctions ayant la signature suivante :
 * 
 *       int64_t nom_fonction(const point_t *, const point_t *)
 *
 * Donc fondamentalement, une fois que vous avez implémenté squared_manhatan_distance et squared_euclidean_distance,
 * vous pouvez faire ce qui suit si vous le souhaitez :
 *
 *       squared_distance_func_t fonction_generique;
 *      if (some_condition) {
 *          fonction_generique = squared_manhattan_distance;
 *      } else {
 *          fonction_generique = squared_euclidean_distance;
 *      }
 *       int64_t dist = fonction_generique(a, b); // calcule soit la distance de Manhattan soit la distance euclidienne selon la some_condition
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



uint64_t distortion(cluster_t const **clusters, uint32_t num_clusters, squared_distance_func_t DISTANCE_SQUARED);
/**
 * @return la distorsion moyenne
 */

#endif //DISTANCE_H
