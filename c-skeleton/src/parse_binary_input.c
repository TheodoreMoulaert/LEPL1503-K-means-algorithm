#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "../headers/point.h"

int parse_binary_input(FILE *input_stream, point_t **points, uint32_t *num_points, uint32_t *dimension) {
    // Read dimension and number of points from the binary file
    if (fread(dimension, sizeof(uint32_t), 1, input_stream) != 1) {
        fprintf(stderr, "Error reading dimension from binary file\n");
        return -1;
    }
    if (fread(num_points, sizeof(uint32_t), 1, input_stream) != 1) {
        fprintf(stderr, "Error reading number of points from binary file\n");
        return -1;
    }

    // Allocate memory for points
    *points = (point_t *)malloc(*num_points * sizeof(point_t));
    if (*points == NULL) {
        fprintf(stderr, "Memory allocation failed for points\n");
        return -1;
    }

    // Read points from binary file
    for (uint32_t i = 0; i < *num_points; i++) {
        (*points)[i].coords = (int64_t *)malloc(*dimension * sizeof(int64_t));
        if ((*points)[i].coords == NULL) {
            fprintf(stderr, "Memory allocation failed for point coordinates\n");
            // Free previously allocated memory
            for (uint32_t j = 0; j < i; j++) {
                free((*points)[j].coords);
            }
            free(*points);
            return -1;
        }
        if (fread((*points)[i].coords, sizeof(int64_t), *dimension, input_stream) != *dimension) {
            fprintf(stderr, "Error reading coordinates of point %" PRIu32 " from binary file\n", i);
            // Free previously allocated memory
            for (uint32_t j = 0; j <= i; j++) {
                free((*points)[j].coords);
            }
            free(*points);
            return -1;
        }
        (*points)[i].dim = *dimension;
    }

    return 0;
}
