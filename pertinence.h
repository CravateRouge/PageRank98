/*
 * pertinence.h
 *
 *  Created on: 6 avr. 2017
 *      Author: robin
 */

#ifndef PERTINENCE_H_
#define PERTINENCE_H_
#include <math.h>
#include "structures.h"
#include "utils.h"

#define ALPHA 0.85

void calculPertinence(Element** index, int* emptyLines, int n);

#endif /* PERTINENCE_H_ */
