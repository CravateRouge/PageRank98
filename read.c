/*
 * read.c
 *
 *  Created on: 31 mars 2017
 *      Author: robin
 */
#include "read.h"

int readFile(char * filename, Element*** pIndex, int* n, int* m, int** pEmptyLines){

	FILE * f = fopen(filename, "r");
	if(f == NULL){
		fprintf(stderr, "Le fichier n'existe pas");
		return -1;
	}

	if(fscanf(f, "%d", n) == 0 || fscanf(f, "%d", m) == 0){
		return -1;
	}

	printf("n = %d ; m = %d \n", *n, *m);

	//La case index[0] n'est jamais utilisée, les indices vont de 1 à n
	Element** index = (*pIndex) = calloc((*n)+1, sizeof(Element*));

	int* emptyLines = (*pEmptyLines) = calloc((*n)+1, sizeof(int*));

	for(int i = 0 ; i < (*n) ; i++){//Dans explication du prof : j = rowNumber et i = columnNumber
		int rowNumber, degree;
		double lastProb = 1.0;
		if(fscanf(f, "%d %d", &rowNumber, &degree) != 2){
			return -1;
		}

		if(degree == 0){
			emptyLines[rowNumber] = 1;
		}

		for(int numCouple = 0 ; numCouple < degree ; numCouple++){
			Element * e = calloc(1, sizeof(Element));

			if(fscanf(f, "%d %lf", &(e->columnNumber), &(e->value)) != 2){
				return -1;
			}

			e->rowNumber = rowNumber ;

			e->son = index[e->columnNumber];
			index[e->columnNumber] = e;

			//Pour assurer la cohérence, on calcule la dernière proba
			if(numCouple == (degree-1)){
				e->value = lastProb;
			} else {
				lastProb -= e->value;
			}
		}


		while(fgetc(f) != '\n' && fgetc(f) != EOF);//Termine de lire la ligne
	}
	fclose(f);
	return 0;
}

