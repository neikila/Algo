/*
Выполнил: Нейман К. А.
Группа: АПО-12
4_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int stop = 0;

//Разбиение на две части
inline int Partition(int arr[], int First, int Last)
{
	int Index = rand() % ( Last - First + 1 ) + First;
	int pivot = arr[Index];
	std::swap(arr[Index], arr[Last]);
	int i = First;
	int j = First;
	while( i <= Last && arr[i] <= pivot )
		i++;
	if ( i >= Last )
		return Last;
	j = i + 1;
	while ( j < Last )
	{
		while( arr[j] > pivot )
		{
			j++;
		}
		if ( j < Last )
		{
			std::swap(arr[i++], arr[j++]);
		}
	}
	std::swap(arr[i], arr[Last]);
	return i;
}


void QSort(int arr[], int First, int Last) 
{
	int pivotpos;
	int Mas[(int)(Last - First + 1)][2];
	int Count = 0, Index = -1;
	Mas[Count][0] = First;
	Mas[Count][1] = Last;
	++Count;
	while(++Index < Count)
	{
		pivotpos = Partition(arr, Mas[Index][0], Mas[Index][1]);
		if (Mas[Index][0] < pivotpos - 1)
		{
			Mas[Count][0] = Mas[Index][0];
			Mas[Count][1] = pivotpos - 1;
			++Count;
		}
		if (Mas[Index][1] > pivotpos + 1)
		{
			Mas[Count][0] = pivotpos + 1;
			Mas[Count][1] = Mas[Index][1];
			++Count;
		}
	}
	return;
}

inline int read_int()
{
	static char c;
	static int res;
	while ( (c = getchar()) == ' ' );
	res = c - '0';
	while ( (c = getchar()) >= '0' && c <= '9')
	{
		res = res * 10 + (c - '0');
	}
	if (c == EOF)
		stop = 1;
	return res;
}

int main() 
{
	int Size = 100;
	int* arr = new int[Size];
	int i = 0;
	do
	{
		if ( i != Size )
		{			
		}
		else
		{
			Size *= 2;
			arr = (int*)realloc(arr, Size * sizeof(int) ) ;
		}
		arr[i++] = read_int();
	}
	while( stop == 0 );
	Size = i - 1;
	QSort(arr, 0, Size-1);
	for( int i = 9; i < Size; i += 10 ) 
	{
			printf("%d\n", arr[i]);
	}
	delete [] arr;
	return 0;
}
