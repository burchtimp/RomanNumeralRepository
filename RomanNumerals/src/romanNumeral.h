/*
 * romanNumeral.h
 *
 *  Created on: Aug 6, 2016
 *      Author: tburch
 */

#ifndef ROMANNUMERAL_H_
#define ROMANNUMERAL_H_

#define MAX_WIDTH  50

// base structure for
// all parts of the Numeral
// with number equivalents
typedef struct {
	char text[MAX_WIDTH];
	unsigned value;
} Numeral;

Numeral* numeral_new();



#endif /* ROMANNUMERAL_H_ */
