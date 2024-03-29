//Trees.cpp
//Jacob Schaupp
//EECS 2510, Fall 2018
//11/7/2018
//Main Entry Point for the Program

#include "pch.h"
#include "BST.h"
#include "AVL.h"
#include "RBT.h"
#include "SkipList.h"
#include <iostream>
#include <string>

using namespace std; 

int main()
{
	string argument, string; 
	char passer[50];  
	//Code to Read File 

	char c;
	RBT RBT_T;
	
	AVL AVL_T;
	BST BST_T;
	SkipList SL; 
	char chari[50]; // assumes no word is longer than 49 characters
	memset(chari, 0, 50); // zero the word buffer
	int iPtr;
	bool IsDelimiter = false, WasDelimiter = false;

	ifstream inFile;
	inFile.open("Shakespeare.txt", ios::binary);
	if (inFile.fail())
	{
		cout << "Unable to open input file\n\n"
			<< "Program Exiting\n\nPress ENTER to exit\n";
		cin.get(c);
		exit(1);
	}
	iPtr = 0;
	inFile.get(c); // priming read
	while (!inFile.eof())
	{
		IsDelimiter = (c == ' ' || c == 10 || c == 13 || c == 9 || c == '.' || c == ',' ||
			c == '!' || c == ';' || c == ':' || c == '(' || c == ')' || c == '?' ||
			c == '-');
		if (IsDelimiter && !WasDelimiter) // if THIS character IS a delimiter, and the
		// last character WASN’T, it’s the end of a word
		{
			WasDelimiter = true;

			RBT_T.Insert(chari); // insert this word in the RBT
			//AVL_T.Insert(chari); // insert it in the AVL Tree
			BST_T.Insert(chari); // insert it in the BST
			SL.Insert(chari); // insert it in the skip list
			memset(chari, 0, 50); // zero the word buffer
			iPtr = 0;
			
		}
		else if (!IsDelimiter) // if this isn’t a delimiter, keep going
		{
			chari[iPtr] = c;
			iPtr++;
		}
		else if (IsDelimiter && WasDelimiter)
		{
			// Do nothing -- two consecutive delimiters.
		}
		WasDelimiter = IsDelimiter; // for the NEXT iteration
		inFile.get(c);
	}
	inFile.close();
	
	//get info from all of the structures 
	BST_T.GetTreeInfo();
	AVL_T.GetTreeInfo(); 
	RBT_T.GetTreeInfo(); 
	SL.GetInfo();
	 
	/*
	SkipList list; 

	std::cout << "input... \n"; 
	std::cin >> argument >> passer; 

	//main entry point for program 
	//create all the trees
	//read in the file and the characters into each tree to test speed and whatever 

	while (argument != "exit")
	{
		if (argument == "insert")
		{
			list.Insert(passer); 
		}
		if (argument == "show")
		{
			//binaryTree.HeightOfRoot(); 
			//list.List(); 
		}
		cout << "Complete...\n"; 
		cin >> argument >> passer; 
	}
	  */ 
}