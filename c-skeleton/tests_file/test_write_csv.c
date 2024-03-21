#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include "../headers/write_csv.h"

void test_create_CSV() {
    // tests avec des données fictives pour s'assurer du fonctionnement 
    uint32_t k = 2; 

    point_t inits1[] = {
        {.dim = 2, .coords = (int64_t[]){1, 2}},
        {.dim = 2, .coords = (int64_t[]){3, 4}},
        {.dim = 2, .coords = (int64_t[]){5, 6}}
    };
    point_t inits2[] = {
        {.dim = 2, .coords = (int64_t[]){0, 0}},
        {.dim = 2, .coords = (int64_t[]){4, 4}},
        {.dim = 2, .coords = (int64_t[]){4, 6}}
    };


    cluster_t clusters[] = {
        {.center = {.dim = 2, .coords = (int64_t[]){2, 2}}, .data = inits1, .size = 3},
        {.center = {.dim = 2, .coords = (int64_t[]){4, 4}}, .data = inits2, .size = 3}
    };



    cluster_t centroid_init = {
        .size = 2,
        .data = (point_t[]){
            {.dim = 2, .coords = (int64_t[]){1, 2}},
            {.dim = 2, .coords = (int64_t[]){3, 4}}
        }
    };


  
    int8_t result = create_CSV(clusters, centroid_init, 100, NULL, k);

    CU_ASSERT_EQUAL(result, 0);
}

int main() {

    if (CUE_SUCCESS != CU_initialize_registry()) {
        return CU_get_error();
    }
    CU_pSuite pSuite = CU_add_suite("Suite", NULL, NULL);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    if ((NULL == CU_add_test(pSuite, "test create_CSV", test_create_CSV))) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
