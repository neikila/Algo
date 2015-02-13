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
class Point
{
public:
	Point(int xx=0, int yy=0) : x(xx), y(yy) {};
	int GetX() { return x; };
	int GetY() { return y; };
	void Swap(Point&);
	void Print() { printf("%d %d", x, y);}
	bool operator < (Point&);
private:
	int x;
	int y;
};

void Point::Swap(Point& A)
{
	::Swap(&x, &(A.x));
	::Swap(&y, &(A.y));
}

bool Point::operator < (Point& A)
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

// Куча данных типа T, реализованная с помощью массива.
template < typename T >
class CArray 
{
public:
	CArray( int size );
	~CArray() { delete Mas; };
	int Amount() { return Number; };
	T GetFirst();	
	void SiftUp(int);
	void SiftDown(int);
	void AddElement( T );		//Добавление элемента
private:
	T* Mas;	//Массив данных
	int SizeMas;	//Размер кучи
	int Number;	//Количество уже заполненных элементов
};

template < typename T >
T CArray < T >::GetFirst()
{
	T temp = Mas[0];
	Mas[0].Swap(Mas[--Number]);
	SiftDown( 0 );
	return temp;
}

// Проталкивание элемента вниз.
template < typename T >
void CArray < T >::SiftDown( int i )
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	// Ищем меньшего сына, если такой есть.
	int largest = i;
	if( left < Number && Mas[left] < Mas[i] )
		largest = left;
	if( right < Number && Mas[right] < Mas[largest] )
		largest = right;
	// Если меньший сын есть, то проталкиваем корень в него.
	if( largest != i ) 
	{
		Mas[i].Swap(Mas[largest]);
		SiftDown( largest );
	}
}


// Проталкивание элемента наверх.
template < typename T >
void CArray < T >::SiftUp( int i )
{
	int parent;
	while( i > 0 ) 
	{
		parent = ( i - 1 ) / 2;
		if( Mas[i] < Mas[parent] )
			Mas[i].Swap(Mas[parent]);
		i = parent;
	}	
}

template < typename T >
CArray < T >::CArray(int size): SizeMas(size), Number(0)
{
	Mas = new T[SizeMas]; // Создаем буфер.
}

template < typename T >
void CArray < T >::AddElement(T Data)
{
	Mas[Number] = Data;
	SiftUp(Number);
	Number++;
}


int main()
{
	//Получение количества слогаемых
	int Number = 0;
	if( scanf("%d\n", &Number) != 1 )
		return 0;
	assert( Number >= 0 );
	
	CArray < Point > IntMas(Number);
	
	for( int x, y, i = 0; i < Number; ++i)
	{
		scanf("%d %d", &x, &y);
		getchar();
		IntMas.AddElement(Point (x, y));
	}
	for(int i = 0, Number = IntMas.Amount(); i < Number; ++i)
	{
		(IntMas.GetFirst()).Print();
		putchar('\n');
	}
	return 0;
}