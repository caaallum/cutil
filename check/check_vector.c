/**********************************************************
 * This file is part of cutil.
 *
 * cutil is free software: you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License 
 * as published by the Free SoftwareFoundation, either version 3 
 * of the License, or (at your option) any later version.
 * 
 * cutil is distributed in the hope that it will be useful, 
 * but WITHOUT ANY WARRANTY; without even the implied warranty of 
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License 
 * along with cutil. If not, see <https://www.gnu.org/licenses/>.
 **********************************************************/

#include <stdlib.h>
#include <check.h>
#include <cutil/vector.h>

START_TEST(test_vector_new) {
    vector_t *v = vector_new();

    ck_assert_ptr_nonnull(v);
    ck_assert_int_eq(vector_size(v), 0);

    vector_destroy(v);
}
END_TEST

START_TEST(test_vector_add) {
    vector_t *v = vector_new();

    int a = 1,
        b = 2,
        c = 3;
    vector_add(v, &a);
    ck_assert_int_eq(vector_size(v), 1);
    ck_assert_int_eq(*((int *)vector_get(v, 0)), 1);

    vector_add(v, &b);
    ck_assert_int_eq(vector_size(v), 2);
    ck_assert_int_eq(*((int *)vector_get(v, 1)), 2);

    vector_add(v, &c);
    ck_assert_int_eq(vector_size(v), 3);
    ck_assert_int_eq(*((int *)vector_get(v, 2)), 3);

    vector_destroy(v);
}
END_TEST

START_TEST(test_vector_addv) {
    vector_t *v = vector_new();

    int a = 1,
        b = 2,
        c = 3;
    vector_addv(v, &a, &b, &c);

    ck_assert_int_eq(vector_size(v), 3);
    ck_assert_int_eq(*((int *)vector_get(v, 0)), 1);
    ck_assert_int_eq(*((int *)vector_get(v, 1)), 2);
    ck_assert_int_eq(*((int *)vector_get(v, 2)), 3);

    vector_destroy(v);
}
END_TEST

START_TEST(test_vector_foreach) {
    vector_t *v = vector_new();

    int a = 1,
        b = 2,
        c = 3;
    vector_addv(v, &a, &b, &c);

    V_FOREACH(v, int, obj) {
        switch (i) {
            case 0:
                ck_assert_int_eq(*obj, a);
                break;
            case 1:
                ck_assert_int_eq(*obj, b);
                break;
            case 2:
                ck_assert_int_eq(*obj, c);
                break;
        }
    }
    vector_destroy(v);
}
END_TEST

START_TEST(test_vector_delete) {
    vector_t *v = vector_new();

    int a = 1,
        b = 2,
        c = 3;
    vector_addv(v, &a, &b, &c);

    ck_assert_int_eq(vector_size(v), 3);
    vector_delete(v, 1);

    ck_assert_int_eq(vector_size(v), 2);
    ck_assert_int_eq(*((int *)vector_get(v, 0)), 1);
    ck_assert_int_eq(*((int *)vector_get(v, 1)), 3);

    vector_destroy(v);
}
END_TEST

Suite *
vector_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Vector");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_vector_new);
    tcase_add_test(tc_core, test_vector_add);
    tcase_add_test(tc_core, test_vector_addv);
    tcase_add_test(tc_core, test_vector_foreach);
    tcase_add_test(tc_core, test_vector_delete);
    suite_add_tcase(s, tc_core);

    return s;
}

int
main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = vector_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
