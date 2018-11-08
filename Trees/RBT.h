#pragma once
//RBT.h
//Jacob Schaupp
//EECS 2510, Fall 2018
//11/7/2018
//Contains the header information for the RBT class 

class RBT
{
public:
	RBT();
	struct RBT_Node
	{
		int height;
		int counter;
		int black_height;
		char key[50];

		//color = 1 ---- RED
		//color = 2 ---- BLACK
		int color;
		RBT_Node* leftChild, *rightChild, *parent;
	};

	int numOfRotations = 0;
	int numOfReColor = 0; 
	int numOfItems = 0; 

	RBT_Node t_nil;

	RBT_Node nodeStorage[50000];
	int nodeStorage_index = 0; 

	RBT_Node *rootNode;

	int numOfComparisons = 0;
	void Insert(char new_key[]);
	void GetTreeInfo();

private:
	void _insert(char in_key[]);
	void _createRoot(char in_key[]);
	bool _search(char in_key[], bool call_internal, bool call_delete);
	void _checkForError(int memoryIndex);
	void RR_rotate(RBT_Node* correctionCenter, bool call_multi);
	void LL_rotate(RBT_Node* correctionCenter, bool call_multi);
	void _traverse(RBT_Node* in_node); 
};

