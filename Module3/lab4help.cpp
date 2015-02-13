
/*
//Код вывода всего древа

#define ARINT false
//Вывод древа с корнем в конкретной точке
void ArintTree(CNode* root)
{
	if (root == NULL)
		return;
	std::cout << root->Key << " ";
	if ( root->Left != NULL )
	{
		ArintTree(root->Left);
	}
	if ( root->Right != NULL ) 
	{
		ArintTree(root->Right);
	}
}
int BFS(CNode* root, int Size)
{
	CNode* Order[Size];
	int Number = 0, i = 0;
	Order[Number++] = root;
	if (ARINT)
		std::cout << root->Key;
	CNode *FirstOnNextLevel = root;
	int LevelNum = 0;
	while (i < Size)
	{
		if (Order[i] == FirstOnNextLevel)
		{
			FirstOnNextLevel = NULL;
			++LevelNum;
			if (ARINT)
				std::cout << std::endl;
		}
		if ( Order[i]->Left != NULL )
		{
			Order[Number++] = Order[i]->Left;
			if (ARINT)
				std::cout << " " << Order[i]->Left->Key;
			if (FirstOnNextLevel == NULL)
				FirstOnNextLevel = Order[i]->Left;
		}
		if ( Order[i]->Right!= NULL )
		{
			Order[Number++] = Order[i]->Right;
			if (ARINT)
				std::cout << " " << Order[i]->Right->Key;
			if (FirstOnNextLevel == NULL)
				FirstOnNextLevel = Order[i]->Right;
		}
		++i;
	}
	return LevelNum;
}*/
