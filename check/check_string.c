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

#include <cutil/string.h>

#include <check.h>
#include <stdlib.h>

START_TEST(test_string_new) {
    const char *str = "Hello World";
    string_t *s = string_new(str);

    ck_assert_ptr_nonnull(s);
    ck_assert_ptr_nonnull(s->str);
    ck_assert_str_eq(s->str, str);

    string_destroy(s);
}
END_TEST

START_TEST(test_string_append) {
    const char *str = "Hello";
    const char *world = " World";
    string_t *s = string_new(str);

    ck_assert_str_eq(s->str, str);

    string_append(s, world);

    ck_assert_str_eq(s->str, "Hello World");

    string_destroy(s);
}
END_TEST

START_TEST(test_string_prepend) {
    const char *world = "World";
    const char *hello = "Hello ";
    string_t *s = string_new(world);

    ck_assert_str_eq(s->str, world);

    string_prepend(s, hello);

    ck_assert_str_eq(s->str, "Hello World");

    string_destroy(s);
}
END_TEST

Suite *string_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("string");

    /* Core */
    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_string_new);
    tcase_add_test(tc_core, test_string_append);
    tcase_add_test(tc_core, test_string_prepend);

    suite_add_tcase(s, tc_core);

    suite_add_tcase(s, tc_core);

    return s;
}

int main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = string_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
