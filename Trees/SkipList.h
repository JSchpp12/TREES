#pragma once
class SkipList
{
public:
	SkipList();
	struct skipNode
	{
		char key[50]; 
		int counter; 
		skipNode *rightNode, *leftNode, *upNode, *downNode;
		

		//this will represent what level this node is on 
		int level; 
	};

	int NumOflevels = 0;

	//count of number of comparisons made when inserting 
	int numOfComparisons = 0; 

	skipNode *bottomLeftNode, *topLeftNode; 

	skipNode nodeStorage[10000]; 
	int nodeStorage_index = 0; 

	skipNode* headerNode;
	skipNode* leftNodes[300]; 

	void Insert(char in_key[]); 
	void List(); 

private:
	void _insert(char in_key[]); 
	bool _random(); 
	void _createNewNode(skipNode *leftNode, skipNode *rightNode, char in_key[]); 
	void _traverse(); 
	void _increaseCounters(skipNode *targetNode); 
	
};

