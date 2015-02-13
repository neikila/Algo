/*
Выполнил: Нейман К. А.
Группа: АПО-12

Дано число N < 106 и последовательность целых чисел из [-231..231] длиной N.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если root→Key ≤ K, то узел K добавляется в правое поддерево root; иначе в левое поддерево root.

2_2. Выведите элементы в порядке pre-order (сверху вниз).
in
3
2 1 3
out
2 1 3
in
3
1 2 3
out
1 2 3
in
3
3 1 2
out
3 1 2
*/
#include <iostream>
#include <stdio.h>


//Узел
struct CBinaryNode
{
	int Data;
	CBinaryNode* Left;
	CBinaryNode* Right;
	CBinaryNode* Parent;
	CBinaryNode(int data, CBinaryNode* parent) : Data(data), Left(NULL), Right(NULL), Parent(parent) {};
	void Delete();
	void PrintTree();
};

//Вывод древа с корнем в конкретной точке
void CBinaryNode::PrintTree()
{
	std::cout << Data << " ";
	if ( Left != NULL )
	{
		Left->PrintTree();
	}
	if ( Right != NULL ) 
	{
		Right->PrintTree();
	}
}

//Удаление древа с корнем в конкретной точке
void CBinaryNode::Delete()
{
	if ( Left != NULL )
	{
		Left->Delete();
		delete Left;
	}
	if ( Right != NULL )
	{
		Right->Delete();
		delete Right;
	}
}

//Структура древа
struct CTree 
{
	CBinaryNode* Root;
	void Add(int data);
	void PrintDown();
	CTree() : Root (NULL) { };
	~CTree();
};

//Переопределение деструктура для освобожденияпамяти всего древа
CTree::~CTree()
{
	if ( Root != NULL )
	{
		Root->Delete();
		delete Root;
	}
}

//Добавление элемента в древо
void CTree::Add(int data)
{
	CBinaryNode* temp = Root;
	CBinaryNode* prev = NULL;
	while ( temp != NULL )
	{
		prev = temp;
		if (data > temp->Data)
		{
			temp = temp->Right;
		}
		else
		{
			temp = temp->Left;
		}
	}
	CBinaryNode* NewNode = new CBinaryNode (data, prev);
	if ( Root == NULL )
	{
		Root = NewNode;
	}
	else
	{
		if ( data > prev->Data )
		{
			prev->Right = NewNode;
		}
		else
		{
			prev->Left = NewNode;
		}
	}
}


//Вывод древа сверху вниз
void CTree::PrintDown()
{
	Root->PrintTree();
}

int main()
{
	int Size;
	std::cin >> Size;
	CTree Tree;
	int temp;
	int i = Size;
	while (i--)
	{
		std::cin >> temp;
		Tree.Add(temp);
	}
	Tree.PrintDown();
}
