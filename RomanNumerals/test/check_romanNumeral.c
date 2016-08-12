/*
 * check_romanNumeral.c
 *
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */
#include <check.h>
#include "../src/romanNumeral.h"
#include "check_romanNumeral.h"
#include <stdlib.h>

START_TEST(test_romanNumeral_new)
{
	Numeral *m = numeral_new();
	// verify that an object has been created
	ck_assert_int_ne(m,0);
	ck_assert_int_eq(m->value,0);
	ck_assert_str_eq(m->text,"");

	free(m);
}
END_TEST

int main(void)
{
    Suite *s1 = suite_create("Core");
    TCase *tc1_1 = tcase_create("Core");
    SRunner *sr = srunner_create(s1);
    int nf;

    suite_add_tcase(s1, tc1_1);
    tcase_add_test(tc1_1, test_romanNumeral_new);

    srunner_run_all(sr, CK_ENV);
    nf = srunner_ntests_failed(sr);
    srunner_free(sr);

    return nf == 0 ? 0 : 1;
}
