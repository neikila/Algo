#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("%d\n", 1<<0);
}


/*
void CArray::SiftDown(int i)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	// Ищем большего сына, если такой есть.
	int largest = i;
	if( left < SizeMas && Mas[left] > Mas[i] )
		largest = left;
	if( right < SizeMas && Mas[right] > Mas[largest] )
		largest = right;
	// Если больший сын есть, то проталкиваем корень в него.
	if( largest != i ) {
		Swap(&Mas[i], &Mas[largest]);
		this->SiftDown(largest);
	}
}

void CArray::SiftUp(int i)
{
	int parent;
	while( i > 0 ) 
	{
		parent = ( i – 1 ) / 2;
		if( mas[i] <= mas[parent] )
			break;
		swap( &arr[index], &arr[parent] );
		i = parent;
	}
}




	int level = 0;
	while( ( ( 1 << ( level + 1 ) ) - 1 ) < Number ) 
		++level;	 
	for(int j = 0; j <= level; ++j)
	{
		printf("Level #%d\n", j);
		int indexfirst = ( 1 << j ) - 1;
		int indexlast = 2 * indexfirst;

		for( int i = indexfirst; i <= indexlast && i < Number; ++i )
		{
			printf("%d ", IntMas[i]);
		}
		printf("\n");
	}


*/


