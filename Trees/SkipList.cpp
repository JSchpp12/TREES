#include "pch.h"
#include "SkipList.h"
#include <string.h>
#include <random>
#include <iostream>
#include <ctime>

SkipList::SkipList()
{
	//create the most negative node and insert it as the bottom left node 

	//might change this to null, this is 50 extra cycles that I might not need to waste with this initialization 

	skipNode newNode;
	for (int i = 0; i < 50; i++)
	{
		newNode.key[i] = '0'; 
	}
	newNode.level = 0; 

	newNode.rightNode = nullptr; 
	newNode.leftNode = nullptr; 
	newNode.upNode = nullptr; 
	newNode.downNode = nullptr; 

	nodeStorage[nodeStorage_index] = newNode; 
	bottomLeftNode = &nodeStorage[nodeStorage_index]; 
	topLeftNode = &nodeStorage[nodeStorage_index]; 
	leftNodes[NumOflevels] = &nodeStorage[nodeStorage_index]; 
	nodeStorage_index++; 

	//seed random generator 
	srand(std::time(0));
}

void SkipList::Insert(char in_key[])
{
	std::cout << "skip list insert \n"; 
	_insert(in_key); 
}

int SkipList::List()
{
	return _traverse(); 
}

void SkipList::GetInfo()
{
	_traverse(); 
	std::cout << "Skip List Info...\n"; 
	std::cout << "Number of Items: " << _traverse() << "\n"; 
	std::cout << "Number of Nodes in List: " << nodeStorage_index << "\n"; 
	std::cout << "Number of Pointer Changes: " << numOfPointerChange << "\n"; 
	std::cout << "Number of Comparisons: " << numOfComparisons << "\n"; 
}

void SkipList::_insert(char in_key[])
{
	bool complete = false; 
	bool makeNewNode = true; 
	int searchRow = topLeftNode->level; 

	skipNode *leaderNode = topLeftNode; 
	skipNode *laggerNode = topLeftNode; 
	skipNode *lastPathDown = topLeftNode; 

	skipNode *currentNode = bottomLeftNode; 
	skipNode *searchNode = topLeftNode; 


	while (searchRow != 0)
	{
		while (strcmp(in_key, leaderNode->key) > 0)
		{
			numOfComparisons++; 

			if (leaderNode->downNode != nullptr)
			{
				lastPathDown = leaderNode;
			}
			if (leaderNode->rightNode != nullptr)
			{
				leaderNode = leaderNode->rightNode;
			}
			else break;
		}
		leaderNode = lastPathDown->downNode;
		searchRow--;
	}

	//search bottom layer for the new node's place 
	while (strcmp(in_key, leaderNode->key) > 0)
	{
		numOfComparisons++;

		if (leaderNode->rightNode != nullptr)
		{
			laggerNode = leaderNode;
			leaderNode = leaderNode->rightNode;
		}
		else if (strcmp(in_key, leaderNode->key) == 0)
		{
			_increaseCounters(leaderNode);
			makeNewNode = false;
		}
		else
		{
			//reached end of the list 
			laggerNode = leaderNode;
			leaderNode = nullptr;
			break;
		}
	}

	if (makeNewNode == true) _createNewNode(laggerNode, leaderNode, in_key); 
}

void SkipList::_createNewNode(skipNode *leftNode, skipNode *rightNode, char in_key[])
{
	skipNode newNode, *newNodePointer;
	skipNode *highestCopy = nullptr; 

	//if this new node is copied up a row, this will be set to true 
	bool upperCreated = false; 
	int level = 0; 

	//newNode should be created in the bottom layer first 
	newNode.downNode = nullptr;
	newNode.upNode = nullptr; 
	newNode.leftNode = leftNode; 
	newNode.rightNode = rightNode; 
	
	//copy key to node key 
	strcpy(newNode.key, in_key); 

	//store new node in memory 
	nodeStorage[nodeStorage_index] = newNode; 
	newNodePointer = &nodeStorage[nodeStorage_index];
	leftNode->rightNode = &nodeStorage[nodeStorage_index];
	if (rightNode != nullptr) rightNode->leftNode = &nodeStorage[nodeStorage_index]; 

	nodeStorage_index++; 
	
	
	//the following will create and link copy nodes above the new node 
	while (_random() == true)
	{
		numOfCopies++;

		skipNode upNode; 
		skipNode *leaderNode = nullptr; 
		skipNode *laggerNode = nullptr; 
		skipNode *nodeSlider = nullptr; 

		level++; 

		//check if need a new level -- create the lowest node in the level
		if (level > NumOflevels)
		{
			//create the lowest left node 
			int lowerLevel = level - 1; 
			skipNode nextMaxNode; 

			//remove this if the most negative node is changed to null
			strcpy(nextMaxNode.key, bottomLeftNode->key); 

			//set the level of the new node
			nextMaxNode.level = level; 

			nextMaxNode.downNode = leftNodes[lowerLevel]; 
			nextMaxNode.rightNode = nullptr; 
			nextMaxNode.leftNode = nullptr; 
			nextMaxNode.upNode = nullptr; 
			
			nodeStorage[nodeStorage_index] = nextMaxNode; 
			
			leftNodes[lowerLevel]->upNode = &nodeStorage[nodeStorage_index];
			nodeStorage[nodeStorage_index].downNode = leftNodes[lowerLevel];
			numOfPointerChange = numOfPointerChange + 2; 

			leftNodes[level] = &nodeStorage[nodeStorage_index]; 
			topLeftNode = leftNodes[level]; 
			nodeStorage_index++; 
			//increase the number of levels in the class
			NumOflevels++; 
		}

		leaderNode = leftNodes[level]; 
		
		//find place in height where the new copy should go -- get left and right pointers for new node
		while (strcmp(in_key, leaderNode->key) > 0)
		{
			numOfComparisons++; 

			if (leaderNode->rightNode != nullptr)
			{
				laggerNode = leaderNode;
				leaderNode = leaderNode->rightNode;
			}
			else
			{
				//reached end of the list 
				laggerNode = leaderNode;
				leaderNode = nullptr;
				break;
			}
		}

		upNode.level = level; 
		strcpy(upNode.key, in_key);
		if (laggerNode != nullptr) upNode.leftNode = laggerNode; 
		else upNode.leftNode = leftNodes[level]; 
		numOfPointerChange++; 

		if (leaderNode != nullptr)
		{
			numOfPointerChange++; 
			upNode.rightNode = leaderNode;
		}
		else upNode.rightNode = nullptr; 

		upNode.upNode = nullptr; 

		if (highestCopy != nullptr) upNode.downNode = highestCopy;
		else upNode.downNode = newNodePointer; 
		numOfPointerChange++; 

		nodeStorage[nodeStorage_index] = upNode;

		//set pointers of nodes around nextHighest to respect nextHighest 
		if (highestCopy != nullptr) highestCopy->upNode = &nodeStorage[nodeStorage_index];

		if (nodeStorage[nodeStorage_index].rightNode != nullptr)
		{
			nodeStorage[nodeStorage_index].rightNode->leftNode = &nodeStorage[nodeStorage_index];
			numOfPointerChange++; 
		}
		//left node should never be null pointer, dont need to worry about it 
		nodeStorage[nodeStorage_index].leftNode->rightNode = &nodeStorage[nodeStorage_index]; 
		numOfPointerChange++; 

		highestCopy = &nodeStorage[nodeStorage_index]; 
		nodeStorage_index++; 
	}

}

bool SkipList::_random()
{
	//should be a 50/50 chance of returning true -- dont think this is what I want, gives the same series each time 
	bool result = true; 

	if ((rand() % 2) == 1) result = false; 

	return result; 
}

int SkipList::_traverse()
{
	int numOfItems = 0; 
	skipNode *currentNode, *farLeftNode; 
	char empty[50]; 
	
	if (topLeftNode != nullptr)
	{
		currentNode = topLeftNode; 

		for (int i = NumOflevels; i >= 0; i--)
		{
			currentNode = leftNodes[i]; 
			std::cout << "Level : " << i << "\n"; 

			while (currentNode!= nullptr)
			{
				if (currentNode != leftNodes[i])
				{
					numOfItems++; 
					std::cout << currentNode->key << " , ";
				}
				currentNode = currentNode->rightNode;
			} 
			std::cout << "\n"; 
		}
	}
	else std::cout << "Empty"; 
	return numOfItems; 
}

void SkipList::_increaseCounters(skipNode *targetNode)
{
	do
	{
		targetNode->counter++; 
		if (targetNode->upNode != nullptr) targetNode = targetNode->upNode; 

	} while (targetNode->upNode != nullptr);
}