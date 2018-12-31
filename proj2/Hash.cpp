#include <iostream>
#include <functional>
#include <string>
#include <iomanip>
#include "Hash.h"

/*
UTLN: dlee07
File contains the implementation of functions of Hash class
*/

/*
Constructor: creates a hash table of pointers

Parameters: none

Return: none
*/
Hash::Hash()
{
	Capacity = initCapacity;
	currentitems = 0;

	HashTable = new Pathnode *[Capacity];
	
	for(int i = 0; i < Capacity; i++)
		HashTable[i] = NULL;
}

/*
Destructor: deallocates any memory allocated on heap

Parameters: none

Return: none
*/
Hash::~Hash()
{	// deletes list at each index
	for(int i = 0; i < Capacity; i++)
	{
		if(HashTable[i] != NULL)
			deletelist(HashTable[i]);
	}
	// deletes the array of pointers
	delete [] HashTable;
}

/*
Destructor: deletes a linked list

Parameters: a pointer to a node

Return: none
*/
void Hash::deletelist(Pathnode *ptr)
{
	Pathnode *temp = ptr;
	Pathnode *temp2 = ptr;
	while(temp != NULL)
	{
		temp = temp->next;	
		delete temp2;
		temp2= temp;
	}
	ptr = NULL;
}

/*
Purpose: when called, will hash the word to an index, 
store it as a Node with other important information, 
and the pointer at that index of the hash table will 
point to the node. It will be inserting on the front 
of the list.  

Arguments: a string that will be the lowercase version of 
a word. The string, value will represent the version of 
the word that appears in the file. The integer filepath is 
an index on the vector filepath. Acessing this index gives 
us acess to the exact filepath. The integer, number is the 
line number where the word appears in the file. The integer 
line is the index on the vector sentence. This index will 
give us the specific index an instance of the word appears 
in. 

Return: none
*/
void Hash::insert(string word, string value, int filepath, 
	int number, int line)
{	
	//expand if greater than load factor
	if(((double)currentitems/(double)Capacity) > 0.7)
		expand();

	size_t temp = hashfunction(word); //hash the word
	size_t temp2 = temp % Capacity; // temp2 will be the index
	// create a node
	Pathnode *newNode = new Pathnode; 
	newNode->lower_key = word;
	newNode->original = value;
	newNode->path = filepath;
	newNode->line_number = number;
	newNode->concatenate = line;
		
	if(HashTable[temp2] == NULL)// if the hash table has no words at that index
	{
		newNode->next = NULL;
		HashTable[temp2] = newNode;
	}
	else if(HashTable[temp2] != NULL)// if a word already existed at that index
	{
		newNode->next = HashTable[temp2];
		HashTable[temp2] = newNode;
	}
	currentitems++;
}
/*
Purpose: expands the Hash table and copies
information in old hash table to new hash table

Parameters: none

Return: none
*/
void Hash::expand()
{
	int old_size = Capacity;//store the old capacity
	
	// create a pointer that points to the old hash table 
	Pathnode **store_array = HashTable;
	//update capacity
	Capacity = Capacity * 2 + 1;
	//set the pointer that pointed to the old hash table point to a new table
	HashTable = new Pathnode*[Capacity]; 
	currentitems = 0;
	// initialize the new hash table
	for(int i = 0; i < Capacity; i++)
		HashTable[i] = NULL;
	// copy until old capacity is reached
	for(int i = 0; i < old_size; i++)
	{	
		Pathnode *temp = store_array[i];
		// if the pointer at the index is pointing to a list, re-insert node
		while(temp != NULL)
		{
			insert(temp->lower_key, temp->original, temp->path, 
			temp->line_number, temp->concatenate);
			temp = temp->next;
		}
		deletelist(store_array[i]); //after, copy delete the list
	}
	// delete the temporary pointer pointing to old table
	delete [] store_array; 
}

/*
Purpose: prints the file path, the line number where
the instance of the query appears, and the sentence
where the instance of the query appears. 

In this case, sensitivity matters so 
the program will compare the string original of each 
node to the Query. 

Parameters:  a word which is the key, the converted lower case 
version of the query. The second parameter is the word passed
by the client. 

Return: none
*/
void Hash::print_sensitive(string word, string Query)
{
	size_t temp = hashfunction(word);// hash to find the index
	size_t index = temp % Capacity;
	// make a temporary pointer pointing to list in index
	Pathnode *temp2 = HashTable[index];

	if(temp2 == NULL)// word is not found
		cout << Query << " Not Found. Try with @insensitive or @i." << endl;
	
	/*iterate through the list*/
	while(temp2 != NULL)
	{	
		// if the original version of the word matches the query and the 
		//sentence hasn't been printed, print
		if(temp2->original == Query && get_bool(temp2->concatenate) == false)
		{
			cout << getvalue(temp2) << endl;
			//set the value at Sentence_print[temp2->concatenate] to true
			// as the sentence at that index has been already printed
			change_bool(temp2->concatenate); 
		}	
			
		temp2 = temp2->next;
	}
}

/*
Purpose: 
Prints the words that match to the query of the user, regardless
if it's upper case or lowercase

Parameters: a word which is the key, the converted lower case version of 
the query. The second parameter is the query

Return: none
*/
void Hash::print_insensitive(string word, string Query)
{
	size_t temp = hashfunction(word); //hash
	size_t index = temp % Capacity;

	Pathnode *temp2 = HashTable[index];// a temporary pointer pointing to index
	// if the pointer at index is pointing to nothing, word is not found
	if(temp2 == NULL)
		cout << Query << " Not Found." << endl;
	/*iterate through the list*/
	while(temp2 != NULL)
	{
		// if the lower_case version of the word match the lower_case
		// version of the query and the sentence that contains the query
		// hasn't been printed, then print
		if(temp2->lower_key == word && get_bool(temp2->concatenate) == false)
		{
			cout << getvalue(temp2) << endl;
			//set the value at Sentence_print[temp2->concatenate] to true
			// as the sentence at that index has been already printed
			change_bool(temp2->concatenate);
		}

		temp2 = temp2->next;
	}
}

/*
Purpose: returns the size of a linked list
Parameters: a ptr to a Node
Return: an integer
*/
int Hash::listlength(Pathnode *ptr)
{
	int count = 0;
	Pathnode *temp = ptr;
	while(temp != NULL)
	{
		temp = temp->next;	
		count++;
	}	
	return count;
}
/*
Purpose: returns a concatenated statement of the filepath, the line 
number and the sentence. Essential for printing

Parameters: a pointer to a Node

Return: a string
*/
string Hash::getvalue(Pathnode *ptr)
{
	string number = ""; 
	number = to_string(ptr->line_number); // converts the line # to a string

	string combined = "";
	// combine the three variables. 
	combined = filepath[ptr->path] + ":" + number + ":" + " " + sentence[ptr->concatenate];

	return combined;
}

/*
STUB that returns capacity of table
Parameters: none
Return: an integer
*/
int Hash::getCapacity()
{
	return Capacity;
}

/*
Purpose: pushes a string into the sentence vector, which stores all the 
sentences in every file of the directory. It returns the size of the 
vector - 1, which is the index where a specific sentence is stored. 
This integer will then be stored in the struct. 

Parameters: a string

Return: an integer.
*/ 
int Hash::insert_line(string word)
{
	sentence.push_back(word);
	return sentence.size() - 1;
}

/*
Purpose: pushes a string into the filepath vector, which is the vector that
contains the filepaths of all the files in the directory. Returns the index
a specific filepath is located

Parameters: a string

Return: an integer, which is the index where a specific filepath is stored
*/
int Hash::insert_filepath(string word)
{
	filepath.push_back(word);
	return filepath.size() - 1;
}

/*
STUB that returns the number of things inside the table
Parameters: none
Return: an integer
*/
int Hash::getitems()
{
	return currentitems;
}

/*
Purpose: as false is inserted to the vector
sentence_print. This vector is identical to the sentence vector
but stores a boolean

Parameters: a boolean

Return: none
*/
void Hash::set_bool(bool word)
{
	sentence_print.push_back(word);
}

/*
Purpose: gets a integer and gets the boolean at that index in 
the sentence_print vector. 

Parameters: a integer

Return: a boolean
*/
bool Hash::get_bool(int number)
{
	return sentence_print[number];
}

/*
Purpose: changes the boolean at a certain index in the sentence_print
array. The boolean will only be changed when a sentence at the same 
index in the sentence array is printed, preventing duplicates.

Parameters: an integer

Return: none
*/
void Hash::change_bool(int n)
{
	sentence_print[n] = true;
}

/*
Purpose: once a query is done, you want to reinitialize 
everything back to false so those lines can be available for
print for the next query

Parameters: none

Return: none
*/
void Hash::reinitialize()
{
	for(unsigned long i = 0; i < sentence_print.size(); i++)
	{
		sentence_print[i] = false;
	}
}