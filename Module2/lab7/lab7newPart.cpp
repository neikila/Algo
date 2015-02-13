/*
Выполнил: Нейман К. А.
Группа: АПО-12
4_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <iostream>
#include <stdlib.h>
#include <time.h>

//Разбиение на две части
int Partition(int* arr, int* Temp, int First, int Last)
{
	int Index = rand() % ( Last - First + 1 ) + First;
	int pivot = arr[Index];
	std::cout << "pivot = " << pivot << std::endl;
//	std::swap(arr[First], arr[Index]);
//	std::swap(arr[Index],arr[Last]);
	register int i = First;
	register int j = First;
	for (; i <= Last; ++i)
	{
		if (arr[i] < pivot)
			Temp[j++] = arr[i];
		else
			Temp[Last - ( i - j )] = arr[i];
	}
//	std::swap(Temp[j - 1], Temp[First]);
	/*while( i <= Last && arr[i] <= pivot )
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
	std::swap(arr[i], arr[Last]);*/
	return j;
}

int* QSortFirst(int* arr, int* Temp, int First, int Last) 
{
	int pivotpos;
	static int Num = 0;
	++Num;
	if (First < Last)
	{
		std::cout << (pivotpos = Partition(arr, Temp, First, Last)) << std::endl;
		std::swap(arr, Temp);
		std::cout << "Test " << Num << "\n";
		for( int i = 0; i <= Last; i++ ) 
		{
			std::cout << arr[i] << std::endl;
		}
		QSortFirst(arr, Temp, pivotpos, Last);
		QSortFirst(arr, Temp, First, pivotpos - 1);
	}
	return arr;
}

int* QSort(int* arr, int First, int Last)
{
	//Выделение памяти под свап
	int *Temp = new int [Last + 1];

	int pivotpos;
	int Mas[(Last - First + 1)/2][2]; //Очередь
	int Count = 0, Index = -1;
	Mas[Count][0] = First;
	Mas[Count][1] = Last;
	++Count;
	while(++Index < Count)
	{
		pivotpos = Partition(arr, Mas[Index][0], Mas[Index][1]);
		if (Mas[Index][1] > pivotpos + 1)
		{
			Mas[Count][0] = pivotpos + 1;
			Mas[Count][1] = Mas[Index][1];
			++Count;
		}
		if (Mas[Index][0] < pivotpos - 1)
		{
			Mas[Count][0] = Mas[Index][0];
			Mas[Count][1] = pivotpos - 1;
			++Count;
		}
	}
	return arr;
}

int main() 
{
	int Size = 0;
	int Search = 0;
	std::cin >> Size;
	int* arr = new int[Size];
	/*for( int i = 0; i < Size; i++ ) 
	{
		arr[i] = rand()%100;
	}*/
	arr[0] = 1;
	arr[1] = 1;
	//arr[2] = 6;
	//arr[3] = 2;
	//arr[4] = 0; 
	for( int i = 0; i < Size; i++ ) 
	{
		std::cout << arr[i] << std::endl;
	}
	std::cout << std::endl;
	long int End;
	long int Start = clock();
	arr = QSort(arr, 0, Size-1);
	End = clock();
	std::cout << "Result\n";
	for( int i = 0; i < Size; i++ ) 
	{
		std::cout << arr[i] << std::endl;
	}
	std::cout << "Difftime = " << End - Start << std::endl;
	delete [] arr;
	return 0;
}
