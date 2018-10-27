//Jacob Schaupp 
//EECS 2510 Non Linear 
//09-28-2018
#include "pch.h"
#include "Node.h"

Node::Node()
{

}

Node::Node(string in_key)
{
	key = in_key;
	//should be 1 since it is new 
	counter = 1;
}

Node::Node(string in_key, Node* parentNode)
{
	key = in_key;
	counter = 1;
	parent = parentNode;
}


Node::~Node()
{
}
