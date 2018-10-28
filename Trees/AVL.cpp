#include "pch.h"
#include "AVL.h"
#include <string.h>

AVL::AVL()
{
}

void AVL::Insert(char in_key[])
{
	AVL_Node* returnedNode; 

	/*
	1. insert new node 
	2. calculate new BFs 
	3. check for a BF that is out of spec
	4. figure out what type of rotation is needed
	5. correct with necessar rotation type 
	*/

	_insert(in_key); 

}

int AVL::_insert(char in_key[])
{
	//this will be slightly different from the BST insert, for simplicity will return node pointer so focus can be set on subtrees
	//can't seem to return AVL_Node object 
	//will return node_storage index instead, will work the same way 

	int in_weight = 0;
	bool cont = false;
	bool done = false;
	bool found;
	AVL_Node* currentNode;

	//need to search first 
	found = _search(in_key, true, false);
	//if not found, need to make a new node 
	if (found == false)
	{
		if (rootNode != nullptr)
		{
			currentNode = rootNode;
			while (done == false)
			{
				//increment number of comparisons counter 
				this->numOfComparisons++;

				//else if (in_weight > currentNode->keyWeight)
				if (strcmp(currentNode->key, in_key) < 0)
				{
					if (currentNode->rightChild == nullptr)
					{
						//this is empty spot
						AVL_Node newNode;
						newNode.counter = 1;
						//newNode.keyWeight = _calculateKeyWeight(in_key); 
						newNode.parent = currentNode;

						//set the new node key 
						strcpy(newNode.key, in_key);

						//store the new node
						nodeStorage[nodeStorage_index] = newNode;
						currentNode->rightChild = &nodeStorage[nodeStorage_index];
						nodeStorage_index++;

						done = true;
					}
					else
					{
						//not an empty spot need to keep looking 
						currentNode = currentNode->rightChild;
					}
				}
				//else if (in_weight < currentNode->keyWeight)
				else if (strcmp(currentNode->key, in_key) > 0)
				{
					if (currentNode->leftChild == nullptr)
					{
						//this is an empty spot
						//Node newNode(in_key, currentNode);

						AVL_Node newNode;
						//copy the key over 
						newNode.counter = 1;
						//newNode.keyWeight = _calculateKeyWeight(in_key); 
						newNode.parent = currentNode;

						//set the newNode key
						strcpy(newNode.key, in_key);

						//copy the node to memory 
						nodeStorage[nodeStorage_index] = newNode;
						currentNode->leftChild = &nodeStorage[nodeStorage_index];
						nodeStorage_index++;

						done = true;
					}
					else
					{
						//need to keep looking for empty spot
						currentNode = currentNode->leftChild;
					}
				}
			}
		}
		else
		{
			this->_createRoot(in_key);
		}
	}
}

bool AVL::_search(char in_key[], bool call_internal, bool call_delete)
{
	int in_weight = 0;
	int counter = 0;
	bool found = false;
	bool done = false;
	AVL_Node* currentNode;

	//look for the correct node 
	if (rootNode != nullptr)
	{
		currentNode = rootNode;
		while (done == false)
		{
			if (currentNode)
			{
				if (0 == strcmp(currentNode->key, in_key))
				{
					//found node
					if (call_internal == true)
					{
						//called from insert method, so add 1 to found node 
						currentNode->counter = currentNode->counter + 1;
						done = true;
						found = true;
					}
					else if (call_delete == true)
					{
						//called from delete method, so subtract 1 from found node 
						currentNode->counter--;
						done = true;
						found = true;
					}
					else
					{
						//called from search command 
						done = true;
						found = true;
					}
				}
				else if (strcmp(currentNode->key, in_key) < 0)
					//else if (in_weight > currentNode->keyWeight)
				{
					if (currentNode->rightChild != nullptr)
					{
						currentNode = currentNode->rightChild;
					}
					else
					{
						//fell off tree -- not found 
						done = true;
						found = false;
					}
				}
				//else if (in_weight < currentNode->keyWeight)
				else if (strcmp(currentNode->key, in_key) > 0)
				{
					if (currentNode->rightChild != nullptr)
					{
						//set to next node in tree and rerun above code with this new node 
						currentNode = currentNode->rightChild;
					}
					else
					{
						//fell off the tree -- not found 
						done = true;
						found = false;
					}
				}
			}
		}
	}
	return found;
}

void AVL::_createRoot(char input[])
{
	int counter = 0;

	AVL_Node newNode;
	newNode.counter = 1;
	newNode.BF = 0; 

	strcpy(newNode.key, input);

	//store node into memory 
	nodeStorage[nodeStorage_index] = newNode;
	nodeStorage_index++;
}

void AVL::_calculateBalanceFactor(AVL_Node* focusNode)
{
	//this should just calculate the balance factor of one node
	//call from method that will handle which nodes need to be recalculated 

}