/*
 * utils.c
 *
 *  Created on: 31 mars 2017
 *      Author: robin
 */
#include "utils.h"

void freeIndex(Element *** index, int n){
	for(int i = 0 ; i < n ; i++){
		if((*index)[i] == NULL)
			continue;
		Element* currentElement = (*index)[i];
		Element* followingElement;
		while(currentElement != NULL){
			followingElement = currentElement->son;
			free(currentElement);
			currentElement = followingElement;
		}
	}

	free((*index));
}

void printliste(Element** index, int n){
	for(int i = 0 ; i < n ; i++){
		printf("i = %d : ", i);
		Element * currentElement = index[i];
		while(currentElement != NULL){
			printf("[%d, %lf]", currentElement->rowNumber, currentElement->value);
			currentElement = currentElement->son;
		}
		printf("\n");
	}
}

void printVecteur(double * tab, int n){
	FILE * f = fopen("./result.txt", "w");
	if(f == NULL){
		fprintf(stderr, "Unable to open result.txt");
		return;
	}
	double somme = 0.0;
	for(int i = 0 ; i < n ; i++){
		fprintf(f, "%d = %lf\n", i, tab[i]);
		somme += tab[i];
	}
	fprintf(f, "Somme = %lf\n", somme);

	fclose(f);
}

double getSommeVecteur(double * tab, int n){
	double somme = 0.0;
	for(int i = 0 ; i < n ; i++){
		somme += tab[i];
	}
	return somme;
}

void set_bit(uint8_t *pElements,int element_index) {
	/*Octet possédant l'info*/
	int byte_index = element_index/8;

	/*Bit d'info concerné*/
	int bit_index = element_index%8;

	uint8_t* element = pElements+(byte_index/8);

	/*Modifie le nème bit à 1*/
	*element= (*element)|(1<<bit_index);
}

bool get_bit(uint8_t *pElements, int element_index){
	/*Octet possédant l'info*/
	int byte_index = element_index/8;

	/*Bit d'info concerné*/
	int bit_index = element_index%8;

	uint8_t* element = pElements+(byte_index/8);

	return *element&(1<<bit_index);
}

void min(double* x, double y){
	if(*x > y)
		*x = y;
}

void max(double* x, double y){
	if(*x < y)
		*x = y;
}
