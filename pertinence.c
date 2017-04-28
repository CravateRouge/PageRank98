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
	double epsilon = pow(10.0, -6.0);
	double normeSub;
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
		for(int i = 1 ; i <= n ; i++){
			Element* current = index[i];
			nPI[i] = 0;
			for(int j = 1 ; j <= n ; j++){
				if(current != NULL && current->rowNumber == j){
					nPI[i] += oPI[j] * current->value;
					current = current->son;
				} else if(emptyLines[j] == 1){
					nPI[i] += oPI[j] * ALPHA * 1/n;
				}
				nPI[i] += oPI[j] * (1.0 - ALPHA) * 1/n;
			}
		}

		normeSub = getNorme1Sub(nPI, oPI, n);

		Element ** tmp = oPI;
		oPI = nPI;
		nPI = tmp;

		nbIterations++;
		if(fabs(getNorme1(oPI, n)-1) > epsilon){
			printf("La somme du vecteur est différente de 1\n");
			break;
		}
	}while(normeSub > epsilon);
	printf("Résultat en %d itérations\n", nbIterations);
	//printVecteur(oPI, n);

	free(nPI);
	free(oPI);
}
