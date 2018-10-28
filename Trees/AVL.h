#pragma once
class AVL
{
public:
	AVL();
	struct AVL_Node
	{
		int BF; 
		int keyWeight = 0; 
		char key[50]; 

		AVL_Node* leftChild; 
		AVL_Node* rightChild; 
	};

private: 
	void RR_rotate();
	void LL_rotate(); 

};

