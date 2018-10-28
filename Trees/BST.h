#pragma once
#include <fStream>
#include <ioStream>

class BST
{
public:
	BST();

	//will count the number of comparisons
	int numOfComparisons = 0; 

	struct Node
	{
		Node* rightChild; 
		Node* leftChild; 
		Node* parent; 
		char key[50]; 
		int lengthOfChar = 0; 
		int keyWeight; 
		int counter; 
	};

	
	~BST();

private: 
	Node* currentFocus; 
	Node nodeStorage[100]; 
	Node* rootNode; 
	int nodeStorage_index = 0; 

	void Insert(char in_key[]); 
	void Search(char in_key[]); 
	void _createRoot(char input[]); 
	bool _search(char in_key[], bool call_internal, bool call_delete); 
	int _calculateKeyWeight(char in_key[]); 
	void _setNodeKey(Node* currentNode, char in_key[]); 
};