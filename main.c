#include <stdio.h>
#include <stdlib.h>
#include "read.h"
#include "structures.h"
#include "utils.h"
#include "pertinence.h"

int main(int argc, char* argv[]){
	if(argc-1 != 1)
	{
		fprintf(stderr, "USAGE : %s nomfichier\n", argv[0]);
		return 1;
	}

	int n;

	Element** index = NULL;
	uint8_t* emptyLines = NULL;
	double* nabla = NULL;
	double* delta = NULL;

	if(readFile(argv[1], &index, &n, &emptyLines, &nabla, &delta) == -1){
		fprintf(stderr, "Fichier non conforme\n");
		freeIndex(&index, n);
		free(emptyLines);
		return 1;
	}

	//printliste(index, n);

	printf("Début de l'algorithme\n");
	calculPertinence(index, emptyLines, nabla, delta, n);

	freeIndex(&index, n);
	free(nabla);
	free(delta);
	free(emptyLines);
	return 0;
}
