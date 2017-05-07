/*
 * pertinence.c
 *
 *  Created on: 6 avr. 2017
 *      Author: robin
 */
#include "pertinence.h"

long double getNorme1(long double * nPI, int n){
	long double norme = 0;

	for(int i = 0 ; i < n ; i++){
		norme += nPI[i];
	}
	return norme;
}

long double getNorme1Sub(long double * nPI, long double * oPI, int n){
	long double norme = 0;

	for(int i = 0 ; i < n ; i++){
		norme += fabs(nPI[i] - oPI[i]);
	}
	return norme;
}

void calculPertinence(Element** index, uint8_t* emptyLines, long double* Y, int n){

	long double normeSub;
	long double alphaDivN = ALPHA/n;
	long double impasseX = 0, impasseY = 0;
	long double precalcSurfer = (1-ALPHA)/n;
	int nbIterations = 1;

	long double* X = malloc(n * sizeof(long double));

	for(int i = 0 ; i < n ; i++){
		if(get_bit(emptyLines, i)){
			impasseX += precalcSurfer;
			impasseY += Y[i];
		}
	}

	for(int i = 0 ; i < n ; i++){
		Element* current = index[i];
		long double newXi = 0;
		long double newYi = 0;

		while(current != NULL){
			newXi += precalcSurfer * current->value;
			newYi += Y[current->rowNumber] * current->value;
			current = current->son;
		}

		newXi += impasseX * alphaDivN + precalcSurfer;
		newYi += impasseY * alphaDivN + precalcSurfer;

		/*
		 * Le max entre precalcSurfer et newXi est forcément newXi
		 * car newXi contient precalcSurfer plus un nombre > 0
		 * dû aux caractéristiques de la matrice
		 */
		X[i] = newXi;
		min(Y+i, newYi);
	}

	do{

		// Saut lors d'une impasse, devient un scalaire
		impasseX = 0;
		impasseY = 0;
		for(int i = 0 ; i < n ; i++){
			if(get_bit(emptyLines, i)){
				impasseX += X[i];
				impasseY += Y[i];
			}
		}

		for(int i = 0 ; i < n ; i++){
			Element* current = index[i];
			long double newXi = 0;
			long double newYi = 0;

			while(current != NULL){
				newXi += X[current->rowNumber] * current->value;
				newYi += Y[current->rowNumber] * current->value;
				current = current->son;
			}

			/*
			 * Sachant que Pour la matrice G, nabla[i]=precalcSurfer
			 * alors norm*precalcSurfer+nabla[i](1-norm)
			 * =precalcSurfer(norm+1-norm)=precalcSurfer
			 */
			newXi += impasseX * alphaDivN + precalcSurfer;
			newYi += impasseY * alphaDivN + precalcSurfer;

			max(X+i, newXi);
			min(Y+i, newYi);
		}


		normeSub = getNorme1Sub(X, Y, n);

		if(nbIterations % 10 == 0)
			printf("ite %d, normeX %6.9Lf, normeY %6.9Lf, normeSub %6.9Lf\n",nbIterations,getNorme1(X, n),getNorme1(Y, n),normeSub);
		nbIterations++;

	}while(normeSub > 1e-9);

	printf("ite %d, normeX %6.9Lf, normeY %6.9Lf, normeSub %6.9Lf\n",nbIterations,getNorme1(X, n),getNorme1(Y, n),normeSub);
	//printVecteur(X, n);
	free(X);
	free(Y);
}


void calculPertinenceOld(Element** index, uint8_t* emptyLines, int n){

	printBoolVecteur(emptyLines, n);
	long double normeSub;
	long double alphaDivN = ALPHA/(long double)n;
	long double precalcSurfer = (1-ALPHA)/(long double)n;
	int nbIterations = 1;

	long double * oPI = malloc((n) * sizeof(long double));
	long double * nPI = malloc((n) * sizeof(long double));

	// Saut lors d'une impasse
	long double impasse = 0;
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

		long double* tmp = oPI;
		oPI = nPI;
		nPI = tmp;

		// Saut lors d'une impasse, devient un scalaire
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

	}while(normeSub > 1e-9);

	printf("Résultat en %d itérations\n", nbIterations);
	printVecteur(nPI, n);

	free(nPI);
	free(oPI);
}
