/*
 * romanNumeral.c
 *  Purpose:
 *  		Add an subtract Roman numeral objects.
 *  Usage:
 *  		Create an instance of the Numeral type object by calling the numeral_new() function.
 *  		Assign a RomanNumeral string to the text member. Multiple objects can be added/subtracted.
 *  Synopsis:
 *  		NumeralReturnCode add(Numeral* first, Numeral* second, int* sum);
 *  			Add two objects together, the answer is written to a provided int*
 *  		NumeralReturnCode subtract(Numeral* first, Numeral* second, int* difference);
 *  			Subtract two objects from one another, the answer is written to a provided int*
 *
 *
 *
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */

#include "romanNumeral.h"
#include <regex.h>
#include <stddef.h>

#include <string.h>

// Return code strings
static const char* const retDesc[] =
{
		"Success", "Length of input string exceeds storage limit.",
		"Numeral does not contain a valid Roman Numeral.",
		"Sum is greater than maximum value.", "Difference is less than 0.",
		"Argument is null."};
// Helper method to return Error Codes
const char* getRetCodeDesc(NumeralReturnCode retCode)
{
	return retDesc[retCode];
}
// Regular expression string used to validate input string.
static char const* const ValidationRegEx =
		"^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$";
// Maximum value
const int MaximumValue = 3999;
const int IndexOffset = 1;

// Decomposed Numeral parts and their integer equivalents
// The strange order is intentional to aid in parsing.
static char const* const NumeralSymbols[] =
{ "MMM", "MM", "CM", "M", "DCCC", "DCC", "DC", "CD", "D", "CCC", "CC", "XC",
		"C", "LXXX", "LXX", "LX", "XL", "L", "XXX", "XX", "IX", "X", "VIII",
		"VII", "VI", "IV", "V", "III", "II", "I" };
static const int NumberEquivalents[] =
{ 3000, 2000, 900, 1000, 800, 700, 600, 400, 500, 300, 200, 90, 100, 80, 70, 60,
		40, 50, 30, 20, 9, 10, 8, 7, 6, 4, 5, 3, 2, 1 };
// Enum for addition and subtraction
typedef enum calcModes
{
	ADD, SUBTRACT
} CalculationMode;

// public "Constructor"
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
// private method to verify that the pointer isn't NULL
static int IsPointerValid(Numeral* numeralToCheck)
{
	int returnCode = EXIT_SUCCESS;
	if (NULL == numeralToCheck)
	{
		returnCode = INVALID_PTR;
	}

	return returnCode;
}
// private method to verify that the string copied doesn't exceed our storage limit.
static int IsStringLenValid(Numeral* numeralToCheck)
{
	int returnCode = EXIT_SUCCESS;
	int length = strlen(numeralToCheck->text);
	if (length < 0 || length > MAX_WIDTH)
	{
		returnCode = STRING_TOO_LONG;
	}
	return returnCode;
}
// private method to validate the Text portion of the Numeral type
static int ValidateText(Numeral* numeralToCheck)
{
	int returnCode = EXIT_SUCCESS;
	regex_t regex;

	// Convert the text to upper case; make a local copy
	char strToCheck[MAX_WIDTH] = { 0 };

	strncpy(strToCheck, numeralToCheck->text, MAX_WIDTH);

	// "construct" regex object
	returnCode = regcomp(&regex, ValidationRegEx, REG_NOSUB | REG_EXTENDED);

	if (returnCode == EXIT_SUCCESS
			&& regexec(&regex, strToCheck, 0, NULL, 0) == REG_NOMATCH)
	{
		returnCode = INVALID_TEXT;
	}

	return returnCode;
}
// private method to perform all validation checks on the Numeral
static int ValidateNumeral(Numeral* instance)
{
	int returnCode = EXIT_SUCCESS;

	// Verify that all pointers are not null
	returnCode = IsPointerValid(instance);

	// Verify that the string length of the first and second arguments are OK
	if (returnCode == EXIT_SUCCESS)
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
// Given a source string remove a substring from the removePostion for subStringLength chars.
// Ideally this would be static as well, however I want to be able to test this from check
// and do to other earlier validation I cannot get the code to execute through all the failure
// cases.  This is an interesting problem that's worth a philosophical discussion.
int removeSubString(char* stringToCut, size_t removePosition, size_t subStringlength)
{
	int returnCode = EXIT_SUCCESS;
	size_t length = strlen(stringToCut);

	// We can't remove anything passed the end of the string
	if (removePosition > length || removePosition < 0)
	{
		returnCode = EXIT_FAILURE;
	}
	if (returnCode == EXIT_SUCCESS)
	{
		// If we have a substring that goes passed the end of the string, shorten the substring length
		if (removePosition + subStringlength > length)
		{
			subStringlength = length - removePosition;
		}
		// Snip
		memmove(stringToCut + removePosition, // Destination; where to be copied
				stringToCut + removePosition + subStringlength, // Source; data to be copied
				IndexOffset + length - removePosition - subStringlength); // number of bytes to copy
	}
	return returnCode;
}
// private method to convert the Numeral text to value
static int convertNumeralTextValue(Numeral* theNumeral)
{
	int returnCode = EXIT_SUCCESS;
	int answer = 0;
	int index = 0;
	char localCopy[MAX_WIDTH] = { 0 };
	strncpy(&localCopy[0], theNumeral->text, MAX_WIDTH);
	// for every symbol in our array
	for (index = 0;	index < (sizeof(NumeralSymbols) / sizeof(NumeralSymbols[0])); index++)
	{
		// Look for that symbol in our Numeral Text
		char* symbol = strstr(&localCopy[0], NumeralSymbols[index]);
		// if not null, we have a match!
		if (symbol != NULL)
		{
			// Add the equivalent value to our accumulator
			answer += NumberEquivalents[index];
			// remove this symbol from the local copy
			size_t position = symbol - localCopy;
			size_t symbolLength = strlen(NumeralSymbols[index]);
			returnCode = removeSubString(&localCopy[0], position, symbolLength);
			if (returnCode != EXIT_SUCCESS)
			{
				break;
			}
		}
	}
	// Copy the final answer back to the numeral
	theNumeral->value = answer;
	return returnCode;
}
// private method common to both addition and subtraction
static int calculate(Numeral* first, Numeral* second, CalculationMode mode,
		int* answer)
{
	// Validate the Numerals
	int returnCode = ValidateNumeral(first);
	if (returnCode == EXIT_SUCCESS)
	{
		returnCode = ValidateNumeral(second);
	}
	// Make sure that the provided int pointer isn't null
	if (returnCode == EXIT_SUCCESS && answer == NULL)
	{
		returnCode = INVALID_PTR;
	}
	if (returnCode == EXIT_SUCCESS)
	{
		// Convert the numeral text to value
		if (convertNumeralTextValue(first) == EXIT_SUCCESS
				&& convertNumeralTextValue(second) == EXIT_SUCCESS)
		{
			// Perform the final calculation FINALLY!
			int firstValue = first->value;
			int secondValue = second->value;

			if (mode == SUBTRACT)
			{
				secondValue = -secondValue;
			}
			(*answer) = firstValue + secondValue;

			// verify that we don't exceed the max number (3999) or go less than 0
			if (*answer > MaximumValue  )
			{
				returnCode = VALUE_OVERFLOW;
			}
			else if(*answer < 0)
			{
				returnCode = NEGATIVE_VALUE;
			}
		}
		else
		{
			returnCode = EXIT_FAILURE;
		}
	}
	return returnCode;
}
// public method to add two Roman numerals.  The answer is provided in the sum pointer.
NumeralReturnCode add(Numeral* first, Numeral* second, int* sum)
{
	return calculate(first, second, ADD, sum);
}
// public method to subtract two Roman numerals. The answer is proved in the difference pointer.
NumeralReturnCode subtract(Numeral* first, Numeral* second, int* difference)
{
	return calculate(first, second, SUBTRACT, difference);
}
