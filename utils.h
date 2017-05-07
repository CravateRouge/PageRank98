/*
 * utils.h
 *
 *  Created on: 31 mars 2017
 *      Author: robin
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

void freeIndex(Element *** index, int n);
void printliste(Element** index, int n);

void printVecteur(long double * tab, int n);
long double getSommeVecteur(long double * tab, int n);

void set_bit(uint8_t *pElements,int element_index);
bool get_bit(uint8_t *pElements, int element_index);

void min(long double* x, long double y);
void max(long double* x, long double y);

#endif /* UTILS_H_ */
