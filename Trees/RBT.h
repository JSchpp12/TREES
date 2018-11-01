#pragma once
class RBT
{
public:
	RBT();
	struct RBT_Node
	{
		int height; 
		int black_height; 
		char key[50]; 

	};

	RBT_Node nodeStorage[100000]; 
	int nodeStorage_index = 0; 

	RBT_Node *rootNode; 

	void Insert(char new_key[]); 
	~RBT();

private: 
	void _insert(char in_key[]);
	void _createRoot(); 
};

