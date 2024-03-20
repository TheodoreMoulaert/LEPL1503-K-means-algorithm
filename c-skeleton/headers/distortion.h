#ifndef DISTORTION_H
#define DISTORTION_H

#include "point.h"    // Include the header file where point_t structure is defined
#include "cluster.h"  // Include the header file where cluster_t structure is defined

// Function prototype for distortion
uint64_t distortion(cluster_t const **clusters, uint32_t num_clusters , squared_distance_func_t DISTANCE_SQUARED);

#endif // DISTORTION_H
