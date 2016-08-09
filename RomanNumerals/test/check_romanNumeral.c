/*
 * check_romanNumeral.c
 *
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */
#include <check.h>
#include "../src/romanNumeral.h"

START_TEST(test_romanNumeral_new)
{
	Numeral *m = Numeral_new();
	// verify that an object has been created
	ck_assert_int_ne(m,0);
	ck_assert_int_eq(m->value,0);
	ck_assert_str_eq(m->text,"");
}
END_TEST

int main(void)
{
	return 0;
}
