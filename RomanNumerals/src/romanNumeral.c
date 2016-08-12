/*
 * romanNumeral.c
 *
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */
#include "romanNumeral.h"
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdio.h>
#include <ctype.h>

// Return code strings
static const char* const retDesc[] =
{
		"Success",
		"Could not determine length of input string.",
		"Numeral does not contain a valid Roman Numeral.",
		"Sum is greater than maximum value.",
		"Difference is less than 0.",
		"Argument is null.",
		"regcomp returned error."
};
const char* getRetCodeDesc(NumeralReturnCode retCode)
{
	return retDesc[retCode];
}
// Regular expression string used to validate input string.
static char const* const ValidationRegEx =
		"^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$";
// Maximum value
const int MaximumValue = 3999;

// Decomposed Numeral parts and their integer equivalents
// The strange order is intentional to aid in parsing.
static char const* const NumeralComponents[] = { "MMM", "MM", "CM", "M", "DCCC",
		"DCC", "DC", "CD", "D", "CCC", "CC", "XC", "C", "LXXX", "LXX", "LX",
		"XL", "L", "XXX", "XX", "IX", "X", "VIII", "VII", "VI", "IV", "V",
		"III", "II", "I"
};
static const int NumberEquivalents[] = { 3000, 2000, 900, 1000, 800,
		700, 600, 400, 500, 300, 200, 90, 100, 80, 70, 60,
		40, 50, 30, 20, 9, 10, 8, 7, 6, 4, 5,
		3, 2, 1
};

typedef enum calcModes {
	ADD,
	SUBTRACT
} CalculationMode;

// "Constructor"
Numeral* numeral_new()
{
	Numeral* aNumeral = (Numeral*) malloc(sizeof(Numeral));
	if (aNumeral != NULL)
	{
		memset(aNumeral->text, 0, sizeof(aNumeral->text));
		aNumeral->value = 0;
	}
	return aNumeral;
}

static int IsPointerValid(Numeral* numeralToCheck)
{
	int returnCode = EXIT_SUCCESS;
	if (NULL == numeralToCheck)
	{
		returnCode = INVALID_PTR;
	}

	return returnCode;
}
static int IsStringLenValid(Numeral* numeralToCheck)
{
	int returnCode = EXIT_SUCCESS;
	if (strlen(numeralToCheck->text) <0 )
	{
		returnCode = NON_NULL_TERM_STRING;
	}
	return returnCode;
}

static int ValidateText(Numeral* numeralToCheck)
{
	int returnCode = EXIT_SUCCESS;
	regex_t regex;

	// Convert the text to upper case; make a local copy
	int index = 0;
	char strToCheck[MAX_WIDTH] = {0};

	strncpy(strToCheck, numeralToCheck->text, MAX_WIDTH);

	while (strToCheck[index])
	{
		putchar(toupper(strToCheck[index]));
		index++;
	}

	// "construct" regex object
	returnCode = regcomp(&regex, ValidationRegEx, REG_NOSUB | REG_EXTENDED);
	if (returnCode )
	{
		returnCode = REGEX_ERROR;
	}

	if (returnCode == EXIT_SUCCESS &&
			regexec(&regex, strToCheck, 0, NULL, 0) == REG_NOMATCH)
	{
		returnCode = INVALID_TEXT;
	}

	return returnCode;
}

static int ValidateNumeral(Numeral* instance) {
	int returnCode = EXIT_SUCCESS;

	// Verify that all pointers are not null
	returnCode = IsPointerValid(instance);

	// Verify that the string length of the first and second arguments are OK
	if (returnCode == EXIT_SUCCESS )
	{
		returnCode = IsStringLenValid(instance);
	}
	// Verify that both numbers are valid Roman numerals
	if (returnCode == EXIT_SUCCESS)
	{
		returnCode = ValidateText(instance);
	}

	return returnCode;
}

int calculate(Numeral* first, Numeral* second, CalculationMode mode, int* answer) {
	// Validate the Numerals
	int returnCode = ValidateNumeral(first);
	if (returnCode == EXIT_SUCCESS) {
		returnCode = ValidateNumeral(second);
	}
	if (returnCode == EXIT_SUCCESS && answer == NULL) {
		returnCode = EXIT_FAILURE;
	}
	// Convert the Numeral to unsigned integer

	// Perform the final calculation FINALLY!
	int firstValue = first->value;
	int secondValue = second->value;
	if (mode == SUBTRACT)
	{
		secondValue = -secondValue;
	}

	(*answer) = firstValue + secondValue;

	// verify that we don't exceed the max number (3999) or go less than 0
	return returnCode;
}

NumeralReturnCode add(Numeral* first, Numeral* second, int* sum)
{
	return calculate(first, second, ADD, sum);
}

NumeralReturnCode subtract(Numeral* first, Numeral* second, int* difference)
{
	// verify that the first number is greater than the second number
	return calculate(first, second, SUBTRACT, difference);

	return 0;
}
