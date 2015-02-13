/*
Выполнил: Нейман К. А.
Группа: АПО-12

Задача 4. АВЛ-дерево (4 балла)
Написать АВЛ-дерево.
Дана последовательность команд добавления или удаления натуральных чисел в АВЛ-дерево. Команда добавления числа A задается положительным числом A, команда удаления числа A задается отрицательным числом “-A”. Требуется вывести высоту АВЛ-дерева после выполнения всех команд.
in
2 4 6 -2
out
2
*/

#include <iostream>

struct CNode
{
    int Key;
    int Height;
    CNode* Left;
    CNode* Right;
    CNode(int k) : Key(k), Left(NULL), Right(NULL), Height(1) {}
};

int Height(CNode* A)
{
    return A ? A->Height : 0;
}

void Correct(CNode* A)
{
 		if (Height(A->Left) > Height(A->Right))
		{
			A->Height = Height(A->Left) + 1;
		}
		else
		{
			A->Height = Height(A->Right) + 1;
		}
}

CNode* RotateRight(CNode* A)
{
    CNode* L = A->Left;
    A->Left = L->Right;
    L->Right = A;
    Correct(A);
    Correct(L);
    return L;
}

CNode* RotateLeft(CNode* A)
{
    CNode* R = A->Right;
    A->Right = R->Left;
    R->Left = A;
    Correct(A);
    Correct(R);
    return R;
}

CNode* MakeItBalanced(CNode* A)
{
		CNode* Temp = NULL;
    Correct(A);
    if( Height(A->Right) - Height(A->Left) == 2 )
    {
        if( Height(A->Right->Right) - Height(A->Right->Left) < 0 )
				{
            A->Right = RotateRight(A->Right);
				}
        Temp = RotateLeft(A);
    }
    if( Height(A->Right) - Height(A->Left) == -2 )
    {
        if( Height(A->Left->Right) - Height(A->Left->Left) > 0  )
				{
            A->Left = RotateLeft(A->Left);
				}
        Temp = RotateRight(A);
    }
    return Temp == NULL ? A : Temp;
}

CNode* Add(CNode* A, int k)
{
		CNode* Temp;
    if( A == NULL ) 
		{
			Temp = new CNode(k);
		}
		else
		{
    	if( k < A->Key )
			{
    	    A->Left = Add(A->Left,k);
			}
    	else
			{
    	    A->Right = Add(A->Right,k);
			}
			Temp = MakeItBalanced(A);
		}
    return Temp;
}

CNode* FindMin(CNode* A) 
{
    return A->Left ? FindMin(A->Left) : A;
}

CNode* RemoveMin(CNode* A)
{
		CNode* Temp;
    if( A->Left == NULL )
		{
        Temp = A->Right;
		}
		else
		{
    	A->Left = RemoveMin(A->Left);
			Temp = MakeItBalanced(A); 
    }
		return Temp; 
}

CNode* Remove(CNode* A, int k)
{
		CNode* Temp = NULL;
    if( A != NULL ) 
		{
			if( k < A->Key )
			{
				A->Left = Remove(A->Left, k);
			}
			else
			{
				if( k > A->Key )
				{
					A->Right = Remove(A->Right, k);	
				}
				else
				{
					CNode* L = A->Left;
					CNode* R = A->Right;
					delete A;
					if( R == NULL ) 
					{
						return L;
					}
					CNode* Min = FindMin(R);
					Min->Right = RemoveMin(R);
					Min->Left = L;
					return MakeItBalanced(Min);
				}
			}
    	Temp = MakeItBalanced(A);
		}
		return Temp;
}

void Delete(CNode* Root)
{
	if ( Root->Left != NULL )
	{
		Delete(Root->Left);
		delete Root->Left;
		Root->Left = NULL;
	}
	if ( Root->Right != NULL )
	{
		Delete(Root->Right);
		delete Root->Right;
		Root->Right = NULL;
	}
}

int main()
{
	CNode *Root = NULL;
	int Command;
	while (std::cin >> Command, !std::cin.eof())
	{
		if (Command >= 0)
		{
			Root = Add(Root, Command);
		}
		else
		{
			Root = Remove(Root, -1 * Command);
		}
	}
	std::cout << Root->Height << std::endl;
	Delete(Root);
	delete Root;
}
