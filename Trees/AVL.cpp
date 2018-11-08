//AVL.cpp
//Jacob Schaupp
//EECS 2510, Fall 2018
//11/7/2018
//Contains logic for the AVL data structure 

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
	if (nodeStorage_index < 10000)
	{
		int insertIndex;
		bool correctionNeeded;
		/*
		1. insert new node
		2. calculate new BFs
		3. check for a BF that is out of spec
		4. figure out what type of rotation is needed
		5. correct with necessary rotation type
		*/
		insertIndex = _insert(in_key);
		_newUpdate(&nodeStorage[nodeStorage_index - 1]);
	}
}

void AVL::GetTreeInfo()
{
	_traverse(rootNode); 
	std::cout << "AVL Tree Info... \n"; 
	std::cout << "Number of Comparisons: " << numOfComparisons << "\n"; 
	std::cout << "Number of Pointer Changes: " << numOfPointerChanges << "\n"; 
	std::cout << "Number of Balance Factor Changes: " << numOfBFChanges << "\n"; 
	std::cout << "Number of Items: " << numOfItems << "\n";
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
	AVL_Node* correctionCenter = nullptr; 

	do
	{
		prevBF = currentNode->BF; 
		currentNode->BF = _calculateBalanceFactor(currentNode); 
		numOfBFChanges++; 

		//check if node's BF needs correction, mark it for correction if so 
		if ((currentNode->BF == -2) || (currentNode->BF == 2)) correctionCenter = currentNode; 

		//if (currentNode->BF < prevBF)
		if (currentNode->BF < 0)
		{
			//insert occured in right subtree, follow this down 
			if (currentNode->rightChild != nullptr)
			{
				currentNode = currentNode->rightChild;
			}
			else complete = true; 
		}
		//else if (currentNode->BF > prevBF)
		else if (currentNode->BF > 0)
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

	//perform rotation on the node that is out of spec
	if (correctionCenter) _rotationHandler(correctionCenter); 
}

bool AVL::_checkForImbalance(char new_key[], AVL_Node* insertedNode)
{
	//this will not work long term, need to pass something in to indicate which subtree to look at after the insertion

	AVL_Node* focusNode, nodeCorrection;
	focusNode = rootNode;
	//start check from rootnode 
	bool done = false;
	bool correctionNeeded = false; 
	bool complete = false; 

	
	//cannot depend on root node being incorrect 
	if ((rootNode->BF >= 2) || (rootNode->BF <= -2))
	{
		do
		{
			if (focusNode->BF >= 2)
			{
				//node is out of balance need to figure out what type of rotation to do 
				//left Subtree to big 
				if ((focusNode->leftChild->BF < 2) && (focusNode->leftChild->BF >-2))
				{
					//the focusNode now is the highest ancestor where the roatation needs to occur
					//cout << focusNode->key << "\n";
					_rotationHandler(focusNode); 
					done = true;
					correctionNeeded = true; 
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
					_rotationHandler(focusNode);
					//cout << focusNode->key << "\n";
					done = true;
					correctionNeeded = true; 
				}
				else focusNode = focusNode->rightChild;
			}
		} while (done == false);
	}
	return correctionNeeded; 
}

void AVL::_rotationHandler(AVL_Node* correctionCenter)
{
	//correctionCenter will be the lowest node with a BF that is out of spec and requires rotation to correct 

	//insertionSide: 
	//1 - left 
	//2 - right

	int temp = nodeStorage_index - 1;
	AVL_Node *insertedNode = &nodeStorage[temp];
	AVL_Node *grandparentNode = nullptr;
	AVL_Node *loopNode = nullptr;

	char tempContainer[50];
	int direction1 = 0;
	int direction2 = 0;

	if (correctionCenter->BF >= 2)
	{
		//left subtree too big 
		if (correctionCenter->leftChild->BF > 0)
		{
			//inserted node was in the left subtree of the left node LL
			LL_rotate(correctionCenter); 
		}
		else
		{
			//LR 
			LR_rotate(correctionCenter);
		}
	}
	else
	{
		if (correctionCenter->rightChild->BF > 0)
		{
			//left subtree of right node RL 
			RL_rotate(correctionCenter);
		}
		else
		{
			//RR rotate, should be 
			RR_rotate(correctionCenter); 
		}
	}
}

//IN RR ROTATION -------------------------------------------------------
//Made a new thing that copies the right child of the middle node to be moved after the rotation per the rotation method 
//NEED DYNAMIC MEMORY ALLOCATION RATHER THAN THE ARRAY ACCORDING TO DR>SHIT 

void AVL::RR_rotate(AVL_Node* correctionCenter)
{
	//these names are in regard to describing the orientation before the rotation
	AVL_Node *middleOfRotation, *bottomRotation; 
	AVL_Node* tempHolder = nullptr;
	AVL_Node *treeConnector = nullptr; 

	//this node will become the root of the subtree after the rotation
	if (correctionCenter->rightChild) middleOfRotation = correctionCenter->rightChild;
	else middleOfRotation = correctionCenter->leftChild; 
	
	//this node will be the parent of the root of the subtree after rotation -- will be right child of the treeConnector 
	
	treeConnector = correctionCenter->parent;

	if (correctionCenter != rootNode)
	{
		if (correctionCenter == treeConnector->rightChild)
		{
			treeConnector->rightChild = middleOfRotation;
			middleOfRotation->parent = treeConnector;
			//increment counter 
			numOfPointerChanges = numOfPointerChanges + 2; 
		}
		else
		{
			treeConnector->leftChild = middleOfRotation;
			middleOfRotation->parent = treeConnector;
			//increment counter 
			numOfPointerChanges = numOfPointerChanges + 2;
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
		numOfPointerChanges++; 
	}
	else if ((middleOfRotation->leftChild != nullptr) && (middleOfRotation->rightChild != nullptr))
	{
		tempHolder = middleOfRotation->leftChild; 
	}

	middleOfRotation->leftChild = correctionCenter;
	correctionCenter->parent = middleOfRotation;
	numOfPointerChanges = numOfPointerChanges + 2;

	//this node is now a leaf 
	//correctionCenter->leftChild = nullptr;
	correctionCenter->rightChild = nullptr;
	numOfPointerChanges++; 

	if (tempHolder != nullptr)
	{
		middleOfRotation->rightChild->leftChild = tempHolder; 
		tempHolder->parent = middleOfRotation->rightChild; 
		numOfPointerChanges++; 
	}
	//rotation should be complete 
	//_updateBalanceFactors(); 
	//_newUpdate(rootNode);

	//correctionCenter->BF = _calculateBalanceFactor(correctionCenter);
	//middleOfRotation->BF = _calculateBalanceFactor(middleOfRotation);
	//if (treeConnector)_newUpdate(treeConnector);
}

void AVL::LL_rotate(AVL_Node* correctionCenter)
{
	AVL_Node *middleOfRotation, *bottomRotation;
	AVL_Node *tempHolder = nullptr;
	AVL_Node *treeConnector = nullptr; 

	AVL_Node *middleOfRotation_RightSubtree = nullptr; 

	//this node will become the root of the subtree after the rotation
	middleOfRotation = correctionCenter->leftChild;
	//if (middleOfRotation->rightChild) middleOfRotation_RightSubtree = middleOfRotation->rightChild; 

	//this node will be the parent of the root of the subtree after rotation
	treeConnector = correctionCenter->parent;

	if (correctionCenter != rootNode)
	{
		//set the middle node as the root of the subtree
		if (correctionCenter == treeConnector->rightChild)
		{
			treeConnector->rightChild = middleOfRotation;
			middleOfRotation->parent = treeConnector;
			numOfPointerChanges = numOfPointerChanges + 2;
		}
		else
		{
			treeConnector->leftChild = middleOfRotation;
			middleOfRotation->parent = treeConnector;
			numOfPointerChanges = numOfPointerChanges + 2;
		}
	}
	else
	{
		//rotation is occuring at the root node
		rootNode = middleOfRotation;
		middleOfRotation->parent = nullptr;
		numOfPointerChanges = numOfPointerChanges + 2;
	}

	//set the correctionCenter as the right child of the new root of the subtree 
	if ((middleOfRotation->rightChild != nullptr) && (middleOfRotation->leftChild == nullptr))
	{
		middleOfRotation->leftChild = middleOfRotation->rightChild;
		numOfPointerChanges++; 
	}
	else if ((middleOfRotation->rightChild != nullptr) && (middleOfRotation->leftChild != nullptr))
	{
		tempHolder = middleOfRotation->rightChild;
	}

	middleOfRotation->rightChild = correctionCenter;
	correctionCenter->parent = middleOfRotation;
	numOfPointerChanges = numOfPointerChanges + 2;

	if (tempHolder != nullptr)
	{
		//moved saved node into position
		middleOfRotation->leftChild->rightChild = tempHolder;
		tempHolder->parent = middleOfRotation->leftChild;
		numOfPointerChanges = numOfPointerChanges + 2;
	}

	//copy the nodes across to new location on other side of tree
	
	if (middleOfRotation_RightSubtree)
	{
		if (middleOfRotation_RightSubtree->leftChild)middleOfRotation_RightSubtree->leftChild = nullptr;

		correctionCenter->leftChild = middleOfRotation_RightSubtree;
		middleOfRotation_RightSubtree->parent = correctionCenter->leftChild; 
	}
	   
	//this node is now a leaf
	correctionCenter->leftChild = nullptr;
	//correctionCenter->rightChild = nullptr; 
	//correctionCenter->BF = 0; 

	//rotation should be complete 
	//_updateBalanceFactors();
	//correctionCenter->BF = _calculateBalanceFactor(correctionCenter);
	//middleOfRotation->BF = _calculateBalanceFactor(middleOfRotation);
	//if (treeConnector)_newUpdate(treeConnector);
}

void AVL::LR_rotate(AVL_Node *correctionCenter)
{
	//apply RR rotation on nodes below correction center 
	//thenn LL on resulting tree 

	RR_rotate(correctionCenter->leftChild); 
	LL_rotate(correctionCenter); 
}

void AVL::RL_rotate(AVL_Node *correctionCenter)
{
	LL_rotate(correctionCenter->rightChild); 
	RR_rotate(correctionCenter); 
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
	 
	_getNodeHeight(tippingNode); 
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

void AVL::_clearChildrenPointers(AVL_Node* targetNode)
{
	targetNode->rightChild = nullptr; 
	targetNode->leftChild = nullptr; 
}

void AVL::_traverse(AVL_Node* in_node)
{
	if (in_node != nullptr)
	{
		numOfItems = numOfItems + in_node->counter;
		_traverse(in_node->leftChild);
		_traverse(in_node->rightChild);
	}
	else
	{
		return;
	}
}

void AVL::_newUpdate(AVL_Node* in_node)
{
	//update BFs using traverse idea 

	bool complete = false; 
	AVL_Node* correctionCenter = nullptr; 

	do
	{
		//start at inserted node and work up to root to calculate new BFs
		in_node->BF = _calculateBalanceFactor(in_node);
		numOfBFChanges++; 

		if ((in_node->BF == 2) || (in_node->BF == -2))
		{
			//this is node where rotation needs to occur
			if (!correctionCenter) correctionCenter = in_node; 
		}

		if (in_node == rootNode) complete = true; 
		else in_node = in_node->parent;  

	} while (complete == false);

	if (correctionCenter)
	{
		_rotationHandler(correctionCenter);
	}
}