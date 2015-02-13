/*
Выполнил: Нейман Кирилл Аркадьевич. (2.Neiman.Kirill)
Группа: АПО-12

3_1. Дан отсортированный массив целых чисел A[0..n-1] и массив целых чисел B[0..m-1]. Для каждого элемента массива B[i] найдите минимальный индекс минимального элемента массива, равного или превосходящего b: A[k] >= B[i]. Если такого элемента нет, выведите n. Время работы поиска каждого элемента B[i]: O(log(k)).
Формат входных данных.
В первой строчке записаны числа m и n. Во второй и третьей массивы A и B соответственно.
in
2 1
1 2
2
out
1
in
4 3
2 4 5 7
4 6 1
out
1 3 0
*/

/*
Test 5
10 11
5 25 45 50 53 71 72 75 81 93
23 29 32 71 74 75 82 85 96 99

1 2 2 5 7 7 8 9 9 21 22

1 2 2 5 7 7 8 9 9 10 10

*/

#include <stdio.h>
#include <stdlib.h>

//Data Input
int Input(int** A, int* sizeA, int** B, int* sizeB)
{
	int size[2];
	int* IntMas[2];
	if(scanf("%d %d", &(size[0]), &(size[1]) ) != 2)
		return 0;
	int j;
	for(j = 0; j < 2; ++j)
	{
		IntMas[j] = (int*)malloc(size[j]*sizeof(int));
		if (IntMas[j] == NULL)
			return 0;
		int i;
		for(i = 0; i < size[j]; ++i)
		{
			if(scanf("%d", &(IntMas[j][i])) != 1)
			{
				free(IntMas[j]);
				return 0;
			}
		}
	}
	*A = IntMas[0];
	*B = IntMas[1];
	*sizeA = size[0];
	*sizeB = size[1];
	return 1;
}


//Search of limits for binary search
void SearchLimit(int* IntMas, int size, int Num, int* min, int* max)
{
	int i = 0;
	while(IntMas[1 << i] < Num && (1 << i) < size) 
	{
		i++;
	}
	*min = (i == 0) ? 0 : 1 << (i - 1);
	*max = ((1 << i) < size)? 1 << i : size;
}

int BinarySearch(int* IntMas, int left, int right, int num)
{
	int first = left;
	int last = right;
	int mid;
	while( first < last ) 
	{
		mid = (first + last) / 2;
		if(num <= IntMas[mid])
			last = mid;
		else
			first = mid + 1;
	}
	return num <= IntMas[last] ? last : right;
}

int main()
{
	//Getting the size of queuqe and crossout-number
	int *A, *B, sizeA, sizeB;
	if(Input(&A, &sizeA, &B, &sizeB) == 0)
		return 0;

	int i, IndexMin, IndexMax;
	for(i = 0; i < sizeB; i++)
	{
		IndexMin = 0;
		IndexMax = sizeA;
		SearchLimit(A, sizeA, B[i], &IndexMin, &IndexMax);
		printf("%d ",BinarySearch(A, IndexMin, IndexMax, B[i]));
	}
	free(A);
	free(B);
	return 0;
}

