/*
 * pertinence.c
 *
 *  Created on: 6 avr. 2017
 *      Author: robin
 */
#include "pertinence.h"

double getNorme1(double * nPI, int n){
	double norme = 0;

	for(int i = 1 ; i <= n ; i++){
		norme += nPI[i];
	}
	return norme;
}

double getNorme1Sub(double * nPI, double * oPI, int n){
	double norme = 0;

	for(int i = 1 ; i <= n ; i++){
		norme += fabs(nPI[i] - oPI[i]);
	}
	return norme;
}

void makeGoogleMatrix(Element** index, int n){
	for(int i = 1 ; i <= n ; i++){
		Element* current = index[i];
		while(current != NULL){
			current->value = current->value*ALPHA;
			current = current->son;
		}
	}
}

void calculPertinence(Element** index, int* emptyLines, int n){
	//La case index[0] n'est jamais utilisée !

	double normeSub;
	double alphaDivN = ALPHA/n;
	double precalcSurfer = (1-ALPHA)/n;
	int nbIterations = 0;


	makeGoogleMatrix(index, n);
	double * oPI = malloc((n+1) * sizeof(double));
	double * nPI = malloc((n+1) * sizeof(double));

	//Initialisation
	for(int i = 1 ; i <= n ; i++){
		oPI[i] = (1.0)/n;
	}

	// Itération
	do{
		//Multiplication
		for(int i = 1 ; i <= n ; i++){
			Element* current = index[i];
			nPI[i] = 0;
			while(current != NULL){
				nPI[i] += oPI[current->rowNumber] * current->value;
				current = current->son;
			}
		}

		// Saut lors d'une impasse
		double impasse = 0.0;
		for(int i = 1 ; i <= n ; i++){
			if(emptyLines[i] == 1){
				impasse += oPI[i];
			}
		}
		impasse *= alphaDivN;
		for(int i = 1 ; i <= n ; i++){
			nPI[i] += impasse + precalcSurfer;//Impasses + RandomSurfer
		}


		normeSub = getNorme1Sub(nPI, oPI, n);

		Element ** tmp = oPI;
		oPI = nPI;
		nPI = tmp;

		nbIterations++;

		//Inutile sachant que le norme est forcée à 1,
		//n'oublions pas que nous sommes optimistes
//		if(fabs(getNorme1(oPI, n)-1) > epsilon){
//			printf("La somme du vecteur est différente de 1\n");
//			break;
//		}

	}while(normeSub > 0.000001);

	printf("Résultat en %d itérations\n", nbIterations);
	//printVecteur(oPI, n);

	free(nPI);
	free(oPI);
}
