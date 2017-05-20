#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "structures.h"
#include "utils.h"
#include "pertinence.h"

int main(int argc, char* argv[]){
	if(argc-1 != 2)
	{
		fprintf(stderr, "USAGE : %s nomfichier précision\n", argv[0]);
		return 1;
	}

	int n;

	Element** index = NULL;
	uint8_t* emptyLines = NULL;
	long double* delta = NULL;

	if(readFile(argv[1], &index, &n, &emptyLines, &delta) == -1){
		fprintf(stderr, "Fichier non conforme\n");
		freeIndex(&index, n);
		free(emptyLines);
		return 1;
	}


	printf("Début de l'algorithme\n");

	double precision = 0;
	sscanf(argv[2], "%lf", &precision);
	calculPertinence(index, emptyLines, delta, n, precision);

	freeIndex(&index, n);
	free(emptyLines);
	return 0;
}
