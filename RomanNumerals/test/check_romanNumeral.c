/*
 * check_romanNumeral.c
 *  Purpose:
 *  		Check Unit test framework for Roman numeral objects.
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */
#include <check.h>
#include "../src/romanNumeral.h"
#include "check_romanNumeral.h"
#include <stdlib.h>

// Helper method common to several test cases.
NumeralReturnCode commonTestSetup(char* numeralSymbols, Numeral* first)
{
	strncpy(first->text, numeralSymbols, strlen(numeralSymbols));
	Numeral* second = numeral_new();
	strncpy(second->text, validTestCases[1], strlen(validTestCases[0]));
	int answer = 0;
	NumeralReturnCode retCode = add(first, second, &answer);
	free(second);
	return retCode;
}

// Validate that the constructor is working as expected
START_TEST(test_romanNumeral_new)
{
	Numeral *aNumeral = numeral_new();
	// verify that an object has been created
	ck_assert_int_ne(aNumeral,0);
	ck_assert_int_eq(aNumeral->value,0);
	ck_assert_str_eq(aNumeral->text,"");

	free(aNumeral);
}
END_TEST
// Validate that we can detect Null arguments
START_TEST(test_romanNumeral_Null_Numeral)
{
	// Validate check for invalid pointer for first arg
	Numeral *first = NULL;

	Numeral* second = numeral_new();
	strncpy(second->text, validTestCases[1], strlen(validTestCases[0]));
	int answer = 0;
	NumeralReturnCode retCode = add(first, second, &answer);
	free(second);
	second = NULL;
	ck_assert_int_eq((int)retCode, INVALID_PTR);

	// Validate check for invalid pointer for second arg
	first = numeral_new();
	strncpy(first->text, validTestCases[0], strlen(validTestCases[0]));
	int sum =0;
	retCode = add(first, second, &sum);
	ck_assert_int_eq((int)retCode, INVALID_PTR);

	free (first);
}
END_TEST
// Validate that the add rejects input that is larger than the internal buffer.
START_TEST(test_StringTooLong)
{
	const char* const check_str = "Length of input string exceeds storage limit.";
	Numeral *aNumeral = numeral_new();
	// Try to assign a string that is too long;
	char tooLong[] = "MMMMDCCCLXXXVIII";
	NumeralReturnCode retCode = commonTestSetup(tooLong, aNumeral);
	ck_assert_int_eq((int)retCode, STRING_TOO_LONG);
	ck_assert_str_eq(check_str, getRetCodeDesc(retCode));
	free(aNumeral);
}
END_TEST
// Validate that the add rejects a null answer argument
START_TEST(test_NULL_answer)
{
	Numeral *aNumeral = numeral_new();
	char valid[] = "MMMDCCCLXIII";
	strncpy(aNumeral->text, valid, strlen(valid));
	Numeral* second = numeral_new();
	strncpy(second->text, validTestCases[1], strlen(validTestCases[0]));
	int *answer = 0;
	NumeralReturnCode retCode = add(aNumeral, second, answer);
	ck_assert_int_eq((int)retCode, INVALID_PTR);
	free(aNumeral);
	free(second);
}
END_TEST
// Validate that the add rejects invalid TEXT (obvious)
START_TEST(test_InvalidNumeralObvious)
{
	Numeral *aNumeral = numeral_new();
	char invalid[] = "MMMDCCCLXYZ";
	NumeralReturnCode retCode = commonTestSetup(invalid, aNumeral);
	ck_assert_int_eq((int)retCode, INVALID_TEXT);
	free(aNumeral);
}
END_TEST
// Validate that the add rejects invalid TEXT (subtle)
START_TEST(test_InvalidNumeralSubtle)
{
	Numeral *aNumeral = numeral_new();
	char invalid[] = "MMCDCCCLXIII";
	NumeralReturnCode retCode = commonTestSetup(invalid, aNumeral);
	ck_assert_int_eq((int)retCode, INVALID_TEXT);
	free(aNumeral);
}
END_TEST
// Validate that lower case is rejected
START_TEST(test_InvalidLowerCase)
{
	Numeral *aNumeral = numeral_new();
	char valid[] = "mmmdccclxiii";
	NumeralReturnCode retCode = commonTestSetup(valid, aNumeral);
	ck_assert_int_eq((int)retCode, INVALID_TEXT);
	free(aNumeral);
}
END_TEST
// Validate Addition: 345 + 1299
START_TEST(test_SunnyDayAdd)
{
	const int firstNum = 345;
	const int secondNum = 1299;
	const int expectedResult = 1644;
	Numeral *threeFortyFive = numeral_new();
	strncpy(threeFortyFive->text, validTestCases[firstNum], strlen(validTestCases[firstNum]));
	Numeral *twelveHundredNinetyNine =  numeral_new();
	strncpy(twelveHundredNinetyNine->text, validTestCases[secondNum], strlen(validTestCases[secondNum]));
	int answer = 0;
	NumeralReturnCode retCode = add(threeFortyFive, twelveHundredNinetyNine, &answer);
	ck_assert_int_eq(answer, expectedResult);
	ck_assert_int_eq(retCode, EXIT_SUCCESS);
	ck_assert_str_eq("Success",getRetCodeDesc(retCode));
}
END_TEST
// Validate Subtraction: 525 - 25
START_TEST(test_SunnyDaySubtract)
{
	const int firstNum = 525;
	const int secondNum = 25;
	const int expectedResult = 500;
	Numeral *fiveTwentyFive = numeral_new();
	strncpy(fiveTwentyFive->text, validTestCases[firstNum], strlen(validTestCases[firstNum]));
	Numeral *twentyFive =  numeral_new();
	strncpy(twentyFive->text, validTestCases[secondNum], strlen(validTestCases[secondNum]));
	int answer = 0;
	NumeralReturnCode retCode = subtract(fiveTwentyFive, twentyFive, &answer);
	ck_assert_int_eq(answer, expectedResult);
	ck_assert_int_eq(retCode, EXIT_SUCCESS);
}
END_TEST
// Validate Addition: 0 + 25
START_TEST(test_AddZero)
{
	const int firstNum = 0;
	const int secondNum = 25;
	const int expectedResult = 25;
	Numeral *Zero = numeral_new();
	strncpy(Zero->text, validTestCases[firstNum], strlen(validTestCases[firstNum]));
	Numeral *twentyFive =  numeral_new();
	strncpy(twentyFive->text, validTestCases[secondNum], strlen(validTestCases[secondNum]));
	int answer = 0;
	NumeralReturnCode retCode = add(Zero, twentyFive, &answer);
	ck_assert_int_eq(answer, expectedResult);
	ck_assert_int_eq(retCode, EXIT_SUCCESS);
}
END_TEST
// Validate Subtraction: 500 - 0
START_TEST(test_SubtractZero)
{
	const int firstNum = 500;
	const int secondNum = 0;
	const int expectedResult = 500;
	Numeral *fiveHundred = numeral_new();
	strncpy(fiveHundred->text, validTestCases[firstNum], strlen(validTestCases[firstNum]));
	Numeral *zero =  numeral_new();
	strncpy(zero->text, validTestCases[secondNum], strlen(validTestCases[secondNum]));
	int answer = 0;
	NumeralReturnCode retCode = subtract(fiveHundred, zero, &answer);
	ck_assert_int_eq(answer, expectedResult);
	ck_assert_int_eq(retCode, EXIT_SUCCESS);
}
END_TEST
// Validate every possible Numeral 0 - 3999
START_TEST(test_ValidateEveryNumeral)
{
	int index = 0;
	// Use zero as the second number.
	const int secondNum = 0;
	Numeral *zero =  numeral_new();
	strncpy(zero->text, validTestCases[secondNum], strlen(validTestCases[secondNum]));

	for (index = 0; index < MAX_VALID_CASES; index++)
	{
		Numeral *first = numeral_new();
		strncpy(first->text, validTestCases[index], strlen(validTestCases[index]));
		int answer = 0;
		NumeralReturnCode retCode = add(first, zero, &answer);
		ck_assert_int_eq(answer, index);
		ck_assert_int_eq(retCode, EXIT_SUCCESS);
		free (first);
	}
	free (zero);
}
END_TEST
// Validate that we handle negative difference
START_TEST(test_SubtractLessThanZero)
{
	const int firstNum = 525;
	const int secondNum = 1100;
	const int expectedResult = -575;
	Numeral *fiveTwentyFive = numeral_new();
	strncpy(fiveTwentyFive->text, validTestCases[firstNum], strlen(validTestCases[firstNum]));
	Numeral *elevenHundred =  numeral_new();
	strncpy(elevenHundred->text, validTestCases[secondNum], strlen(validTestCases[secondNum]));
	int answer = 0;
	NumeralReturnCode retCode = subtract(fiveTwentyFive, elevenHundred, &answer);
	ck_assert_int_eq(answer, expectedResult);
	ck_assert_int_eq(retCode, NEGATIVE_VALUE);
}
END_TEST
// Validate that we handle overflow.
START_TEST(test_SumGreaterThan3999)
{
	const int firstNum = 3980;
	const int secondNum = 25;
	const int expectedResult = 4005;
	Numeral *first = numeral_new();
	strncpy(first->text, validTestCases[firstNum], strlen(validTestCases[firstNum]));
	Numeral *twentyFive =  numeral_new();
	strncpy(twentyFive->text, validTestCases[secondNum], strlen(validTestCases[secondNum]));
	int answer = 0;
	NumeralReturnCode retCode = add(first, twentyFive, &answer);
	ck_assert_int_eq(answer, expectedResult);
	ck_assert_int_eq(retCode, VALUE_OVERFLOW);
}
END_TEST
// The following two test cases cannot be hit through the normal add/subtract code,
// however for code coverage and testing completeness they are here.
// Validate that it rejects a substring off the end of the source string
START_TEST(test_removeSubstringOffTheEnd)
{
	char sourceString[] = "This is the source string.";
	char validationStr [] = "This is the source str";
	size_t removePosition = 22;
	size_t length = 10;
	int returnCode = removeSubString(sourceString, removePosition, length);
	ck_assert_int_eq(returnCode, EXIT_SUCCESS);
	ck_assert_str_eq(validationStr, sourceString);
}
END_TEST
// Validate that it rejects an invalid position
START_TEST(test_removeSubstringPositionProblem)
{
	char sourceString[] = "This is the source string.";
	size_t removePosition = 50;  // Off the end of the source string
	size_t length = 5;
	int returnCode = removeSubString(sourceString, removePosition, length);
	ck_assert_int_eq(returnCode, EXIT_FAILURE);

	removePosition = -1; // Less than zero;
	returnCode = removeSubString(sourceString, removePosition, length);
	ck_assert_int_eq(returnCode, EXIT_FAILURE);
}
END_TEST


int main(void)
{
    Suite *suite = suite_create("Core");
    TCase *testCaseConstructor = tcase_create("Constructor");
    TCase *testCaseNullNumeral = tcase_create("NullNumeral");
    TCase *testCaseStringTooLong = tcase_create("StringTooLong");
    TCase *testCaseNULL_answer = tcase_create("NULL_answer");
    TCase *testCaseInvalidNumeralObvious = tcase_create("InvalidNumeralObvious");
    TCase *testCaseInvalidNumeralSubtle = tcase_create("InvalidNumeralSubtle");
    TCase *testCaseInvalidLowerCase = tcase_create("InvalidLowerCase");
    TCase *testCaseSunnyDayAdd = tcase_create("SunnyDayAdd");
    TCase *testCaseSunnyDaySubtract = tcase_create("SunnyDaySubtract");
    TCase *testCaseValidateEveryNumeral = tcase_create("ValidateEveryNumeral");
    TCase *testCaseSubtractLessThanZero = tcase_create("SubtractLessThanZero");
    TCase *testCaseAddZero = tcase_create("AddZero");
    TCase *testCaseSubtractZero = tcase_create("SubtractZero");
    TCase *testCaseSumGreaterThan3999 = tcase_create("SumGreaterThan3999");
    TCase *testCaseremoveSubstringPositionProblem = tcase_create("removeSubstringPositionProblem");
    TCase *testCaseremoveSubstringOffTheEnd = tcase_create("removeSubstringOffTheEnd");


    SRunner *suiteRunner = srunner_create(suite);
    int numberFailed;

    suite_add_tcase(suite, testCaseConstructor);
    suite_add_tcase(suite, testCaseNullNumeral);
    suite_add_tcase(suite, testCaseStringTooLong);
    suite_add_tcase(suite, testCaseNULL_answer);
    suite_add_tcase(suite, testCaseInvalidNumeralObvious);
    suite_add_tcase(suite, testCaseInvalidNumeralSubtle);
    suite_add_tcase(suite, testCaseInvalidLowerCase);
    suite_add_tcase(suite, testCaseSunnyDayAdd);
    suite_add_tcase(suite, testCaseSunnyDaySubtract);
    suite_add_tcase(suite, testCaseValidateEveryNumeral);
    suite_add_tcase(suite, testCaseSubtractLessThanZero);
    suite_add_tcase(suite, testCaseAddZero);
    suite_add_tcase(suite, testCaseSubtractZero);
    suite_add_tcase(suite, testCaseSumGreaterThan3999);

    suite_add_tcase(suite, testCaseremoveSubstringPositionProblem);
    suite_add_tcase(suite, testCaseremoveSubstringOffTheEnd);

    tcase_add_test(testCaseConstructor, test_romanNumeral_new);
    tcase_add_test(testCaseNullNumeral, test_romanNumeral_Null_Numeral);
    tcase_add_test(testCaseStringTooLong, test_StringTooLong);
    tcase_add_test(testCaseNULL_answer, test_NULL_answer);
    tcase_add_test(testCaseInvalidNumeralObvious, test_InvalidNumeralObvious);
    tcase_add_test(testCaseInvalidNumeralSubtle, test_InvalidNumeralSubtle);
    tcase_add_test(testCaseInvalidLowerCase, test_InvalidLowerCase);
    tcase_add_test(testCaseSunnyDayAdd, test_SunnyDayAdd);
    tcase_add_test(testCaseSunnyDaySubtract, test_SunnyDaySubtract);
    tcase_add_test(testCaseValidateEveryNumeral, test_ValidateEveryNumeral);
    tcase_add_test(testCaseSubtractLessThanZero, test_SubtractLessThanZero);
    tcase_add_test(testCaseAddZero, test_AddZero);
    tcase_add_test(testCaseSubtractZero, test_SubtractZero);
    tcase_add_test(testCaseSumGreaterThan3999, test_SumGreaterThan3999);
    tcase_add_test(testCaseremoveSubstringPositionProblem, test_removeSubstringPositionProblem);
    tcase_add_test(testCaseremoveSubstringOffTheEnd, test_removeSubstringOffTheEnd);

    srunner_run_all(suiteRunner, CK_ENV);
    numberFailed = srunner_ntests_failed(suiteRunner);
    srunner_free(suiteRunner);

    return numberFailed == 0 ? 0 : 1;
	return 0;
}
