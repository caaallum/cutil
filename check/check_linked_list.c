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
#include <cutil/linked_list.h>

START_TEST(test_linked_list_new) {
    int a = 1;
    node_t *list = linkedlist_new(&a);

    ck_assert_ptr_nonnull(list);
    ck_assert_int_eq(1, *(int*)list->val);
    ck_assert_ptr_null(list->next);
}
END_TEST

Suite *
linked_list_suite(void) {
    Suite *s;
    TCase *tc_core;

    s = suite_create("Linked List");
    tc_core = tcase_create("Core");

    return s;
}

int
main(void) {
    int number_failed;
    Suite *s;
    SRunner *sr;

    s = linked_list_suite();
    sr = srunner_create(s);

    srunner_run_all(sr, CK_VERBOSE);
    number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
