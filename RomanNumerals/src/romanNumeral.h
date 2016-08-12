/*
 * romanNumeral.h
 *
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */

#ifndef ROMANNUMERAL_H_
#define ROMANNUMERAL_H_

#define MAX_WIDTH  50
#define ERR_WIDTH  25
#define NUM_ERRORS 4


extern const int MaximumValue;




// Type for all parts of the Numeral
// with unsigned integer equivalents
typedef struct {
	char text[MAX_WIDTH];
	unsigned value;
} Numeral;

// Errors
typedef enum returnCodes {
	NON_NULL_TERM_STRING = -1,
	INVALID_TEXT = -2,
	VALUE_OVERFLOW = -3,
	NEGATIVE_VALUE = -4,
	INVALID_PTR = -5,
	REGEX_ERROR = -6
} NumeralReturnCode;

const char* getRetCodeDesc(NumeralReturnCode retCode);

// Constructor
Numeral* numeral_new();

NumeralReturnCode add(Numeral* first, Numeral* second, int* sum);
NumeralReturnCode subtract(Numeral* first, Numeral* second, int* difference);


#endif /* ROMANNUMERAL_H_ */
