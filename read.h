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

int readFile(char * filename, Element*** pIndex, int* n, int* m, int** pEmptyLines, double** pXvector, double** pYvector, double** pNabla);


#endif /* READ_H_ */
