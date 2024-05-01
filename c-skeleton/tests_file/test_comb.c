#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>
#include "../headers/point.h"
#include "../headers/cluster.h"
#include "../headers/distance.h"
#include "../headers/combinaison.h"
#include "CUnit/Basic.h"

int init_suite(void) {
    return 0;
}

int clean_suite(void) {
    return 0;
}

void test_combinations(void) {
    int64_t coordinates[7][2] = {
        {1, 1},
        {2, 2},
        {3, 4},
        {5, 7},
        {3, 5},
        {5, 5},
        {4, 5}
    };

    point_t **vectors = malloc(7 * sizeof(point_t *));
    CU_ASSERT_PTR_NOT_NULL_FATAL(vectors);

    for (int i = 0; i < 7; i++) {
        vectors[i] = malloc(sizeof(point_t));
        CU_ASSERT_PTR_NOT_NULL_FATAL(vectors[i]);
        
        vectors[i]->coords = malloc(2 * sizeof(int64_t));
        CU_ASSERT_PTR_NOT_NULL_FATAL(vectors[i]->coords);
        
        vectors[i]->coords[0] = coordinates[i][0];
        vectors[i]->coords[1] = coordinates[i][1];
        vectors[i]->dim = 2;
    }

    uint64_t n = 7;
    uint32_t k = 2;
    uint32_t p = 3;

    point_t ***combinations = generate_combinations(vectors, n, k, p);
    CU_ASSERT_PTR_NOT_NULL_FATAL(combinations);

    // Test combinations
    CU_ASSERT_EQUAL(combinations[0][0]->coords[0], 1);
    CU_ASSERT_EQUAL(combinations[0][0]->coords[1], 1);
    CU_ASSERT_EQUAL(combinations[0][1]->coords[0], 2);
    CU_ASSERT_EQUAL(combinations[0][1]->coords[1], 2);

    CU_ASSERT_EQUAL(combinations[1][0]->coords[0], 1);
    CU_ASSERT_EQUAL(combinations[1][0]->coords[1], 1);
    CU_ASSERT_EQUAL(combinations[1][1]->coords[0], 3);
    CU_ASSERT_EQUAL(combinations[1][1]->coords[1], 4);

    CU_ASSERT_EQUAL(combinations[2][0]->coords[0], 2);
    CU_ASSERT_EQUAL(combinations[2][0]->coords[1], 2);
    CU_ASSERT_EQUAL(combinations[2][1]->coords[0], 3);
    CU_ASSERT_EQUAL(combinations[2][1]->coords[1], 4);

    // Free memory
    for (uint64_t i = 0; i < combinaison(p, k); i++) {
        free(combinations[i]);
    }
    free(combinations);

    for (int i = 0; i < 7; i++) {
        free(vectors[i]->coords);
        free(vectors[i]);
    }
    free(vectors);
}

int main() {
    CU_pSuite pSuite = NULL;

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    pSuite = CU_add_suite("Suite de tests", init_suite, clean_suite);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    if ((NULL == CU_add_test(pSuite, "test_combinations", test_combinations))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}
