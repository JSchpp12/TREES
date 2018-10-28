#pragma once
class AVL
{
public:
	AVL();
	struct AVL_Node
	{
		int BF; 
		AVL_Node* leftChild; 
		AVL_Node* rightChild; 

	};


	~AVL();
};

