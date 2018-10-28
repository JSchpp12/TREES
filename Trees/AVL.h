#pragma once
class AVL
{
public:
	int numOfComparisons = 0; 

	AVL();
	struct AVL_Node
	{
		int BF; 
		char key[50]; 
		int counter = 0; 

		AVL_Node* leftChild; 
		AVL_Node* rightChild;

		//I know this is not necessarly needed, however it might be useful down the road 
		AVL_Node* parent; 
	};

	void Insert(char in_key[]); 

private: 

	AVL_Node nodeStorage[10000]; 

	AVL_Node* currentFocus;
	AVL_Node* rootNode;
	int nodeStorage_index = 0;

	void _createRoot(char input[]);
	bool _search(char in_key[], bool call_internal, bool call_delete);
	void _traverse(AVL_Node* in_node);

	void RR_rotate();
	void LL_rotate(); 
};

