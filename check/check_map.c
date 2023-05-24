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

#include <cutil/map.h>

#include <check.h>
#include <stdlib.h>

START_TEST(test_map_new) {
  map_t *map;

  map = map_new();

  ck_assert_ptr_nonnull(map);
  ck_assert_int_eq(map_total(map), 0);

  map_destroy(map);
}
END_TEST

START_TEST(test_map_add_string) {
  map_t *map;

  map = map_new();
  int a = 1;

  map_add(map, "key", &a);

  ck_assert_int_eq(map_total(map), 1);

  map_destroy(map);
}
END_TEST

START_TEST(test_map_add_string_many) {
  map_t *map;
  int a = 1, b = 2, c = 3, d = 4;

  map = map_new();

  map_add(map, "a", &a);
  ck_assert_int_eq(map_total(map), 1);
  map_add(map, "b", &b);
  ck_assert_int_eq(map_total(map), 2);
  map_add(map, "c", &c);
  ck_assert_int_eq(map_total(map), 3);
  map_add(map, "d", &d);
  ck_assert_int_eq(map_total(map), 4);

  map_destroy(map);
}
END_TEST

START_TEST(test_map_get_string) {
  map_t *map;
  int a = 1;

  map = map_new();

  map_add(map, "a", &a);

  ck_assert_int_eq(a, map_get_int(map, "a"));

  map_destroy(map);
}
END_TEST

START_TEST(test_map_get_string_many) {
  map_t *map;
  int a = 1, b = 2, c = 3, d = 4;

  map = map_new();

  map_add(map, "a", &a);
  ck_assert_int_eq(a, map_get_int(map, "a"));

  map_add(map, "b", &b);
  ck_assert_int_eq(b, map_get_int(map, "b"));

  map_add(map, "c", &c);
  ck_assert_int_eq(c, map_get_int(map, "c"));

  map_add(map, "d", &d);
  ck_assert_int_eq(d, map_get_int(map, "d"));

  map_destroy(map);
}
END_TEST

Suite *map_suite(void) {
  Suite *s;
  TCase *tc_core, *tc_string;

  s = suite_create("map");

  /* Core */
  tc_core = tcase_create("Core");
  tcase_add_test(tc_core, test_map_new);

  suite_add_tcase(s, tc_core);

  /* String */
  tc_string = tcase_create("String");
  tcase_add_test(tc_string, test_map_add_string);
  tcase_add_test(tc_string, test_map_add_string_many);
  tcase_add_test(tc_string, test_map_get_string);
  tcase_add_test(tc_string, test_map_get_string_many);

  suite_add_tcase(s, tc_string);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s;
  SRunner *sr;

  s = map_suite();
  sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);
  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
