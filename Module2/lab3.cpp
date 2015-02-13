/*
Выполнил: Нейман К. А.
Группа: АПО-12
3_3. Закраска прямой 1.
На числовой прямой окрасили N отрезков. Известны координаты левого и правого концов каждого отрезка (Li и Ri). Найти длину окрашенной части числовой прямой.
In
3
1 4
7 8
2 5
Out
5
*/

#include <iostream>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>

void Swap (int* a, int* b)
{
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}

//Класс точки с целочисленными координатами
class Segment
{
public:
	Segment(int xx=0, int yy=0) : x(xx), y(yy) {};
	int GetX() { return x; };
	int GetY() { return y; };
	void Swap(Segment&);
	void Print() { printf("%d %d", x, y);}
	int Length() { return y - x > 0? y - x: 0; };
	bool operator < (Segment&);
private:
	int x;
	int y;
};

void Segment::Swap(Segment& A)
{
	::Swap(&x, &(A.x));
	::Swap(&y, &(A.y));
}

bool Segment::operator < (Segment& A)
{
	bool State = false;
	if ( x == A.x)
	{
		if ( y < A.y )
			State = true;
	}
	else
	{
		if ( x < A.x )
			State = true;
	}
	return State;
}


template < typename T >
class CQueue 
{
public:
	CQueue(int);
	~CQueue() { delete[] Buffer; }
	// Добавление элемента в очереди.
	void PushBack( T a );
	T operator[] (int index) { return Buffer[index]; };
	void Sort();
	int Amount() { return Last; };
	int Count();
private:
	T* Buffer;	//Массив
	int BufferSize;	//Размер массива
	int Last;
};

template < typename T >
CQueue < T >::CQueue(int size):
	BufferSize(size), Last(0)
{
	Buffer = new T[BufferSize]; // Создаем буфер.
}

// Добавление элемента.
template < typename T >
void CQueue < T >::PushBack(T a)
{
	if (Last < BufferSize)
	{
		Buffer[Last++] = a;
	}
}

template <class T>
T* Merge(T *mas1, T *mas2, int s1, int s2)
{
	T *mas = new T[ s1 + s2 ];
	int n = 0;
	while (s1 && s2) 
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
		for (int i = 0; i < s2; ++i) 
		{
			mas[n++] = *mas2++;
		}
	} 
	else 
	{
		for (int i = 0; i < s1; ++i) 
		{
			mas[n++] = *mas1++;
		}
	}
	return mas;
}


template < typename T >
void CQueue < T >::Sort()
{
	int n = 1, l, ost;
	T* mas;
	while (n < Last) 
	{
		l = 0;
		while (l < Last) 
		{
			if (l + n >= Last) break;
			ost = (l + n * 2 > Last) ? (Last - (l + n)) : n;
			mas = Merge(Buffer + l, Buffer + l + n, n, ost);
            for (int i = 0; i < n + ost; ++i)
                Buffer[l+i] = mas[i];
			delete[] mas;
			l += n * 2;
		}
		n *= 2;
	}
}

template < typename T >
int CQueue < T >::Count()
{
	int Length = Buffer[0].Length();
	for (int i = 1; i < Last; ++i)
	{
		if (Buffer[i - 1].GetY() > Buffer[i].GetX())
			if ( Buffer[i - 1].GetY() < Buffer[i].GetY() )
				Buffer[i] = Segment(Buffer[i - 1].GetY(), Buffer[i].GetY());
			else 
				Buffer[i] = Segment(Buffer[i - 1].GetY(),Buffer[i - 1].GetY());
		Length += Buffer[i].Length();
	}
	return Length;
}



int main()
{
	int Number = 0;
	if( scanf("%d\n", &Number) != 1 )
		return 0;
	assert( Number >= 0 );
	
	CQueue < Segment > IntMas(Number);
	
	for( int x, y, i = 0; i < Number; ++i)
	{
		scanf("%d %d", &x, &y);
		getchar();
		IntMas.PushBack(Segment (x, y));
	}
	IntMas.Sort();
	/*for(int i = 0, Number = IntMas.Amount(); i < Number; ++i)
	{
		IntMas[i].Print();
		putchar('\n');
	}*/
	printf("%d",IntMas.Count());
	return 0;
}