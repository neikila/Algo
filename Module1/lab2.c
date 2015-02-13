/*
Выполнил: Нейман Кирилл Аркадьевич. (2.Neiman.Kirill)
Группа: АПО-12

2_4. “Считалочка”. 
В круг выстроено N человек, пронумерованных числами от 1 до N. 
Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек. 
(Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й, затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.) 
Необходимо определить номер уцелевшего.
in
10 3
out
4
*/

#include <stdio.h>
#include <stdlib.h>

struct Element
{
	int number;
	struct Element* next;
};

//Deleting all Elements
struct Element* DeleteAll(struct Element* Pointer)
{
	struct Element* temp;
	while(Pointer->next != Pointer)
	{
		temp = Pointer->next;
		Pointer->next = Pointer->next->next;
		free(temp);
	}
	free(Pointer);
	return NULL;
}

//Deleting of the Element
void Delete(struct Element* Pointer)
{
	struct Element* temp = Pointer->next;
	Pointer->next = Pointer->next->next;
	free(temp);
}

//Making the queuqe
struct Element* MakeQueuqe(int size)
{
	struct Element* Start = NULL, *Pointer = NULL;
	int i;
	for( i = 0; i < size; ++i)
	{
		if (Pointer != NULL)
		{
			Pointer->next = (struct Element*)malloc(sizeof(struct Element));
			if (Pointer->next == NULL)
				return DeleteAll(Pointer);
			Pointer = Pointer->next;
		}
		else
		{
			Start = (struct Element*)malloc(sizeof(struct Element));
			if(Start == NULL)
				return DeleteAll(Pointer);
			Pointer = Start;
		}
		Pointer->next = NULL;
		Pointer->number = i+1;	
	}
	Pointer->next = Start;	
	return Pointer;
}

//Crossing out everu num-element
struct Element* CrossOut(struct Element* Pointer, int num)
{
	int i;
	while (Pointer->next != Pointer)
	{
		for ( i = 0; i < num - 1; ++i)
			Pointer = Pointer->next;
		Delete(Pointer);
	}
	return Pointer;
}

//Getting input data
int Input(int* size, int* num)
{
	if(scanf("%d",size) != 1 || getchar() != ' ' || *size < 1)
		return 0;
	char c;
	if(scanf("%d",num) != 1 || !( (c=getchar()) == EOF || c == '\n') )
		return 0;
}

int main()
{
	//Getting the size of queuqe and crossout-number
	int size = 0, num = 0;
	if(Input(&size, &num) == 0)
		return 0;
	struct Element *Pointer = NULL;
	if( (Pointer = MakeQueuqe(size)) == NULL)
		return 0;
	Pointer = CrossOut(Pointer, num);
	
	printf("%d\n", Pointer->number);
	free(Pointer);
	return 0;
}

