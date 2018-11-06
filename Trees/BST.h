#pragma once
#include <fStream>
#include <ioStream>

class BST
{
public:
	BST();

	//will count the number of comparisons
	int numOfComparisons = 0; 
	int numOfItems = 0; 

	struct Node
	{
		Node* rightChild; 
		Node* leftChild; 
		Node* parent; 
		char key[50]; 
		int lengthOfChar = 0;  
		int counter = 0; 
	};

	void Insert(char in_key[]);
	void List(); 
	void GetTreeInfo(); 
	//void Search(char in_key[]);

private: 
	Node* currentFocus; 
	Node nodeStorage[1000]; 
	Node* rootNode; 
	int nodeStorage_index = 0; 

	void _createRoot(char input[]); 
	bool _search(char in_key[], bool call_internal, bool call_delete); 
	void _traverse(Node* in_node); 
};