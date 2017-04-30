/*
 * read.c
 *
 *  Created on: 31 mars 2017
 *      Author: robin
 */
#include "read.h"

double min(double x, double y){
	if(x == 0) return y;
	return x > y ? y : x;
}

double max(double x, double y){
	return x < y ? y : x;
}

int readFile(char * filename, Element*** pIndex, int* n, int* m, int** pEmptyLines, double** pNabla, double** pDelta){

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

	double* nabla = (*pNabla) = calloc((*n)+1, sizeof(double*));
	double* delta = (*pDelta) = calloc((*n)+1, sizeof(double*));

	for(int i = 0 ; i < (*n) ; i++){
		int rowNumber, degree;
		double lastProb = 1.0;

		if(fscanf(f, "%d %d", &rowNumber, &degree) != 2){
			return -1;
		}

		if(degree == 0){
			emptyLines[rowNumber] = 1;

			//TODO Optimisation, ne pas refaire lorsqu'une ligne vide a déjà été vue
			for(int i = 0 ; i < (*n) ; i++){
				nabla[i] = min(nabla[i], ALPHA/(*n));
				delta[i] = max(delta[i], ALPHA/(*n));
			}

		}

		for(int numCouple = 0 ; numCouple < degree ; numCouple++){
			int columnNumber;
			double value;
			Element * e = calloc(1, sizeof(Element));

			if(fscanf(f, "%d %lf", &columnNumber, &value) != 2){
				return -1;
			}

			e->rowNumber = rowNumber ;

			//Insertion dans la liste
			e->son = index[columnNumber];
			index[columnNumber] = e;


			//Pour assurer la cohérence, on calcule la dernière proba
			//TODO A cause de l'arrondissement, la dernière proba est
			// souvent majorée alors qu'elle ne devrait pas l'être
			// exemple ligne 281899 de Stanford
			if(numCouple == (degree-1)){
				value = lastProb;
			} else {
				lastProb -= value;
			}
			e->value = value * ALPHA;

			// nabla[0] c'est le minimum de la colonne 0 de G
			nabla[columnNumber] = min(nabla[columnNumber], e->value);
			delta[columnNumber] = max(delta[columnNumber], e->value);

		}

		char suite = fgetc(f);
		while(suite != '\n' && suite != EOF){
			suite = fgetc(f); //Termine de lire la ligne
		}
	}
	fclose(f);
	return 0;
}

