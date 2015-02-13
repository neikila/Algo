/*
Выполнил: Нейман К. А.
Группа: АПО-12
4_3. Реализуйте стратегию выбора опорного элемента “случайный элемент”. Функцию Partition реализуйте методом прохода двумя итераторами от начала массива к концу.
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>

int stop  = 0;

void swap (int *a, int *b)
{
	static int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

//Разбиение на две части
int Partition(int* arr, int First, int Last)
{
	int Index = rand() % ( Last - First + 1 ) + First;
	int pivot = arr[Index];
	swap(&arr[Index], &arr[Last]);
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
			swap( &arr[i++], &arr[j++]);
		}
	}
	swap(&arr[i], &arr[Last]);
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
