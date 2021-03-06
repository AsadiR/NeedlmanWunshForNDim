/*
 * MultiDimensionalArray.h
 *
 *  Created on: 29.10.2015
 *      Author: ugin
 */


#ifndef MULTIDIMENSIONALARRAY_H_
#define MULTIDIMENSIONALARRAY_H_
#include <cmath>
#include "BlossumMatrix.h"
#include <string>
#include <limits.h>

class Cube {
public:
	Cube(string *sequences, int n, BlossumMatrix *matrix);
	virtual ~Cube();
	//возвращает максимальный score для глобального выравнивания
	int getMaxScore();
	//возвращает массив с выравненными последовательностями
	//ответственость за освобождение памяти ложится на вызывающую функцию
	string* doAlign();

private:
	int *array; //массив всех элементов
	int n;//количество последовательностей
	int *cur_coords;//координаты текущего положения
	int cur_pos;// текущая обощеная координата
	int size;// размер масива array
	BlossumMatrix* matrix;
	string *sequences;
	//служебная функция
	void specInc(int *k, int shifths[]);

	//возвращает предшествующий элемент заданный массивом сдвигов
	int getPrec(int shifts[]);

	int sliceSize(int index);

	// возвращает максимальный из значение Score при шаге из предшествующих элементов
	int getMaxValue();

	// возвращает Score элемента с индексом cur_pos при переходе в него из элемента
	// c индексом prec
	int getScore(int prec, int shift[]);

	void inc();
};



#endif /* MULTIDIMENSIONALARRAY_H_ */
