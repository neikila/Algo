/*
Выполнил: Нейман К. А.
Группа: АПО-12
3_2. Вычислить количество узлов в самом широком слое декартового дерева и количество узлов в самом широком слое наивного дерева поиска. Вывести их разницу.

in
10
5 11
18 8
25 7
50 12
30 30
15 15
20 10
22 5
40 20
45 9
out
1

in
10
38 19
37 5
47 15
35 0
12 3
0 42
31 37
21 45
30 26
41 6
out
1

*/
#include <iostream>
#include <stdio.h>


//Узел
struct CBinaryNode
{
	int Data;
	int Priority;
	CBinaryNode* Left;
	CBinaryNode* Right;
	CBinaryNode* Parent;
    CBinaryNode(int data, CBinaryNode* parent, int pr = 0, CBinaryNode *L = NULL, CBinaryNode *R = NULL) : Data(data), Priority(pr), Left(L), Right(R), Parent(parent) {}
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
class CTree 
{
protected:
	CBinaryNode* Root;
public:
	virtual void Add(int data);
	int BFS(int Size);
	void PrintDown();
	CTree(CBinaryNode *R = NULL) : Root (R) { };
	~CTree();
};

//Переопределение деструктура для освобождения памяти всего древа
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

//Поиск в ширину
int CTree::BFS(int Size)
{
	CBinaryNode* Order[Size];
	int Number = 0, i = 0;
	Order[Number++] = Root;
	//std::cout << Root->Data;
	CBinaryNode *FirstOnNextLevel = Root;
	int LevelNum = 0;
	int WidthMax = 1;
	int WTemp = 0;
	while (i < Size)
	{
		if (Order[i] == FirstOnNextLevel)
		{
			FirstOnNextLevel = NULL;
			if (WTemp > WidthMax)
				WidthMax = WTemp;
			++LevelNum;
			WTemp = 0;
			std::cout << std::endl;
		}
		if ( Order[i]->Left != NULL )
		{
			Order[Number++] = Order[i]->Left;
			++WTemp;
		//	std::cout << " " << Order[i]->Left->Data;
			if (FirstOnNextLevel == NULL)
				FirstOnNextLevel = Order[i]->Left;
		}
		if ( Order[i]->Right!= NULL )
		{
			Order[Number++] = Order[i]->Right;
			++WTemp;
		//	std::cout << " " << Order[i]->Right->Data;
			if (FirstOnNextLevel == NULL)
				FirstOnNextLevel = Order[i]->Right;
		}
		++i;
	}
	//std::cout << std::endl << "WidthMax = " << WidthMax << std::endl;
	return WidthMax;
}

//Вывод древа сверху вниз
void CTree::PrintDown()
{
	Root->PrintTree();
}

class CDecardTree : public CTree
{
public:
	void Add(int data, int priority);
	void MergeWith(CDecardTree *&B);
	void SplitTo(int key, CDecardTree *&Second);
	CDecardTree(CBinaryNode* R = NULL) : CTree(R) {};
};

void Split(CBinaryNode *Root, int key, CBinaryNode *&Left, CBinaryNode *&Right)
{
	if (Root == NULL)
	{
		Left = NULL;
		Right = NULL;
	}
	else
	{
		if (Root->Data <= key)
		{
			Split(Root->Right, key, Root->Right, Right);
			Left = Root;
		}
		else
		{
			Split(Root->Left, key, Left, Root->Left);
			Right = Root;
		}
	}
};

void CDecardTree::SplitTo(int key, CDecardTree *&Second)
{
	CBinaryNode *NewRoot;
	Split(Root, key, Root, NewRoot);
	Second = new CDecardTree (NewRoot);
}


CBinaryNode *Merge(CBinaryNode *Left, CBinaryNode *Right)
{
	if (Left == NULL)
		return Right;
	if (Right == NULL)
		return Left;
	if (Left->Priority > Right->Priority)
	{
		Left->Right = Merge(Left->Right, Right);
		return Left;
	}
	Right->Left = Merge(Left, Right->Left);
	return Right;
}


void CDecardTree::MergeWith(CDecardTree *&B)
{
	Root = Merge(Root, B->Root);
	delete B;
}

void CDecardTree::Add(int data, int priority)
{
	CBinaryNode *Temp = Root, *Prev = NULL;
	while (Temp != NULL && Temp->Priority > priority)
	{
		Prev = Temp;
		if (Temp->Data > data)
			Temp = Temp->Left;
		else
			Temp = Temp->Right;
	}

	CBinaryNode *Left = NULL, *Right = NULL;
	if (Temp != NULL)
	{
		Split(Temp, data, Left, Right);
	}
	CBinaryNode *New = new CBinaryNode(data, Prev, priority, Left, Right);
	if (Left != NULL)
		Left->Parent = New;
	if (Right != NULL)
		Right->Parent = New;
	if (Prev != NULL)
	{
		if (Prev->Data < data)
			Prev->Right = New;
		else
			Prev->Left = New;
	}
	else
	{
		Root = New;
	}
}

int main()
{
	int Size;
	std::cin >> Size;
	CTree Tree;
	CDecardTree DTree;
	int data, priority;
	int i = Size;
	while (i--)
	{
		std::cin >> data;
		std::cin >> priority;
		Tree.Add(data);
		DTree.Add(data, priority);
	}
	int NativeTreeWidth = Tree.BFS(Size);
	int DecartTreeWidth = DTree.BFS(Size);
	std::cout << DecartTreeWidth - NativeTreeWidth << std::endl; 
}
