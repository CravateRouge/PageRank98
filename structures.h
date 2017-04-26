/*
 * structures.h
 *
 *  Created on: 31 mars 2017
 *      Author: robin
 */

#ifndef STRUCTURES_H_
#define STRUCTURES_H_

typedef struct Element{
	double value;
	int rowNumber;
	int columnNumber;
	struct Element * son;
} Element;

#endif /* STRUCTURES_H_ */
