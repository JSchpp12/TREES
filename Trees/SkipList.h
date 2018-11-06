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

	//counters for analysis 
	int numOfCopies = 0;
	int numOfPointerChange = 0; 
	
	int NumOflevels = 0;

	//count of number of comparisons made when inserting 
	int numOfComparisons = 0; 

	skipNode *bottomLeftNode, *topLeftNode; 

	skipNode nodeStorage[1000]; 
	int nodeStorage_index = 0; 

	skipNode* headerNode;
	skipNode* leftNodes[300]; 

	void Insert(char in_key[]); 
	int List(); 
	void GetInfo(); 

private:
	void _insert(char in_key[]); 
	bool _random(); 
	void _createNewNode(skipNode *leftNode, skipNode *rightNode, char in_key[]); 
	int _traverse(); 
	void _increaseCounters(skipNode *targetNode); 
	
};

