#pragma once
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

	RBT_Node t_nil;

	RBT_Node nodeStorage[10000];
	int nodeStorage_index = 0; 

	RBT_Node *rootNode;

	int numOfComparisons = 0;
	void Insert(char new_key[]);
	void print();

private:
	void _insert(char in_key[]);
	void _createRoot(char in_key[]);
	bool _search(char in_key[], bool call_internal, bool call_delete);
	void _checkForError(int memoryIndex);
	void RR_rotate(RBT_Node* correctionCenter, bool call_multi);
	void LL_rotate(RBT_Node* correctionCenter, bool call_multi);
};

