#include "pch.h"
#include "RBT.h"
#include <string.h>
#include <iostream>

RBT::RBT()
{
	/*
	RBT_Node newNode;
	newNode.color = 2;
	t_nil = newNode;
	*/
}

void RBT::Insert(char in_key[])
{
	_insert(in_key);
}

void RBT::print()
{
	std::cout << "wow\n";
}

void RBT::_insert(char in_key[])
{
	int in_weight = 0;
	bool cont = false;
	bool done = false;
	bool found;
	RBT_Node* currentNode;

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
						RBT_Node newNode;
						newNode.counter = 1;
						//newNode.keyWeight = _calculateKeyWeight(in_key); 
						newNode.parent = currentNode;
						newNode.leftChild = nullptr;
						newNode.rightChild = nullptr;

						//new nodes inserted must be RED
						newNode.color = 1;

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

						RBT_Node newNode;
						newNode.counter = 1;
						newNode.parent = currentNode;
						newNode.rightChild = nullptr;
						newNode.leftChild = nullptr;

						//new nodes color = RED
						newNode.color = 1;
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
	//run checks on the nodes for necessary corrections 
	_checkForError(nodeStorage_index--);
}

bool RBT::_search(char in_key[], bool call_internal, bool call_delete)
{
	int in_weight = 0;
	int counter = 0;
	bool found = false;
	bool done = false;
	RBT_Node* currentNode;

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

void RBT::_createRoot(char in_key[])
{
	int counter = 0;

	RBT_Node newNode;
	newNode.counter = 1;

	strcpy(newNode.key, in_key);

	//root node should be BLACK
	newNode.color = 2;
	newNode.rightChild = nullptr;
	newNode.leftChild = nullptr;

	//store node into memory 
	nodeStorage[nodeStorage_index] = newNode;
	rootNode = &nodeStorage[nodeStorage_index];

	nodeStorage_index++;
}

void RBT::_checkForError(int memoryIndex)
{
	//pass in the index newly inserted node in the tree to check the conditions
	bool complete = false;

	RBT_Node* insertedNode, *parentNode, *uncleNode, *grandparentNode;
	insertedNode = &nodeStorage[memoryIndex];

	do
	{
		if (insertedNode->parent != nullptr)
		{
			if ((insertedNode->parent->color != 2) || (insertedNode != rootNode))
			{
				//set up nodes needed for the cases 
				parentNode = insertedNode->parent;
				grandparentNode = parentNode->parent;

				if (parentNode == grandparentNode->rightChild)
				{
					uncleNode = grandparentNode->leftChild;
				}
				else uncleNode = grandparentNode->rightChild;

				if (uncleNode->color == 1)
				{
					//RED -- change color and move up 
					parentNode->color = 2;
					uncleNode->color = 2;
					grandparentNode->color = 1;

					//move the focus up to the grandparent and run again
					insertedNode = grandparentNode;

				}
				else
				{
					//BLACK
					//do rotation and then complete 
					if (parentNode == grandparentNode->leftChild)
					{
						if (insertedNode == parentNode->leftChild)
						{
							//Left Left Case 
							//LL rotate around G
							//swap colors of g and p 
							LL_rotate(grandparentNode);
						}
						else
						{
							//Left Right Case 

						}
					}
					else
					{
						if (insertedNode == parentNode->leftChild)
						{
							//RR case aroung G 
							RR_rotate(grandparentNode);

						}
						else
						{

						}
					}
					complete = true;
				}
			}
			else complete = true;
		}
		else complete = true; 
	} while (complete == false);
	/*
	if (insertedNode != rootNode)
	{
		parentNode = insertedNode->parent;
		if (parentNode->color != 2)
		{
			grandparentNode = parentNode->parent;

			if (parentNode == grandparentNode->rightChild)
			{
				uncleNode = grandparentNode->leftChild;
			}
			else uncleNode = grandparentNode->rightChild;

			if (uncleNode->color == 1)
			{
				//Uncle is RED
				do
				{
					parentNode->color = 2;
					uncleNode->color = 2;
				} while (complete == false);
			}
			else
			{
				//Uncle is BLACK
				//get configuration and use the rotations from AVL

			}
		}
	}
	*/
}

void RBT::RR_rotate(RBT_Node* correctionCenter)
{
	//these names are in regard to describing the orientation before the rotation
	RBT_Node *middleOfRotation, *treeConnector, *bottomRotation;
	RBT_Node* tempHolder = nullptr;

	int colorHolder;

	//this node will become the root of the subtree after the rotation
	middleOfRotation = correctionCenter->rightChild;

	treeConnector = correctionCenter->parent;

	if (correctionCenter != rootNode)
	{
		if (correctionCenter == treeConnector->rightChild)
		{
			treeConnector->rightChild = middleOfRotation;
			middleOfRotation->parent = treeConnector;
		}
		else
		{
			treeConnector->leftChild = middleOfRotation;
			middleOfRotation->parent = treeConnector;
		}
	}
	else
	{
		//rotation is occuring at the root node 
		rootNode = middleOfRotation;
		middleOfRotation->parent = nullptr;
	}

	//set the correctionCenter as the left child of the new root of the subtree
	if ((middleOfRotation->leftChild != nullptr) && (middleOfRotation->rightChild == nullptr))
	{
		//tempHolder = middleOfRotation->leftChild; 
		middleOfRotation->rightChild = middleOfRotation->leftChild;
	}
	else if ((middleOfRotation->leftChild != nullptr) && (middleOfRotation->rightChild != nullptr))
	{
		tempHolder = middleOfRotation->leftChild;
	}

	middleOfRotation->leftChild = correctionCenter;
	correctionCenter->parent = middleOfRotation;


	//this node is now a leaf 
	//correctionCenter->leftChild = nullptr;
	correctionCenter->rightChild = nullptr;

	if (tempHolder != nullptr)
	{
		middleOfRotation->rightChild->leftChild = tempHolder;
		tempHolder->parent = middleOfRotation->rightChild;
	}
	//rotation should be complete 
}

void RBT::LL_rotate(RBT_Node* correctionCenter)
{
	RBT_Node *middleOfRotation, *treeConnector, *bottomRotation;
	RBT_Node *tempHolder = nullptr;

	//this node will become the root of the subtree after the rotation
	middleOfRotation = correctionCenter->leftChild;

	//this node will be the parent of the root of the subtree after rotation
	treeConnector = correctionCenter->parent;

	if (correctionCenter != rootNode)
	{
		//set the middle node as the root of the subtree
		if (correctionCenter == treeConnector->rightChild)
		{
			treeConnector->rightChild = middleOfRotation;
			middleOfRotation->parent = treeConnector;
		}
		else
		{
			treeConnector->leftChild = middleOfRotation;
			middleOfRotation->parent = treeConnector;
		}

	}
	else
	{
		//rotation is occuring at the root node
		rootNode = middleOfRotation;
		middleOfRotation->parent = nullptr;
	}

	//set the correctionCenter as the right child of the new root of the subtree 
	if ((middleOfRotation->rightChild != nullptr) && (middleOfRotation->leftChild == nullptr))
	{
		middleOfRotation->leftChild = middleOfRotation->rightChild;
	}
	else if ((middleOfRotation->rightChild != nullptr) && (middleOfRotation->leftChild != nullptr))
	{
		tempHolder = middleOfRotation->rightChild;
	}

	middleOfRotation->rightChild = correctionCenter;
	correctionCenter->parent = middleOfRotation;

	if (tempHolder != nullptr)
	{
		//moved saved node into position
		middleOfRotation->leftChild->rightChild = tempHolder;
		tempHolder->parent = middleOfRotation->leftChild;
	}

	//this node is now a leaf
	correctionCenter->leftChild = nullptr;

	//rotation should be complete 
}
