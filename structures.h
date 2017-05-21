#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <stdint.h>

typedef struct Element{
	long double value;
	int rowNumber;
	struct Element * son;
} Element;

#define ALPHA 0.85

#endif /* STRUCTURES_H_ */
