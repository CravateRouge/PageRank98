/*
 * pertinence.c
 *
 *  Created on: 6 avr. 2017
 *      Author: robin
 */
#include "pertinence.h"

double getNorme1(double * nPI, int n){
	double norme = 0;

	for(int i = 0 ; i <n ; i++){
		norme += nPI[i];
	}
	return norme;
}

double getNorme1Sub(double * nPI, double * oPI, int n){
	double norme = 0;

	for(int i = 0 ; i < n ; i++){
		norme += fabs(nPI[i] - oPI[i]);
	}
	return norme;
}

void calculPertinence(Element** index, uint8_t* emptyLines, int n){

	double normeSub;
	double alphaDivN = ALPHA/(double)n;
	double precalcSurfer = (1-ALPHA)/(double)n;
	int nbIterations = 0;

	double * oPI = malloc((n) * sizeof(double));
	double * nPI = malloc((n) * sizeof(double));

	// Saut lors d'une impasse
	double impasse = 0;
	for(int i = 0 ; i < n ; i++){
		if(get_bit(emptyLines, i))
			impasse += 1;
	}

	//Initialisation
	for(int i = 0 ; i < n ; i++){
		Element* current = index[i];
		nPI[i] = 0;

		while(current != NULL){
			nPI[i] += current->value;
			current = current->son;
		}

		nPI[i] = nPI[i]/n + impasse*alphaDivN/n + precalcSurfer;
	}
	//Est-ce vraiment la peine de faire la norme à la première itération?

	// Itération
	do{

		double* tmp = oPI;
		oPI = nPI;
		nPI = tmp;

		// Saut lors d'une impasse devient un scalaire
		impasse = 0;
		for(int i = 0 ; i < n ; i++){
			if(get_bit(emptyLines, i))
				impasse += oPI[i];
		}

		//Multiplication
		for(int i = 0 ; i < n ; i++){
			Element* current = index[i];
			nPI[i] = 0;

			while(current != NULL){
				nPI[i] += current->value * oPI[current->rowNumber];
				current = current->son;
			}

			nPI[i] = nPI[i] + impasse*alphaDivN + precalcSurfer;
		}


		normeSub = getNorme1Sub(nPI, oPI, n);

		nbIterations++;

		//Inutile sachant que le norme est forcée à 1,
		//n'oublions pas que nous sommes optimistes
//		if(fabs(getNorme1(oPI, n)-1) > epsilon){
//			printf("La somme du vecteur est différente de 1\n");
//			break;
//		}

	}while(normeSub > 0.000001);

	printf("Résultat en %d itérations\n", nbIterations);
	printVecteur(nPI, n);

	free(nPI);
	free(oPI);
}
