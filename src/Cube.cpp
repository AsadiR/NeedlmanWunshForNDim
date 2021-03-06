/*
 * MultiDimensionalArray.cpp
 *
 *  Created on: 29.10.2015
 *      Author: ugin
 */

#include "Cube.h"

Cube::Cube(string *sequences, int n, BlossumMatrix *matrix) {
	int size = sequences[0].length()+1;
	this->n = n;
	this->matrix = matrix;
	this->sequences = sequences;
	int i;

	for (i=1; i<n; i++) {
		size *= sequences[i].length()+1;
	}
	cout << "for hyper cube allocated: " << size*sizeof(int) << " bytes\n";
	this->array = new int[size];
	this->size = size;
	cur_pos = 0;
	this->cur_coords = new int[n];
	for (i=0; i<n; i++) cur_coords[i] = 0;

	while (cur_pos<size) {
		array[cur_pos] = getMaxValue();
		//cout << "arrayElem:" << array[cur_pos] << "\n";
		inc();
	}
}

string* Cube::doAlign() {
	//обратный ход по вычисленной матрице
	int i,k;
	k = pow(2,n)-1;
	cur_pos--;
	string *res = new string[n];
	//массив, поразрядно представляющий двоичное число
	int shifts[n];

	for (i=0;i<n;i++)
		cur_coords[i] = sequences[i].length();

	while (cur_pos!=0) {
		for (i=0; i<n; i++) shifts[i] = 0;
		shifts[0] = 1;//получаем двоичную запись числа 1, Little Endian
		//перебираем все прецессоры
		for (i=1; i<=k; specInc(&i,shifts)) {
			int prec = getPrec(shifts);
			if (prec == -1) continue;
			int newValue = getScore(prec, shifts);
			//в случае если найден обратный путь
			if (array[cur_pos]==newValue) {
				cur_pos = prec;
				for (i=0; i<n; i++){
					if (shifts[i]==0)
						res[i] = "-" + res[i];
					else {
						res[i] = sequences[i][cur_coords[i]-1] + res[i];
						cur_coords[i] -= shifts[i];
					}
				}
				break;
			}
		}
	}
	return res;
}

int Cube::getMaxScore() {
	return array[size-1];
}

void Cube::inc() {
	int i;
	cur_pos++;
	cur_coords[0]++;
	for (i=0; i<n; i++) {
		if ( cur_coords[i] == (int)sequences[i].length()+1 ) {
			cur_coords[i] = 0;
			if (i+1<n) cur_coords[i+1]++;
		} else break;
	}
}

int Cube::getMaxValue() {
	/*
	Всего k=2^n-1 способов выбрать предыдущий элемент.
	Каждый из таких способов кодируется двоичным числом shift
	В нем 0 обозначает отсутствие сдвига вдоль i-oй координаты
	1 обозначает наличие сдвига относительно
	  */
	if (cur_pos==0) return 0;
	int i;
	int k = pow(2,n)-1;
	//массив, поразрядно представляющий двоичное число
	int shifts[n];
	for (i=0; i<n; i++) shifts[i] = 0;
	shifts[0] = 1;//получаем двоичную запись числа 1, Little Endian
	int max = INT_MIN;

	for (i=1; i<=k; specInc(&i,shifts)) {
		int prec = getPrec(shifts);
		if (prec == -1) continue;
		int newValue = getScore(prec, shifts);
		max = ( newValue>max ? newValue : max );
	}
	return max;
}

int Cube::getPrec(int shifts[]) {
	int i;
	int prec = 0;
	for (i=0; i<n; i++) {
		int slice = sliceSize(i);
		int coord = cur_coords[i] - shifts[i];

		if (coord < 0)
			return -1;//таких элементов не существует

		prec += slice*coord;
	}
	return prec;
}

void Cube::specInc(int *index, int shifts[]) {
	(*index)++;
	shifts[0]++;
	for (int i=0; i<n; i++) {
		if (shifts[i] == 2) {
			shifts[i] = 0;
			if (i+1<n) shifts[i+1]++;
		} else break;
	}
}

int Cube::getScore(int prec, int shifts[]) {
	int i,k;
	int score = array[prec];
	char cur;
	char next;
	//цикл по всем сочитаниям из n по 2
	for (k=0; k<n-1; k++) {
		for (i=k+1; i<n; i++) {
			cur = ( shifts[k]==0 ? '-' : sequences[k][cur_coords[k]-1] );
			next = ( shifts[i]==0 ? '-' : sequences[i][cur_coords[i]-1] );
			score += matrix->getValue(cur, next);
		}
	}
	return score;
}


Cube::~Cube() {
	delete[] array;
	delete[] cur_coords;
}

int Cube::sliceSize(int index) {
	//можно вычеслить один раз а потом использовать
	int size = 1;
	for (int i=1; i<=index; i++) {
		size *= sequences[i-1].length()+1;
	}
	return size;
}


