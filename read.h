/*
 * read.h
 *
 *  Created on: 31 mars 2017
 *      Author: robin
 */

#ifndef READ_H_
#define READ_H_

#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
#include "utils.h"

int readFile(char * filename, Element*** pIndex, int* pN, uint8_t** pEmptyLines, long double** pDelta);


#endif /* READ_H_ */
