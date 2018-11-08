//BST.cpp
//Jacob Schaupp
//EECS 2510, Fall 2018
//11/7/2018
//Contains logic for the BST data structure 

#include "pch.h"
#include "BST.h"

BST::BST()
{
}

void BST::List()
{
	_traverse(rootNode); 
}

void BST::GetTreeInfo()
{
	_traverse(rootNode); 
	
	std::cout << "Binary Search Tree Info...\n"; 
	std::cout << "Number of Comparisons: " << numOfComparisons << "\n"; 
	std::cout << "Number of Items: " << numOfItems << "\n"; 
}

void BST::Insert(char in_key[])
{
	int in_weight = 0; 
	bool cont = false;
	bool done = false;
	bool found;
	Node* currentNode;

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
						Node newNode; 
						newNode.counter = 1; 
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

						Node newNode; 
						newNode.counter = 1; 
						newNode.parent = currentNode; 
						newNode.rightChild = nullptr; 
						newNode.leftChild = nullptr; 

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
				else
				{
					currentNode->counter++;
					done = true; 
				}
			}
		
		}
		else
		{
			this->_createRoot(in_key);
		}
	}
}

void BST::_createRoot(char input[])
{
	int counter = 0;
	
	Node newNode;
	newNode.counter = 1;

	strcpy(newNode.key, input); 

	newNode.rightChild = nullptr; 
	newNode.leftChild = nullptr; 

	//store node into memory 
	nodeStorage[nodeStorage_index] = newNode;
	rootNode = &nodeStorage[nodeStorage_index]; 

	nodeStorage_index++;

}

bool BST::_search(char in_key[], bool call_internal, bool call_delete)
{
	int in_weight = 0;
	int counter = 0;
	bool found = false; 
	bool done = false; 
	Node* currentNode; 

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
			else
			{
				//Hopefully never hit this 
				std::cout << "Unknown Error! \n";
			}
		}
	}
	return found;
}

void BST::_traverse(Node* in_node)
{
	if (in_node != nullptr)
	{
		numOfItems = numOfItems + in_node->counter;
		_traverse(in_node->leftChild);
		//std::cout << in_node->key << " " << in_node->counter << "\n";
		_traverse(in_node->rightChild);
	}
	else
	{
		return;
	}
}