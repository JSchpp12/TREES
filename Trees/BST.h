//Jacob Schaupp 
//EECS 2510 Non Linear 
//09-28-2018
#pragma once
#include <string>
#include <iostream>
#include "Node.h"
#include <list>
using namespace std;
class BST
{
public:
	BST();
	~BST();

	void Insert(string input);
	void List();
	void Search(string in_key);
	void Delete(string in_key);
	void Minimum();
	void Maximum();
	void Next(string in_key);
	void Previous(string in_key);

private:
	Node* currentFocus;
	Node nodeStorage[100];
	Node* rootNode;
	int nodeStorage_index = 0;
	void _createRoot(string input);
	bool _search(string in_key, bool call_internal, bool call_delete);
	void _traverse(Node* current_node);
	void _getRange(bool mM);
	Node* _getNode(string in_key);
};


