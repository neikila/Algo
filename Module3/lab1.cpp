#include <iostream>
#include <vector>
#include <string>

using namespace std;

const int InitialSize = 2;
const int MaxOccupancy = 2;
const int GrowFactor = 2;

int Hash(const string& data, int tableSize)
{
	int hash = 0;
	for( unsigned int i = 0; i < data.size(); i++ ) {
		hash = (hash * 127 + data[i]) % tableSize;
	}
	return hash;
}

int SquereHash(int DefaultHash, int TableSize, int i)
{
	return (DefaultHash + i * (i + 1) / 2) % TableSize;
}

template<class T>
struct CHashTableNode {
	T Data;
	CHashTableNode<T>* Next;

	CHashTableNode() : Next(0) {}
	CHashTableNode(const T& data, CHashTableNode<T>* next) : Data(data), Next(next) {}
};

template<class T>
class CHashTable {
public:
	CHashTable();
	~CHashTable();

	bool Has(const T& data) const;
	bool Add(const T& data);
	bool Delete(const T& data);

private:
	vector<CHashTableNode<T>*> table;
	unsigned int keysCount;

	bool has(const T& data, int hash) const;
	void growTable();
};

template<class T>
CHashTable<T>::CHashTable() :
	keysCount(0)
{
	table.resize(InitialSize, 0);
}

template<class T>
CHashTable<T>::~CHashTable()
{
	for( unsigned  int i = 0; i < table.size(); i++ ) {
		CHashTableNode<T>* node = table[i];
		while( node != 0 ) {
			CHashTableNode<T>* nextNode = node->Next;
			delete node;
			node = nextNode;
		}
	}
}

template<class T>
bool CHashTable<T>::Has(const T& data) const
{
	int hash = Hash(data, table.size());
	return has(data, hash);
}

template<class T>
bool CHashTable<T>::has(const T& data, int hash) const
{
	CHashTableNode<T>* node = table[hash];
	while( node != 0 && node->Data != data ) {
		node = node->Next;
	}
	return node != 0;
}


template<class T>
bool CHashTable<T>::Add(const T& data)
{
	int hash = Hash(data, table.size());
	if( has(data, hash) ) {
		return false;
	}

	if( keysCount + 1 > MaxOccupancy * table.size() ) {
		growTable();
		hash = Hash(data, table.size());
	}

	table[hash] = new CHashTableNode<T>(data, table[hash]);
	keysCount++;
	return true;	
}

template<class T>
void CHashTable<T>::growTable()
{
	vector<CHashTableNode<T>*> newTable(table.size() * GrowFactor, 0); 
	for( unsigned int i = 0; i < table.size(); i++ ) {
		CHashTableNode<T>* node = table[i];
		while( node != 0 ) {
			CHashTableNode<T>* nextNode = node->Next;
			int newHash = Hash(node->Data, newTable.size());
			node->Next = newTable[newHash];
			newTable[newHash] = node;
			node = nextNode;
		}
	}
}

template<class T>
bool CHashTable<T>::Delete(const T& data)
{
	int hash = Hash(data, table.size());
	CHashTableNode<T>* prevNode = 0;
	CHashTableNode<T>* node = table[hash];
	while( node != 0 && node->Data != data ) {
		prevNode = node;
		node = node->Next;
	}
	if( node == 0 ) {
		return false;
	}
	if( prevNode != 0 ) {
		prevNode->Next = node->Next;
	} else {
		table[hash] = node->Next;
	}
	delete node;
	return true;
}

int main()
{
	CHashTable<string> table;
	char operation;
	string word;

	while( cin >> operation >> word ) {
		if( operation == '+' ) {
			cout << (table.Add(word) ? "OK" : "FAIL") << "\n";
		} else if( operation == '-' ) {
			cout << (table.Delete(word) ? "OK" : "FAIL") << "\n";
		}if( operation == '?' ) {
			cout << (table.Has(word) ? "OK" : "FAIL") << "\n";
		}
	}

	return 0;
}
