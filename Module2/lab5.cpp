/*
Выполнил: Нейман К. А.
Группа: АПО-12
5_1. Первые k элементов длинной последовательности.
Дана очень длинная последовательность целых чисел длины n. Требуется вывести в отсортированном виде её первые k элементов. Последовательность может не помещаться в память. Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.

In
9 4
3 7 4 5 6 1 15 4 2
Out
1 2 3 4
*/

#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

//Слияние
int* Merge(int *mas1, int *mas2, int s1, int s2, int SizeResult=0)
{
	SizeResult = SizeResult == 0? s1 + s2: SizeResult;	
	int *mas = new int[ SizeResult ];
	int n = 0;
	while (s1 && s2 && n < SizeResult) 
	{
		if (*mas1 < *mas2) 
		{
			mas[n] = *mas1;
			mas1++;
			--s1;
		} 
		else 
		{
			mas[n] = *mas2;
			++mas2;
			--s2;
		}
		++n;
	}
	if (s1 == 0)
	{
		for (int i = 0; i < s2 && n < SizeResult; ++i) 
		{
			mas[n++] = *mas2++;
		}
	} 
	else 
	{
		for (int i = 0; i < s1 && n < SizeResult; ++i) 
		{
			mas[n++] = *mas1++;
		}
	}
	return mas;
}

//Сортировка слиянием
void Sort(int* Buffer, int Size)
{
	int n = 1, l, ost;
	int* mas;
	while (n < Size) 
	{
		l = 0;
		while (l < Size) 
		{
			if (l + n >= Size) break;
			ost = (l + n * 2 > Size) ? (Size - (l + n)) : n;
			mas = Merge(Buffer + l, Buffer + l + n, n, ost);
			for (int i = 0; i < n + ost; ++i)
				Buffer[l+i] = mas[i];
			delete[] mas;
			l += n * 2;
		}
		n *= 2;
	}
}

//Поиск первых `Portion` элементов в отсортированном массиве
void GetFirstSortedNumber(int* Result, int* Mas, int Portion, int Number)
{
	int i = Portion, x;
	for( i = 0; i < Portion; ++i)
	{
		if (scanf("%d", &x) == 0)
			break;
		Result[i] = x;
	}
	Sort(Result, Portion);
	int j = Portion;
	int* temp;
	while ( j < Number )
	{
		for( i = 0; i < Portion && j < Number; ++i, ++j)
		{
			scanf("%d", &x);
			Mas[i] = x;
		}
		Sort(Mas, i);
		temp=Merge(Result, Mas, Portion, i, Portion);
		for (int z = 0; z < Portion; ++z)
			Result[z] = temp[z];
		delete[] temp;
	}
}

int main()
{
	int Number = 0, Portion = 0;
	if( scanf("%d %d\n", &Number, &Portion) != 2 )
		return 0;
	assert( Portion > 0 );
	assert( Number >= Portion );
	int* Result = new int [Portion];
	int* Mas = new int [Portion];
	GetFirstSortedNumber(Result, Mas, Portion, Number);
	for ( int i = 0; i < Portion; ++i)
	{
		printf("%d ", Result[i]);
	}
	printf("\n");
	delete[] Mas;
	delete[] Result;
	return 0;
}
