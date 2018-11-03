#pragma once
class AVL
{
public:
	int numOfComparisons = 0; 
	int numOfPointerChanges = 0; 
	int numOfBFChanges = 0; 

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
	void HeightOfRoot(); 

private: 

	AVL_Node nodeStorage[10000]; 

	AVL_Node* currentFocus;
	AVL_Node* rootNode;
	int nodeStorage_index = 0;

	int _insert(char in_key[]); 
	void _createRoot(char input[]);
	bool _search(char in_key[], bool call_internal, bool call_delete);
	void _traverse(AVL_Node* in_node);

	void _updateBalanceFactors(); 
	int _calculateBalanceFactor(AVL_Node* focusNode); 
	int _getNodeHeight(AVL_Node* focusNode); 
	bool _checkForImbalance(char new_key[]); 
	void _rotationHandler(AVL_Node* correctionCenter, AVL_Node* treeConnector, char new_key[]); 
	void RR_rotate(AVL_Node* correctionCenter);
	void RL_rotate(AVL_Node* correctionCenter); 
	void LL_rotate(AVL_Node * correctionCenter); 
	void LR_rotate(AVL_Node *correctionCenter); 
	int _getHeightOfNode(AVL_Node* focusNode);
	void _clearChildrenPointers(AVL_Node* targetNode); 
};