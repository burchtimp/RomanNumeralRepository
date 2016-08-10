/*
 * romanNumeral.c
 *
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */
#include "romanNumeral.h"
#include <stdlib.h>
#include <string.h>

// Return code strings
static const char* retDesc[] =
{
		"Success",
		"Could not determine length of input string.",
		"Numeral does not contain a valid Roman Numeral.",
		"Roman numeral specified is greater than 3999.",
		"Difference is less than 0."
		"Numeral is null."
};

const char* getRetCodeDesc(NumeralReturnCode retCode)
{
	return retDesc[retCode];
}

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
		returnCode = EXIT_FAILURE;
	}

	return returnCode;
}
static int IsStringLenValid(Numeral* numeralToCheck)
{
	int returnCode = EXIT_SUCCESS;
	if (strlen(numeralToCheck->text) <=0 )
	{
		returnCode = EXIT_FAILURE;
	}
	return returnCode;
}

//static int ValidateText(Numeral* numeralToCheck)
//{
//
//	return 0;
//}

NumeralReturnCode add(Numeral* first, Numeral* second, Numeral* answer)
{
	int returnCode = EXIT_SUCCESS;
	// Validation
	{
		// Verify that all pointers are not null
		if (!(IsPointerValid(first) &&
				IsPointerValid(second) &&
				IsPointerValid(answer)))
		{
			returnCode = INVALID_NUMERAL_PTR;
		}

		// Verify that the string length of the first and second arguments are OK
		if (returnCode == EXIT_SUCCESS &&
				!(IsStringLenValid(first) && IsStringLenValid(second)))
		{
			returnCode = INVALID_NUMERAL_PTR;
		}

		// verify that both numbers are valid Roman numerals

	}
	// Convert the Numeral to unsigned integer

	// verify that we don't exceed the max number (3999)
	return returnCode;
}

 NumeralReturnCode subtract(Numeral* first, Numeral* second, Numeral* difference)
{
	// verify that the first number is greater than the second number


	return 0;
}
