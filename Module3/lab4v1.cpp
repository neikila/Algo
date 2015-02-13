
/*
struct CNode
{
	int Key;
	int Height;
	CNode *Left;
	CNode *Right;
	CNode *Parent;

	CNode (int k = 0, CNode *l = NULL, CNode *r = NULL, CNode *p = NULL, int h = 0) : Key(k), Height(h), Left(l), Right(r), Parent(p) {} 
	int IsBalanced();
	void Correct();
	CNode *RotateLeft();
	CNode *RotateRight();
	CNode *MakeItBalanced(); // балансировка узла p
	CNode *Min();
	CNode *DeleteMin();
};

int CNode::IsBalanced()
{
	return Right->Height - Left->Height;
}

void CNode::Correct()
{
	if (Right->Height > Left->Height)
		Height = Right->Height + 1;
	else
		Height = Left->Height + 1;
}

CNode* CNode::RotateLeft()
{
	CNode* B = Right;
	Right = B->Left;
	B->Left = this;
	Correct();
	B->Correct();
	return B;
}

CNode* CNode::RotateRight()
{
	CNode* B = Left;
	Left = B->Right;
	B->Right = this;
	Correct();
	B->Correct();
	return B;
}

CNode* CNode::MakeItBalanced()
{
		Correct();
    if( IsBalanced() == 2 )
    {
        if( Right->Height < 0 )
            Right = Right->RotateRight();
        return RotateLeft();
    }
    if( IsBalanced() == -2 )
    {
        if( Left->Height < 0 )
            Left = Left->RotateLeft();
        return RotateRight();
    }
		return this;
}

CNode* Insert(CNode* A, int key)
{
	if (A == NULL ) 
		return new CNode(key);
	if (key < A->Key)
		A->Left = Insert(A->Left, key);
	else
		A->Right = Insert(A->Right, key);
	return A->MakeItBalanced();
}

CNode* CNode::Min() // поиск узла с минимальным ключом в дереве p 
{
    return Left ? Left->Min() : this;
}

CNode* CNode::DeleteMin() // удаление узла с минимальным ключом из дерева p
{
    if( Left == NULL )
        return Right;
    Left = Left->DeleteMin();
    return MakeItBalanced();
}

CNode* remove(CNode* p, int k) // удаление ключа k из дерева p
{
    if( p == NULL )
			return NULL;
    if( k < p->Key )
        p->Left = remove(p->Left,k);
    else if( k > p->Key )
        p->Right = remove(p->Right,k);	
    else //  k == p->key 
    {
        CNode* l = p->Left;
        CNode* r = p->Right;
        delete p;
        if( !r ) return l;
        CNode* min = r->Min();
        min->Right = r->DeleteMin();
        min->Left = l;
        return min->MakeItBalanced();
    }
    return p->MakeItBalanced();
}

int main()
{
	CNode *Root = NULL;
	int Command;
	while (!std::cin.eof())
	{
		std::cin >> Command;
		if (Command >= 0)
			Root = Insert(Root, Command);
		else
			Root = Insert(Root, -1 * Command);
	}
}*/
