/*
 * utils.h
 *
 *  Created on: 31 mars 2017
 *      Author: robin
 */

#ifndef UTILS_H_
#define UTILS_H_
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"
void freeIndex(Element *** index, int n);
void printliste(Element** index, int n);

void printVecteur(double * tab, int n);
double getSommeVecteur(double * tab, int n);

#endif /* UTILS_H_ */
