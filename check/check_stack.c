#include <cutil/stack.h>

#include <check.h>
#include <stdlib.h>

START_TEST(test_stack_new) {
    stack_t *stack;

    stack = stack_new();

    ck_assert_ptr_nonnull(stack);
    ck_assert_int_eq(stack_size(stack), 0);

    stack_destroy(stack);
}
END_TEST

Suite *stack_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("stack");

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_stack_new);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = stack_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
