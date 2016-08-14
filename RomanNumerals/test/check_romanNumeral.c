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

// Validate that the constructor is working as expected
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
// Validate that we can detect Null arguments
START_TEST(test_romanNumeral_Null_Numeral)
{
	// Validate check for invalid pointer for first arg
	Numeral *first = NULL;
	Numeral *second = numeral_new();
	strncpy(second->text, validTestCases[0], strlen(validTestCases[0]));
	int sum = 0;
	NumeralReturnCode retCode = add(first, second, &sum);
	ck_assert_int_eq((int)retCode, INVALID_PTR);

	free (second);

	// Validate check for invalid pointer for second arg
	first = numeral_new();
	second = NULL;
	strncpy(first->text, validTestCases[0], strlen(validTestCases[0]));

	retCode = add(first, second, &sum);
	ck_assert_int_eq((int)retCode, INVALID_PTR);

	free (first);
}
END_TEST
// Validate that the constructor is working as expected
START_TEST(test_StringNotTerm)
{
	Numeral *m = numeral_new();
	// Try to assign a string that is too long;
	char tooLong[] = "MMMMDCCCLXXXVIII";
	strncpy (m->text, tooLong, sizeof(tooLong));
	Numeral *second = numeral_new();
	strncpy(second->text, validTestCases[0], strlen(validTestCases[0]));
	int sum = 0;
	NumeralReturnCode retCode = add(m, second, &sum);
	ck_assert_int_eq((int)retCode, STRING_TOO_LONG);
	free(m);
}
END_TEST
int main(void)
{
    Suite *suite = suite_create("Core");
    TCase *testCaseConstructor = tcase_create("Constructor");
    TCase *testCaseNullNumeral = tcase_create("NullNumeral");
    TCase *testCaseStringNotTerm = tcase_create("StringNotTerm");
    SRunner *suiteRunner = srunner_create(suite);
    int numberFailed;

    suite_add_tcase(suite, testCaseConstructor);
    suite_add_tcase(suite, testCaseNullNumeral);
    suite_add_tcase(suite, testCaseStringNotTerm);
    tcase_add_test(testCaseConstructor, test_romanNumeral_new);
    tcase_add_test(testCaseNullNumeral, test_romanNumeral_Null_Numeral);
    tcase_add_test(testCaseStringNotTerm, test_StringNotTerm);

    srunner_run_all(suiteRunner, CK_ENV);
    numberFailed = srunner_ntests_failed(suiteRunner);
    srunner_free(suiteRunner);

    return numberFailed == 0 ? 0 : 1;
//	Numeral *m = numeral_new();
//
//	char valid[] = "MMMDCCCLXIII";
//	strncpy (m->text, valid, sizeof(valid));
//	Numeral *second = numeral_new();
//	strncpy(second->text, validTestCases[1], strlen(validTestCases[0]));
//	int sum = 0;
//	NumeralReturnCode retCode = add(m, second, &sum);
//	ck_assert_int_eq((int)retCode, STRING_TOO_LONG);
//	free(m);
	return 0;
}
