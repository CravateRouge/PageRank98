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

void calculPertinence(Element** index, uint8_t* emptyLines, long double* Y, int n, double precision){

	long double normeSub;
	long double alphaDivN = ALPHA/n;
	long double impasseX = 0, impasseY = 0;
	long double precalcSurfer = (1-ALPHA)/n;
	int nbIterations = 1;

	long double* X = malloc(n * sizeof(long double));

	/* Première itération */
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

	/* Itérations suivantes */
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

		nbIterations++;

	}while(normeSub > precision);

	printf("Résultat en %d itérations, normeX = %6.9Lf, normeY = %6.9Lf, normeSub = %6.9Lf\n", nbIterations, getNorme1(X, n), getNorme1(Y, n), normeSub);
	//printVecteur(X, n);

	free(X);
	free(Y);
}
