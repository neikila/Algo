/*
Выполнил: Нейман Кирилл Аркадьевич. (2.Neiman.Kirill)
Группа: АПО-12

1_4. Дано натуральное число N. Представить N в виде A + B, так, что НОД(A, B) максимален, A <= B.
Вывести A и B. Если возможно несколько ответов - вывести ответ с минимальным A.
Пример:
in
35
out
7 28
*/

#include <stdio.h>
#include <iostream>
#include "assert.h"
using namespace std;

//Поиск наменьшего общего делителя
int SearchMinDiv(int N)
{
	int temp = N;
	for ( int i = 2; i*i <= N ; ++i )
	{
		if (N%i==0)
		{
			temp = i;
			break;
		}
	}
	return temp;
}


void countAandB(int N, int* A, int* B)
{
	int temp = SearchMinDiv(N);
	if (temp == N)
	{
		*A = 1;
		*B = N - *A;
	}
	else
	{
		*B = (N/temp)*(temp-1);
		*A = N - *B;
	}
}

int main()
{
	int N = 0;
	//Ввод числа N и проверка
	cin >> N;
	assert(N > 0);

	//Расчет А и B
	int A = 0, B = 0;
	countAandB(N, &A, &B);

	cout << A << ' ' << B << endl;
	return 0;
}
