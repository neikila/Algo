/*
Выполнил: Нейман К. А.
Группа: АПО-12
4_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>

//Разбиение на две части
int Partition(int* arr, int First, int Last)
{
	int Index = rand() % ( Last - First + 1 ) + First;
	int pivot = arr[Index];
	std::swap(arr[Index],arr[Last]);
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


void QSort(int* arr, int First, int Last) 
{
	int pivotpos;
	if (First < Last)
	{
		pivotpos = Partition(arr, First, Last);
		QSort(arr, pivotpos + 1, Last);
		QSort(arr, First, pivotpos - 1);
	}
	return;
}

int main() 
{
	int Size = 0;
	int Search = 0;
	std::cin >> Size;
	int* arr = new int[Size];
	for( int i = 0; i < Size; i++ ) 
	{
		arr[i] = rand();
	}
	long int End;
	long int Start = clock();
	QSort(arr, 0, Size-1);
	End = clock();
	/*for( int i = 0; i < Size; i++ ) 
	{
		std::cout << arr[i] << std::endl;
	}*/
	std::cout << "Difftime = " << End - Start << std::endl;
	delete [] arr;
	return 0;
}