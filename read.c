/*
 * read.c
 *
 *  Created on: 31 mars 2017
 *      Author: robin
 */
#include "read.h"


int readFile(char * filename, Element*** pIndex, int* pN, uint8_t** pEmptyLines, long double** pDelta){

	/* Ouverture du fichier */
	FILE * f = fopen(filename, "r");
	if(f == NULL){
		fprintf(stderr, "Le fichier n'existe pas");
		return -1;
	}

	/* Lecture du nombre de sommets et du nombre d'arcs */
	int m;
	if(fscanf(f, "%d", pN) == 0 || fscanf(f, "%d", &m) == 0){
		return -1;
	}

	int n = (*pN);
	printf("n = %d ; m = %d \n", n, m);


	Element** index = (*pIndex) = calloc(n, sizeof(Element*));

	/*Pour n informations on alloue (n+7)/8 octets*/
	uint8_t* emptyLines = (*pEmptyLines) = calloc((n+7)/8, sizeof(*emptyLines));

	//	int * columnLength = calloc(n, sizeof(*columnLength));

	long double* delta = (*pDelta) = calloc(n, sizeof(*delta));

	bool flagImpasse = false;//Flag true si il y a au moins une ligne vide

	long double alphaDivN = ALPHA/(long double)n;
	/* Initialisation Nabla et delta (cout en N au lieu de M tests dans le min)*/
	long double precalcSurfer = (1-ALPHA)/n;

	/* Lecture des arcs */
	for(int i = 0 ; i < n ; i++){
		int rowNumber, degree;
		long double otherProb = 0;

		if(fscanf(f, "%d %d", &rowNumber, &degree) != 2){
			return -1;
		}
		rowNumber--;

		if(degree == 0){
			set_bit(emptyLines, rowNumber);
			flagImpasse = true;
		}

		for(int numCouple = 0 ; numCouple < degree ; numCouple++){
			int columnNumber;
			long double value;
			Element * e = malloc(sizeof(Element));

			if(fscanf(f, "%d %Lf", &columnNumber, &value) != 2){
				return -1;
			}
			columnNumber--;

			e->rowNumber = rowNumber ;

			//Insertion dans la liste
			e->son = index[columnNumber];
			index[columnNumber] = e;

			//			columnLength[columnNumber]++;


			//Pour assurer la cohérence, on calcule la dernière proba
			//TODO A cause de l'arrondissement, la dernière proba est
			// souvent majorée alors qu'elle ne devrait pas l'être
			// exemple ligne 281899 de Stanford
//			if(numCouple == (degree-1)){
//				value = 1-otherProb;
//			} else {
//				otherProb += value;
//			}

			value = value * ALPHA;
			e->value = value;

			//			if(!is_impasse){
			//				// nabla[0] c'est le minimum de la colonne 0 de G
			//				min(nabla+columnNumber, value + precalcSurfer);
			//			}

			max(delta+columnNumber, value + precalcSurfer);

		}

		char suite = fgetc(f);
		while(suite != '\n' && suite != EOF){
			suite = fgetc(f); //Termine de lire la ligne
		}
	}
	fclose(f);

	if(flagImpasse){
		long double precalc = alphaDivN + precalcSurfer;
		for(int k = 0; k < n ; k++)
			max(delta+k,precalc);
	}

	//	/* Gestion des potentiels 0 dans les colonnes, qui ne seraient pas compris dans des lignes vides */
	//	for(int k = 0 ; k < n ; k++)
	//		if(columnLength[k] != n)
	//			nabla[k] = precalcSurfer;



	//	free(columnLength);
	return 0;
}

