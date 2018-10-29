#include "pch.h"
#include "AVL.h"
#include <string.h>
#include <iostream>

using namespace std; 

AVL::AVL()
{
}

void AVL::Insert(char in_key[])
{
	int insertIndex;

	/*
	1. insert new node 
	2. calculate new BFs 
	3. check for a BF that is out of spec
	4. figure out what type of rotation is needed
	5. correct with necessar rotation type 
	*/

	insertIndex = _insert(in_key); 
	_updateBalanceFactors(); 
	std::cout << "rootBF = " << rootNode->BF << "\n"; 
 	_checkForImbalance(); 

}

void AVL::HeightOfRoot()
{
	std::cout << _calculateBalanceFactor(rootNode); 
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

						//BF should be 0 since is is a leaf when inserted
						newNode.BF = 0; 
						//newNode.keyWeight = _calculateKeyWeight(in_key); 
						newNode.parent = currentNode;
						newNode.leftChild = nullptr; 
						newNode.rightChild = nullptr;
						
						//set the new node key 
						strcpy(newNode.key, in_key);

						//store the new node
						nodeStorage[nodeStorage_index] = newNode;
						currentNode->rightChild = &nodeStorage[nodeStorage_index];
						nodeStorage_index++;

						//return the index in node storage where the new node was inserted
						return (nodeStorage_index - 1); 
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
						AVL_Node newNode;
						newNode.counter = 1; 
						newNode.BF = 0; 
						newNode.parent = currentNode;
						newNode.leftChild = nullptr; 
						newNode.rightChild = nullptr; 

						//set the newNode key
						strcpy(newNode.key, in_key);

						//copy the node to memory 
						nodeStorage[nodeStorage_index] = newNode;
						currentNode->leftChild = &nodeStorage[nodeStorage_index];
						nodeStorage_index++;

						//return the index in node storage where the new node was inserted
						return (nodeStorage_index - 1); 

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

			//return 0 since it is the root and should be the first node put into the node storage array
			return 0; 
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
			numOfComparisons++; 
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
	newNode.leftChild = nullptr; 
	newNode.rightChild = nullptr; 
	//might not need this in the end 
	newNode.parent = nullptr; 

	//copy key over 
	strcpy(newNode.key, input);

	//store node into memory 
	nodeStorage[nodeStorage_index] = newNode;
	rootNode = &nodeStorage[nodeStorage_index]; 
	nodeStorage_index++;
}


void AVL::_updateBalanceFactors()
{
	//start from the root node and calculate the new balance factors 
	//look for the BFs that change and set that as focus and work down 
	int prevBF; 
	bool complete = false;
	AVL_Node* currentNode; 
	currentNode = rootNode; 

	do
	{
		prevBF = currentNode->BF; 
		currentNode->BF = _calculateBalanceFactor(currentNode); 
		if (currentNode->BF < prevBF)
		{
			//insert occured in right subtree, follow this down 
			if (currentNode->rightChild != nullptr)
			{
				currentNode = currentNode->rightChild;
			}
			else complete = true; 
		}
		else if (currentNode->BF > prevBF)
		{
			//insert occured in left subtree, follw this down 
			if (currentNode->leftChild != nullptr)
			{
				currentNode = currentNode->leftChild;
			}
			else complete = true;
		}
		else
		{
			//no change
			complete = true; 
		}

	} while (complete == false);
}

void AVL::_checkForImbalance()
{
	AVL_Node* focusNode; 
	focusNode = rootNode; 
	//start check from rootnode 
	bool done = false; 
	if ((rootNode->BF >= 2) || (rootNode->BF <= -2))
	{
		do
		{
			if (focusNode->BF >= 2)
			{
				//node is out of balance need to figure out what type of rotation to do 
				//left Subtree to big 
				if ((focusNode->leftChild->BF < 2) && (focusNode->leftChild->BF > -2))
				{
					//the focusNode now is the highest ancestor where the roatation needs to occur
					cout << focusNode->key << "\n";
					done = true; 
				}
				else focusNode = focusNode->leftChild;
			}
			else if (focusNode->BF <= -2)
			{
				//need to rebalance the subtrees 
				//right subtree to big 
				if ((focusNode->rightChild->BF < 2) && (focusNode->rightChild->BF > -2))
				{
					//the focusNode now is the highest ancestor where the roatation needs to occur
					cout << focusNode->key << "\n"; 
					done = true; 
				}
				else focusNode = focusNode->rightChild;
			}
		} while (done == false); 
	}
	std::cout << "Completed Check \n";
}

int AVL::_calculateBalanceFactor(AVL_Node* tippingNode)
{
	int rightHeight, leftHeight; 
	if (tippingNode->rightChild != nullptr)
	{
		rightHeight = (_getNodeHeight(tippingNode->rightChild) + 1);
	}
	else rightHeight = 0; 
	 
	if (tippingNode->leftChild != nullptr)
	{
		leftHeight = (_getNodeHeight(tippingNode->leftChild) + 1);
	}
	else leftHeight = 0; 
	 
	return (leftHeight - rightHeight); 
}

int AVL::_getNodeHeight(AVL_Node* focusNode)
{
	int ret1, ret2; 
	//calculate the height of the node 
	if ((focusNode->rightChild == nullptr) && (focusNode->leftChild == nullptr))
	{
		return 0;
	}
	else
	{
		if (focusNode->rightChild != nullptr)
		{
			ret1 = _getNodeHeight(focusNode->rightChild);
		}
		else ret1 = 0; 

		if (focusNode->leftChild != nullptr)
		{
			ret2 = _getNodeHeight(focusNode->leftChild);
		}
		else ret2 = 0; 
		

		if (ret1 > ret2)
		{
			return (ret1 + 1);
		}
		else
		{
			return (ret2 + 1);
		}
	}
}