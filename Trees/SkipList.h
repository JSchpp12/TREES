#pragma once
class SkipList
{
public:
	SkipList();
	struct skipNode
	{
		char key[50]; 
		skipNode *rightNode, *leftNode, *upNode, *downNode;

		//this will represent what level this node is on 
		int level; 
	};

	int NumOflevels = 0;

	skipNode *bottomLeftNode, *topLeftNode; 

	skipNode nodeStorage[10000]; 
	int nodeStorage_index = 0; 

	//fraction of nodes with level i pointers also having i+1 pointers 
	float p; 

	skipNode* headerNode;
	skipNode* leftNodes[100]; 

	void Insert(char in_key[]); 

private:
	void _insert(char in_key[]); 
	bool _random(); 
	void _createNewNode(skipNode *leftNode, skipNode *rightNode, char in_key[]); 
};

