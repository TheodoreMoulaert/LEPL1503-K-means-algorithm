#ifndef PARSE_BINARY_INPUT_H
#define PARSE_BINARY_INPUT_H

#include <stdio.h>
#include <stdint.h>
#include "../headers/point.h"

/**
 * Parse binary input file and populate points array.
 * 
 * @param input_stream Pointer to the input binary file stream.
 * @param points Pointer to the array of points to be populated.
 * @param num_points Pointer to store the number of points.
 * @param dimension Pointer to store the dimension of each point.
 * @return 0 on success, -1 on failure.
 */
int parse_binary_input(FILE *input_stream, point_t **points, uint32_t *num_points, uint32_t *dimension);

#endif // PARSE_BINARY_INPUT_H
