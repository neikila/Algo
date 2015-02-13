/*
Выполнил: Нейман К. А.
Группа: АПО-12

6_3. Binary MSD для long long.
Дан массив неотрицательных целых 64-разрядных чисел. Количество чисел не больше 106. Отсортировать массив методом MSD по битам (бинарный QuickSort).
In
3
4 1000000 7
Out
4 7 1000000
*/

#include <iostream>
#include "assert.h"
#include <stdio.h>
#include <stdint.h>

#define BITSWORD 63

//Проверка наличия единицы в раряде под номером индекс
inline bool digit(unsigned long long Num, int Index)
{
	return Num & ((unsigned long long int)1 << Index);
}

void Swap(unsigned long long *a, unsigned long long *b)
{
	unsigned long long temp = *a;
	*a = *b;
	*b = temp;
}

//Бинарная сортировка по старшему биту
void quicksortB(unsigned long long *a, int first, int last, int w)
{
	int i = first;
	int j = last;
	if (last <= first || w < 0)
		return;
	while(j != i)
	{
		while ( !digit(a[i], w) && (i < j) )
			++i;
		while ( digit(a[j], w) && (j > i) )
			--j;
		Swap(&(a[i]), &(a[j]));
	}
	if ( !digit(a[last], w) )
		++j;
	quicksortB(a, first, j - 1, w - 1);
	quicksortB(a, j, last, w - 1);
}

int main()
{
	int Size;
	std::cin >> Size;
	assert(Size > 0);
	unsigned long long *Num = new unsigned long long [Size];
	for (int i = 0; i < Size; ++i)
	{
		std::cin >> Num[i];
	}
	quicksortB(Num, 0, Size - 1, BITSWORD);
	for (int i = 0; i < Size; ++i)
	{
		std::cout << Num[i] << std::endl;
	}
	delete[] Num;
}
