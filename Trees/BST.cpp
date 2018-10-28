#include "pch.h"
#include "BST.h"



BST::BST()
{
}

void BST::Insert(char in_key[])
{
	int in_weight = 0; 
	bool cont = false;
	bool done = false;
	bool found;
	Node* currentNode;

	//calculate the weight of the in_key 
	in_weight = _calculateKeyWeight(in_key); 

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
				if (in_weight > currentNode->keyWeight)
				{
					if (currentNode->rightChild == nullptr)
					{
						//this is empty spot
						Node newNode; 
						newNode.counter = 1; 
						newNode.keyWeight = _calculateKeyWeight(in_key); 
						newNode.parent = currentNode; 

						//set the key in the node 
						_setNodeKey(&newNode, in_key); 

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
				else if (in_weight < currentNode->keyWeight)
				{
					if (currentNode->leftChild == nullptr)
					{
						//this is an empty spot
						//Node newNode(in_key, currentNode);

						//CREATE A NEW NODE-----------------------------

						Node newNode; 
						//copy the key over 
						newNode.counter = 1; 
						newNode.keyWeight = _calculateKeyWeight(in_key); 
						newNode.parent = currentNode; 

						//set the key in the node
						_setNodeKey(&newNode, in_key); 

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

void BST::_createRoot(char input[])
{
	int counter = 0;
	
	Node newNode;
	newNode.counter = 1;
	
	//copy the values in the input into the node 
	_setNodeKey(&newNode, input); 

	//calculate the key weight for the node 
	newNode.keyWeight = _calculateKeyWeight(input); 

	//store node into memory 
	nodeStorage[nodeStorage_index] = newNode;
	nodeStorage_index++;
}

bool BST::_search(char in_key[], bool call_internal, bool call_delete)
{
	int charWeight; 
	int in_weight = 0;
	int counter = 0;
	bool found = false; 
	bool done = false; 
	Node* currentNode; 

	//calculate the weight of the string contained in the character array (INPUT)
	charWeight = _calculateKeyWeight(in_key); 

	//look for the correct node 
	if (rootNode != nullptr)
	{
		currentNode = rootNode;
		while (done == false)
		{
			if (currentNode)
			{
				if (currentNode->keyWeight == in_weight)
				{
					
					//found node with same weight
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
				else if (in_weight > currentNode->keyWeight)
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
				else if (in_weight < currentNode->keyWeight)
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

int BST::_calculateKeyWeight(char in_key[])
{
	int counter = 0; 
	int temp = 0; 
	int in_weight = 0;

	while ((in_key[counter] != -52) && (counter <= 50))
	{
		temp = in_key[counter]; 
		in_weight = in_weight + temp; 
		counter++; 
	}

	return in_weight; 
}

void BST::_setNodeKey(Node* currentNode, char in_key[])
{
	//this will copy the char array to the node 
	int counter = 0; 

	while ((in_key[counter] != -52) && (counter <= 50))
	{
		currentNode->key[counter] = in_key[counter]; 
		counter++; 
	}
}