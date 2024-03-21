#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <errno.h>
#include <inttypes.h>
#include "../headers/distance.h"

extern uint32_t k; // Declare as extern
extern uint32_t dim; // Declare as extern
extern FILE* fp; // Declare as extern
extern uint64_t p; // Declare as extern
extern squared_distance_func_t squared_distance_func; // Declare as extern

typedef struct {
    FILE *input_stream;
    FILE *output_stream;
    uint32_t n_threads;
    uint32_t k;
    uint32_t n_first_initialization_points;
    bool quiet;
    squared_distance_func_t squared_distance_func;
} args_t;

#endif // MAIN_H
