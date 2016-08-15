/*
 * romanNumeral.h
 *
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */

#ifndef ROMANNUMERAL_H_
#define ROMANNUMERAL_H_

#include <stdlib.h>
#define MAX_WIDTH  15 // based on the longest possible value: MMMDCCCLXXXVIII
#define ERR_WIDTH  25

extern const int MaximumValue;
// Type for all parts of the Numeral
// with unsigned integer equivalents
typedef struct {
	char text[MAX_WIDTH];
	unsigned value;
} Numeral;

// Errors
typedef enum returnCodes {
	STRING_TOO_LONG = 1,
	INVALID_TEXT = 2,
	VALUE_OVERFLOW = 3,
	NEGATIVE_VALUE = 4,
	INVALID_PTR = 5
} NumeralReturnCode;

const char* getRetCodeDesc(NumeralReturnCode retCode);

// "Constructor"
Numeral* numeral_new();
// "public" functions
int removeSubString(char* stringToCut, size_t removePosition, size_t subStringlength);
NumeralReturnCode add(Numeral* first, Numeral* second, int* sum);
NumeralReturnCode subtract(Numeral* first, Numeral* second, int* difference);


#endif /* ROMANNUMERAL_H_ */
