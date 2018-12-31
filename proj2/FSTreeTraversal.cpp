#include <iostream>
#include <string>
#include "FSTree.h"
#include "DirNode.h"
using namespace std;

/*
Author: Daniel Lee
UTLN: dlee07

Purpose: contains the implementation of tree traversal function.
Also the file contains an int main to test the function
*/

// function declaration of treetraversal function
void treetraversal(DirNode *object);
void print_parent(DirNode *object);

int main(int argc, char *argv[])
{
	if(argc == 2) // if one string, the directory is not taken
	{
		string str(argv[1]);
		FSTree tree(str);
		treetraversal(tree.getRoot());
	}
	else{
		cerr << "Usage: put in valid directory" << endl;
	}
	return 0;	
}


void treetraversal(DirNode *object)
{	//if the directory is empty
	if(object->isEmpty() == true)
		return;
	if(object->hasFiles() == true)	
		{//if directory has files, print files. 
			for(int i = 0; i < object->numFiles(); i++)
			{	//if at root directory
				if(object->getParent() == NULL)
					cout << object->getName() << "/" << object->getFile(i) << endl;
				else{
					print_parent(object->getParent()); //print the subdirectories
					cout << object->getName() << "/" << object->getFile(i) << endl; //print current directory and file
				}			
			}		
		}	
	///if directory has sub-directories
	if(object->hasSubDir() == true)
	{	//traverse through those sub-directories and print file path. 
		for(int j = 0; j < object->numSubDirs(); j++)
			treetraversal(object->getSubDir(j));
	}
}

/*
Purpose: prints the subdirectories in which the current directory belongs
parameter: a pointer to a Node
Return: none
*/
string print_parent(DirNode *object)
{
	if(object == NULL)
		return;
	else{
		print_parent(object->getParent());
		
			cout << object->getName() << "/";
		
		
	}
}

