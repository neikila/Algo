#include <iostream>
#include <assert.h>
#include <vector>
#include <time.h>

struct CNode {
	int Data;
	CNode* Next;

	CNode() : Data(0), Next(0) {}
	CNode(int data) : Data(data), Next(0) {}
};

class CList {
public:
	CList() : first(0) {}
	~CList() { DeleteAll(); }

	void AddFirst(CNode* node);
	const CNode* GetFirst() const { return first; };
	void DeleteFirst();
	void DeleteAll();
	bool IsEmpty() const { return first == 0; }

private:
	CNode* first;

};

inline void CList::AddFirst(CNode* node)
{
	if( first == 0 ) {
		first = node;
	} else {
		CNode* second = first;
		first = node;
		first->Next = second;
	}
}

inline void CList::DeleteFirst()
{
	CNode* second = first->Next;
	delete first;
	first = second;
}

inline void CList::DeleteAll()
{
	while( first != 0 ) {
		DeleteFirst();
	}
}

class CStack {
public:
	CStack() {}

	void Push(int data);
	int Pop();
	bool IsEmpty() { return list.IsEmpty(); }

private:
	CList list;
};

void CStack::Push(int data)
{
	list.AddFirst(new CNode(data));
}

int CStack::Pop()
{
	assert( list.GetFirst() != 0 );
	int data = list.GetFirst()->Data;
	list.DeleteFirst();
	return data;
}

void WriteCommand(std::vector<int>& stack, bool needPush)
{
	if( needPush ) {
		int value = rand();
		std::cout << "0 " << value << "\n";
		stack.push_back(value);
	} else {
		int value = stack.back();
		std::cout << "1 " << value << "\n";
		stack.pop_back();
	}
}

void GenerateTest()
{
	std::vector<int> stack;
	std::cout << "2000" << "\n";
	for( int i = 0; i < 1000; i++ ) {
		WriteCommand(stack, true);
		WriteCommand(stack, rand() % 2 == 0);
	}
}

FILE* f; 

int main()
{
	freopen_s(&f, "C:\\Temp\\output.txt", "w", stdout);
	freopen_s(&f, "C:\\Temp\\input.txt", "r", stdin);

	GenerateTest();

/*	int n = 0;
	std::cin >> n;
	clock_t startTime = clock();
	CStack stack;
	for( int i = 0; i < n; i++ ) {
		int operation = 0;
		std::cin >> operation;
		if( operation == 0 ) {
			int data = 0;
			std::cin >> data;
			stack.Push(data);
		} else {
			int data = 0; 
			std::cin >> data;
			if( data != stack.Pop() ) {
				std::cout << "NO";
			}
		}
	}
	std::cout << "YES";
	int processingTime = clock() - startTime;
	std::cout << "Processing Time" << processingTime;*/
	return 0;
}

