#include "pch.h"
#include "SkipList.h"
#include <string.h>

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
	leftNodes[NumOflevels] = &nodeStorage[nodeStorage_index]; 
	nodeStorage_index++; 

}

void SkipList::Insert(char in_key[])
{
	_insert(in_key); 
}

void SkipList::_insert(char in_key[])
{
	skipNode *currentNode = bottomLeftNode; 
	while (strcmp(in_key, currentNode->key) > 0 )
	{
		if (currentNode->rightNode != nullptr) currentNode = currentNode->rightNode; 
		else break; 
	}
	//will exit when the in_key is larger than the next node in the list 


}

void SkipList::_createNewNode(skipNode *leftNode, skipNode *rightNode, char in_key[])
{
	skipNode newNode, *newNodePointer, *highestCopy; 

	//if this new node is copied up a row, this will be set to true 
	bool upperCreated = false; 
	int level = 0; 

	//newNode should be created in the bottom layer first 
	newNode.downNode = nullptr; 
	newNode.leftNode = leftNode; 
	newNode.rightNode = rightNode; 

	strcpy(newNode.key, in_key); 

	//store new node in memory 
	nodeStorage[nodeStorage_index] = newNode; 
	newNodePointer = &nodeStorage[nodeStorage_index]; 
	nodeStorage_index++; 
	
	//copy the key over 
	strcpy(newNode.key, in_key);

	//the following will create and link copy nodes above the new node 
	while (_random() == true)
	{
		skipNode upNode, *leaderNode, *laggerNode; 
		skipNode *nodeSlider = nullptr; 

		level++; 

		//check if need a new level -- create the lowest node in the level
		if (level > NumOflevels)
		{
			//create the lowest left node 
			int lowerLevel = NumOflevels - 1; 
			skipNode nextMaxNode; 

			//remove this if the most negative node is changed to null
			strcmp(nextMaxNode.key, bottomLeftNode->key); 

			//set the level of the new node big tits and small niggas
			nextMaxNode.level = level; 

			nextMaxNode.downNode = leftNodes[lowerLevel]; 
			nextMaxNode.rightNode = nullptr; 
			nextMaxNode.leftNode = nullptr; 
			nextMaxNode.upNode = nullptr; 
			
			nodeStorage[nodeStorage_index] = nextMaxNode; 
			
			leftNodes[lowerLevel]->upNode = &nodeStorage[nodeStorage_index];
			nodeStorage[nodeStorage_index].downNode = leftNodes[lowerLevel];
			leftNodes[NumOflevels] = &nodeStorage[nodeStorage_index]; 
			nodeStorage_index++; 
			//increase the number of levels in the class
			NumOflevels++; 
		}

		leaderNode = leftNodes[level]; 
		
		//look for where upper level copy will go in list 
		while (strcmp(in_key, leaderNode->key) > 0)
		{
			laggerNode = leaderNode; 
			leaderNode = leaderNode->rightNode; 
		}
		//when this while exits, the laggerNode will contain the left node, and the leftSearchNode will be the right node
		
		strcpy(upNode.key, in_key);
		upNode.leftNode = laggerNode; 
		upNode.rightNode = leaderNode;
		upNode.upNode = nullptr; 
		
		/*
		//go up from the newNode to the level below new copy level to get pointer to downNode
		nodeSlider = newNodePointer; 
		for (int j = 0; j < NumOflevels; j++)
		{
			nodeSlider = nodeSlider->upNode; 
		}
		//upNode.downNode = nodeSlider;
		*/

		if (highestCopy != nullptr) upNode.downNode = highestCopy;
		else upNode.downNode = newNodePointer; 

		nodeStorage[nodeStorage_index] = upNode; 
		highestCopy->upNode = &nodeStorage[nodeStorage_index]; 
		highestCopy = &nodeStorage[nodeStorage_index]; 
		nodeStorage_index++; 
	}
}

bool SkipList::_random()
{

}