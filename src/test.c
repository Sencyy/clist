#include "list.h"
#include <CUnit/CUError.h>
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>
#include <CUnit/TestDB.h>
#include <stdio.h>

void list_init_test() {
    List l;
    list_init(&l);
    CU_ASSERT_EQUAL(list_length(&l), 0);

    CU_ASSERT_EQUAL(list_pop(&l), 0);
    list_push(&l, 1);
    CU_ASSERT_EQUAL(list_pop(&l), 1);
    CU_ASSERT_EQUAL(list_pop(&l), 0);
}

void list_push_test() {
    List l;
    list_init(&l);

    list_push(&l, 1);
    list_push(&l, 2);
    list_push(&l, 3);
    list_push(&l, 1000);
    list_push(&l, 100000);
    list_push(&l, 1000000000);

    CU_ASSERT_EQUAL(list_length(&l), 6);

    CU_ASSERT_EQUAL(list_pop(&l), 1000000000);
    CU_ASSERT_EQUAL(list_pop(&l), 100000);
    CU_ASSERT_EQUAL(list_pop(&l), 1000);
    CU_ASSERT_EQUAL(list_pop(&l), 3);
    CU_ASSERT_EQUAL(list_pop(&l), 2);
    CU_ASSERT_EQUAL(list_pop(&l), 1);
}

void list_push_back_test() {
    List l;
    list_init(&l);

    list_push_back(&l, 1);
    list_push_back(&l, 2);
    list_push_back(&l, 3);

    CU_ASSERT_EQUAL(list_pop(&l), 1);
    CU_ASSERT_EQUAL(list_pop(&l), 2);
    CU_ASSERT_EQUAL(list_pop(&l), 3);
}

void list_pop_test() {
    List l;
    list_init(&l);

    list_push(&l, 1);
    list_push(&l, 2);
    list_push(&l, 3);

    CU_ASSERT_EQUAL(list_pop(&l), 3);
    CU_ASSERT_EQUAL(list_pop(&l), 2);
    CU_ASSERT_EQUAL(list_pop(&l), 1);
}

void list_pop_back_test() {
    List l;
    list_init(&l);

    list_push(&l, 1);
    list_push(&l, 2);
    list_push(&l, 3);

    CU_ASSERT_EQUAL(list_pop_back(&l), 1);
    CU_ASSERT_EQUAL(list_pop_back(&l), 2);
    CU_ASSERT_EQUAL(list_pop_back(&l), 3);
    CU_ASSERT_EQUAL(list_pop_back(&l), NULL);

}

void list_length_test() {
    List l;
    list_init(&l);

    CU_ASSERT_EQUAL(list_length(&l), 0);

    list_push(&l, 1);
    CU_ASSERT_EQUAL(list_length(&l), 1);

    list_push(&l, 1);
    CU_ASSERT_EQUAL(list_length(&l), 2);

    list_push(&l, 1);
    CU_ASSERT_EQUAL(list_length(&l), 3);

    list_push(&l, 1);
    CU_ASSERT_EQUAL(list_length(&l), 4);

    list_push(&l, 1);
    CU_ASSERT_EQUAL(list_length(&l), 5);

    list_pop(&l);
    CU_ASSERT_EQUAL(list_length(&l), 4);

    list_pop(&l);
    CU_ASSERT_EQUAL(list_length(&l), 3);

    list_pop(&l);
    CU_ASSERT_EQUAL(list_length(&l), 2);

    list_pop(&l);
    CU_ASSERT_EQUAL(list_length(&l), 1);

    list_pop(&l);
    CU_ASSERT_EQUAL(list_length(&l), 0);

}

void list_destroy_test() {
    List l;

    list_init(&l);

    list_push(&l, 1);
    list_push(&l, 2);
    list_push(&l, 3);

    CU_ASSERT_EQUAL(list_pop(&l), 3);
    CU_ASSERT_EQUAL(list_pop(&l), 2);
    CU_ASSERT_EQUAL(list_pop(&l), 1);

    list_push(&l, 1);
    list_push(&l, 2);
    list_push(&l, 3);

    list_destroy(&l);

    CU_ASSERT_EQUAL(list_pop(&l), 0);
    CU_ASSERT_EQUAL(list_length(&l), 0);
}

int main() {
    CU_initialize_registry();
    CU_pSuite test_suite = CU_add_suite("list tests", NULL, NULL);

    CU_add_test(test_suite, "list_init", list_init_test);
    CU_add_test(test_suite, "list_destroy", list_destroy_test);
    CU_add_test(test_suite, "list_push", list_push_test);
    CU_add_test(test_suite, "list_push_back", list_push_back_test);
    CU_add_test(test_suite, "list_pop", list_pop_test);
    CU_add_test(test_suite, "list_pop_back", list_pop_back_test);
    CU_add_test(test_suite, "list_length", list_length_test);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();

    return CU_get_error();
}
