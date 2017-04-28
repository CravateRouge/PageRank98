#include <stdio.h>
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

	int n, m;
	//index est de taille n+1, index[0] n'est pas utilisé
	Element** index = 0;
	int* emptyLines = 0;

	if(readFile(argv[1], &index, &n, &m, &emptyLines) == -1){
		fprintf(stderr, "Fichier non conforme\n");
		return -1;
	}

	//printliste(index, n);

	calculPertinence(index, emptyLines, n);
	freeIndex(&index, n);
	free(emptyLines);
	return 0;
}
