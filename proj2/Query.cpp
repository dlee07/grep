#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <sstream>
#include <algorithm>
#include <cctype>

#include "Query.h"

/*
File contains the implementations of the functions of Query Class.
The functions create a tree based on the directory passed from 
user, stores all the words in the directory into a hash table, 
forming some sort of collection database
Once a word is passed to search, this class accesses the information
*/
using namespace std;

/*
purpose: default constructor

Parameters: nothing

Return: nothing
*/
Query::Query()
{
	//nothing 
}

/*
Purpose: Constructor that takes in a string
The constructor creates a tree and passes that tree
into the treetraversal function to create  a database
of words

Parameters: a string

Return: none
*/
Query::Query(string directory)
{
	FSTree temp_Tree(directory);
	tree = temp_Tree; // assign operator
	object = tree.getRoot();
	sensitivity = false;	
	treetraversal(object);
}

/*
Purpose: deallocates any memory on heap; 
reinitializes pointers to NULL

Parameters: none

Return: none
*/
Query::~Query()
{
	object = NULL;
}

/*
purpose: runs the query search

Parameters: none

Return: none
*/
void Query::run()
{
	string input;
	bool game = false; // a boolean to start or stop query search
	int count = 0; 
			
	while(game != true)
	{	
		cout << "Query? ";
		getline(cin, input); // read user input as one line
		istringstream line(input); //parse words if line has multiple words
		string temp;
		
		while(line >> temp)
		{	// if user inputs quit as the very first string, 
			//cout query before termination
			if((temp == "@q" || temp == "@quit") && count > 0)
				cout << "Query? ";

			game = command(temp); // execute a specific operation on word
			//incremented count so query isn't printed if quit isn't first input
			count++; 
		}
		count = 0; // set count to zero for the next line of command
		if(game == true)//user submitted quit
				break;
		if(cin.eof())// user presses control and d
		{
			cout << endl;
			cout << "Goodbye! Thank you and have a nice day." << endl;
			break;
		}	
	}	
}

/*
Purpose: determines what operation should be done based on word

Parameters: a word

Return: a boolean
*/
bool Query::command(string word)
{
	if(word == "@q" || word == "@quit")//case for quit
	{
		cout << endl;
		cout << "Goodbye! Thank you and have a nice day." << endl;
		return true;
	}	
				
	else if(word == "@i" || word == "@insensitive")
		sensitivity = true;

	else if(sensitivity == false)//case for test sensitive
	{
		case_sensitive(word);
	}
	else if(sensitivity == true)//case for test insensitive
	{
		case_insensitive(word);
	}
	
	return false;
}

/*
Purpose: does a case insensitive searxh

Parameters: the word, which is the query

Return: none
*/
void Query::case_insensitive(string word)
{
	string temp;
	string search;
	temp = stripNonAlphaNum(word); //strip all non-alphanumeric characters
	
	//convert word to lowercase
	if(check_EmptyString(temp) == true)
	{
		search = temp; // store the stripped version of word
		// converts to lowercase
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower); 
		Index_Structure.print_insensitive(temp, search); // print all instances
		// reset this boolean so it can do a case sensitive if @i is not passed 
		//after the current query
		sensitivity = false; 
		// reinitializes the vector sentence print to false so lines can be 
		//printed again for the next query. 
		Index_Structure.reinitialize(); 
	}
}

/*
Purpose: does a case sensitive searxh

Parameters: the word, which is the query

Return: none
*/
void Query::case_sensitive(string word)
{
	string temp;
	string search;//strip all non-alphanumeric characters
	temp = stripNonAlphaNum(word);
	
	//convert word to lowercase
	if(check_EmptyString(temp) == true)
	{
		search = temp; // store stripped version of word
		transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
		Index_Structure.print_sensitive(temp, search);
		// reinitializes the vector sentence print to false so lines can be 
		//printed again for the next query. 
		Index_Structure.reinitialize();
	}
}

/*
Purpose: returns a boolean to signal the program if the query,
after processed through stripNonAlphaNum is an empty string or not

Parameters: a word, the query

Return: returns false if the string is empty, true otherwise.
*/
bool Query::check_EmptyString(string word)
{

	if(word.length() == 1 && !isalnum(word[0]) && sensitivity == false)
	{
		cout << " Not Found. Try with @insensitive or @i." << endl;
		return false;
	}	
	else if(word.length() == 1 && !isalnum(word[0]) && sensitivity == true)
	{
		cout << " Not Found." << endl;
		return false;
	}
	return true;
}
/*
Purpose: iterates through the directory, calles execute_files
to store all words in file into the hash table. Calls execute
files if a file exist. The execute file will process the file

Parameters: a pointer to a node of tree

Return: none
*/
void Query::treetraversal(DirNode *ptr)
{
	//if the directory is empty
	if(ptr->isEmpty() == true)
		return;
	if(ptr->hasFiles() == true)	
	{//if directory has files, execute files. 
		for(int i = 0; i < ptr->numFiles(); i++)
		{	//if at root directory
			if(ptr->getParent() == NULL)
			{
				string word;
				word = ptr->getName() + "/" + ptr->getFile(i);
				execute_files(word, word);
			}	
			else{
				string word;
				string word2;
				word2 = print_parent(ptr->getParent()); //store name of subdirs
				//concatenate the parent, the directory name and name of file.
				word = word2 + ptr->getName() + "/" + ptr->getFile(i); 
				execute_files(word, word);
				//cerr << word << endl;
			}			
		}
	}
	///if directory has sub-directories
	if(ptr->hasSubDir() == true)
	{	//traverse through those sub-directories and print file path. 
		for(int j = 0; j < ptr->numSubDirs(); j++)
			treetraversal(ptr->getSubDir(j));
	}
}

/*
Purpose: opens a file and reads each line of the file.
Then inserts all the words in file in hash table

Parameters: two strings: one for file name and the other
for file path

Return: none
*/
void Query::execute_files(string word, string word2)
{
	string input;
	ifstream infile; 
	//insert_filepath returns the index the filepath is located in the 
	// filepath vector, which stores all the filepath
	int b = Index_Structure.insert_filepath(word2);
	int count = 1; //line number
	infile.open(word.c_str());//open file

	//while reading each line
	while(getline(infile, input))
	{	// stores the index the sentence is stored in the sentence array
		int a = Index_Structure.insert_line(input);
		Index_Structure.set_bool(false);
		istringstream read(input); //parse each line
		string file_input;

		while(read >> file_input)// while each word of line is read
		{
			string save;
			string temp;
			// get rid of non-alphanumeric characters, store into variable
			temp = stripNonAlphaNum(file_input);
			//if it is not an empty string
			if(isalnum(temp[0]))
			{
				save = temp;// store a copy of word
				// convert word to lowercase
				transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
				/*insert word into hash table, w/ the version of word in file,
				the index the filepath is located in the filepath vector, the line
				number, and the index the sentence is located in sentence vector*/
				Index_Structure.insert(temp, save, b, count, a);
			}
		}
		count++;// increment number of lines
	}
	infile.close();
}

/*
STUB that prints the capacity and number of items in table
Parameters: none
Return: none
*/
void Query::print()
{
	cout << Index_Structure.getCapacity() << endl;
	cout << Index_Structure.getitems() << endl;
}

/*
Purpose: prints the subdirectories in which the current directory belongs
parameter: a pointer to a Node
Return: none
*/
string Query::print_parent(DirNode *ptr)
{// if it's at the root
	if(ptr->getParent() == NULL)
		return ptr->getName() + "/";
	
	else{
		string temp = ptr->getName() + "/";
		// concatenate the current directory name with parent directory name
		return print_parent(ptr->getParent()) + temp;
	}
}

/*
Purpose: strips all non-alphabet and non-numeric chars
at the beginning and end of string

Parameters: a string

Return: the updated string
*/

string Query::stripNonAlphaNum(string array)
{
	bool check = false; //boolean to check for non-alpha or non-numeric
	bool check_alpha = false; //boolean to check for valid char
	string concatenate = "";
	string word = "";
	// iterate through the array	
	for(unsigned long i = 0; i < array.length(); i++)
	{
		if(isalnum(array[i])) //if it's a valid char, concatenate
		{
			concatenate += array[i];
			check_alpha = true; 
			// turn this into true so any invalid chars are not erased
			check = true; 
		}
		else if(!isalnum(array[i])) // if it's not a valid char
		{//if there are non-valid chars between valid chars, concatenate
			if(check_alpha == true && check == true)
				concatenate += array[i];
		}
	}
	unsigned k = concatenate.length();
	// find the index k of concatenated string for the first invalid char
	while(k > 0) 
	{	
		if(isalnum(concatenate[k]))
			break;
		k--;
	}// concatenate all chars from the beginning to k.
	for(unsigned long j = 0; j <= k; j++)  
			word += concatenate[j];

	return word;
}