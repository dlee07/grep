#ifndef HASH_H
#define HASH_H
#include <vector>

/*
UTLN: dlee07
File contains the declarations and functions of Hash class. 
The class acts as some sort of dictionary and storage base
for all words in a directory
*/
using namespace std;

class Hash{

public: 

	Hash();
	
	~Hash();

	void insert(string word, string value, int filepath, int number, int line);
	
	void expand();

	void print_sensitive(string word, string Query);
	
	void print_insensitive(string word, string Query);
	
	int insert_line(string word);
	
	int insert_filepath(string word);
	
	int getCapacity();
	
	int getitems();
	
	void set_bool(bool word);
	
	bool get_bool(int number);
	
	void change_bool(int n);
	
	void reinitialize();

private: 
	
	/* a Node that contains: 
	1. a lower-case version of a word
	
	2. the version of the word appeared in the file
	
	3. an integer that is an index of the vector filepath. 
	   This index gives us constant access to the filepath of the word

	4. an integer that represents the line number

	5. an integer that is an index of the vector sentence.
	   This index gives us constant access to the sentence the word 
	   is located.
	*/
	struct Pathnode{

		string lower_key;

		string original;
		
		int path;

		int line_number;
		
		int concatenate;
		
		Pathnode *next;
	};
	
	static const int initCapacity = 101;
	int Capacity;
	int currentitems;

	Pathnode **HashTable; // a hashtable of pointers

	int listlength(Pathnode *ptr);
	void deletelist(Pathnode *ptr);
	string getvalue(Pathnode *ptr);
	
	// an object of the hash class. Can pass a string and 
	// the word will be hashed to a certain index of the 
	// hash table
	hash<string> hashfunction; 
	
	// a vector that stores a sentence of a file in each index
	vector<string> sentence; 
	
	// a vector that stores a filepath in an index. 
	vector<string> filepath;

	// a vector of booleans that corresponds to the vector sentence.
	vector<bool> sentence_print;


};
#endif
