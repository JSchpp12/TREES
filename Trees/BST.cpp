//Jacob Schaupp 
//EECS 2510 Non Linear 
//09-28-2018

#include "pch.h"
#include "BST.h"

BST::BST()
{
}


BST::~BST()
{
}

//public methods 
void BST::Insert(string in_key)
{
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
				if (in_key > currentNode->key)
				{
					if (currentNode->rightChild == nullptr)
					{
						//this is empty spot
						Node newNode(in_key, currentNode);

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
				else if (in_key < currentNode->key)
				{
					if (currentNode->leftChild == nullptr)
					{
						//this is an empty spot
						Node newNode(in_key, currentNode);

						//store new node in array 
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

void BST::List()
{
	if (rootNode != nullptr)
	{
		_traverse(rootNode);
	}
	else
	{
		cout << "Tree is Empty";
	}
}

void BST::Search(string in_key)
{
	_search(in_key, false, false);
}

void BST::Delete(string in_key)
{
	bool returned;
	returned = _search(in_key, false, true);
}

void BST::Minimum()
{
	_getRange(false);
}

void BST::Maximum()
{
	_getRange(true);
}

void BST::Next(string in_key)
{
	Node* currentNode;
	Node* parentNode;
	currentNode = _getNode(in_key);

	if (currentNode != nullptr)
	{
		if (currentNode->rightChild != nullptr)
		{
			currentNode = currentNode->rightChild;

			while (currentNode->leftChild != nullptr)
			{
				currentNode = currentNode->leftChild;
			}
			//currentNode will be successor once loop in complete 
			cout << currentNode->key << "\n";
		}
		else if (currentNode->rightChild == nullptr)
		{
			while ((currentNode->rightChild == nullptr) or (currentNode != rootNode))
			{
				currentNode = currentNode->parent;
			}
			while (currentNode->leftChild != nullptr)
			{
				currentNode = currentNode->leftChild;
			}
			//after these loops, the successor will be the currentNode
			cout << currentNode->key << "\n";
		}
	}
	else
	{
		cout << "Tree is empty \n";
	}
}

void BST::Previous(string in_key)
{
	bool done = false;
	Node* currentNode;
	if (rootNode != nullptr)
	{
		currentNode = _getNode(in_key);

		if (currentNode != nullptr)
		{
			if (currentNode->leftChild != nullptr)
			{
				currentNode = currentNode->leftChild;

				while (currentNode->rightChild != nullptr)
				{
					currentNode = currentNode->rightChild;
				}
				//currentNode will be the predacessor 
				cout << currentNode->key << "\n";
			}
			else if (currentNode->leftChild == nullptr)
			{
				//want it to stop climbing at the root node or when it finds a path with a left child 
				while ((currentNode->leftChild == nullptr) and (currentNode != rootNode))
				{
					currentNode = currentNode->parent;
				}
				while (currentNode->rightChild != nullptr)
				{
					currentNode = currentNode->rightChild;
				}
				cout << currentNode->key << "\n";
			}
		}
		else
		{
			cout << "Tree is empty \n";
		}
	}
	else
	{
		cout << "Tree is empty \n";
	}
}


//private methods 
void BST::_createRoot(string input)
{
	cout << "creating root node" << input;
	this->rootNode = new Node(input);
}

bool BST::_search(string in_key, bool call_internal, bool call_delete)
{
	//cout << "Searching..."; 
	bool done = false;
	bool found = false;
	Node* currentNode;
	if (rootNode != nullptr)
	{
		currentNode = rootNode;
		while (done == false)
		{
			if (currentNode)
			{
				if (currentNode->key == in_key)
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
						cout << in_key << currentNode->counter << "\n";
						done = true;
						found = true;
					}
				}
				else if (in_key > currentNode->key)
				{
					if (currentNode->rightChild != nullptr)
					{
						currentNode = currentNode->rightChild;
					}
					else
					{
						//fell off tree -- not found 
						cout << in_key << " 0\n";
						done = true;
						found = false;
					}
				}
				else if (in_key < currentNode->key)
				{
					if (currentNode->rightChild != nullptr)
					{
						//set to next node in tree and rerun above code with this new node 
						currentNode = currentNode->rightChild;
					}
					else
					{
						//fell off the tree -- not found 
						cout << in_key << "0\n";
						done = true;
						found = false;
					}
				}
			}
			else
			{
				//Hopefully never hit this 
				cout << "Unknown Error! \n";
			}
		}
	}
	return found;
}

void BST::_traverse(Node* in_node)
{
	if (in_node != nullptr)
	{
		_traverse(in_node->leftChild);
		cout << in_node->key << " " << in_node->counter << "\n";
		_traverse(in_node->rightChild);
	}
	else
	{
		return;
	}
}

void BST::_getRange(bool mM)
{
	//using mM to tell if this should search for the minimum or maximum 
	//false for minimum
	//true for maximum

	Node* currentNode;
	bool complete = false;

	if (rootNode != nullptr)
	{
		currentNode = rootNode;
		while (complete == false)
		{
			if (mM == false)
			{
				if (currentNode->leftChild != nullptr)
				{
					currentNode = currentNode->leftChild;
				}
				else
				{
					//fell off the tree 
					//currentNode is the minimum 
					cout << "Minimum: " << currentNode->key << " " << currentNode->counter << "\n";
					complete = true;
				}
			}
			else
			{
				if (currentNode->rightChild != nullptr)
				{
					currentNode = currentNode->rightChild;
				}
				else
				{
					//fell off the tree
					//currentNode is the minimum 
					cout << "Maximum: " << currentNode->key << " " << currentNode->counter << "\n";
					complete = true;
				}
			}
		}
	}
	else
	{
		//tree is empty 
		cout << "Tree is empty\n";
	}
}

Node* BST::_getNode(string in_key)
{
	Node* foundNode;
	if (rootNode->key == in_key)
	{
		return rootNode;
	}
	else
	{
		for (int i = 0; i < 100; i++)
		{
			if (nodeStorage[i].key == in_key)
			{
				return &nodeStorage[i];

			}
		}
	}
}