/*
 * BlossumMatrix.cpp
 *
 *  Created on: 29.10.2015
 *      Author: ugin
 */

#include "BlossumMatrix.h"





BlossumMatrix::BlossumMatrix(istream &stream) {
	int i,j;
	int n;//размерность матрицы
	stream >> n;
	map<char,int> * charToInt = new map<char,int>();
	char sym;
	for (i=0; i<n; i++) {
		stream >> sym;
		charToInt->insert(pair<char,int>(sym,i));
		//cout << (*charToInt)[sym] << "\n";
	}
	int **matrix = new int*[n];
	int cur;
	for (i=0; i<n; i++) {
		matrix[i] = new int[n];
		for (j=0; j<n; j++) {
			stream >> cur;
			matrix[i][j] = cur;
		}
	}

	this->charToInt = charToInt;
	this->matrix = matrix;
	this->n = n;
}



int BlossumMatrix::getValue(char sym1, char sym2) {
	return matrix[charToInt->at(sym1)][charToInt->at(sym2)];
}

BlossumMatrix::~BlossumMatrix() {
	delete charToInt;
	for (int i=0; i<n; i++) {
		delete[] matrix[i];
	}
	delete[] matrix;
}
