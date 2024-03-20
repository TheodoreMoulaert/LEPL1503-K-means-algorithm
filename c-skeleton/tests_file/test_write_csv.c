#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/write_csv.h"

void test_create_CSV() {
    // Déclaration et initialisation de k
    uint32_t k = 2; // Remplacez 2 par la valeur appropriée selon votre cas

    // Création de quelques points fictifs
    point_t inits[] = {
        {.dim = 2, .coords = (int64_t[]){1, 2}},
        {.dim = 2, .coords = (int64_t[]){3, 4}},
        {.dim = 2, .coords = (int64_t[]){5, 6}}
    };

    // Création de quelques clusters fictifs
    cluster_t clusters[] = {
        {.center = {.dim = 2, .coords = (int64_t[]){2, 2}}, .data = inits, .size = 3},
        {.center = {.dim = 2, .coords = (int64_t[]){4, 4}}, .data = inits, .size = 3}
    };

    // Appel de la fonction create_CSV
    int8_t result = create_CSV(inits, clusters, 100, NULL, k);

    CU_ASSERT_EQUAL(result, 0);
}


int main() {
    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }

    // Add a suite to the registry
    CU_pSuite pSuite = CU_add_suite("Suite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Add the test function to the suite
    if ((NULL == CU_add_test(pSuite, "test create_CSV", test_create_CSV))) {
        CU_cleanup_registry();
        return CU_get_error();
    }

    // Run the tests
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}

