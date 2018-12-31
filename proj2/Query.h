#ifndef QUERY_H
#define QUERY_H
#include "Hash.h"
#include "DirNode.h"
#include "FSTree.h"
/*
UTLN: dlee07
File contains the function and private attribute declarations of 
Query Class. This class represents the search engine. 
*/
using namespace std;

class Query 
{

public: 

	Query();
	
	Query(string directory);
	
	~Query();
	
	void run();
	
	bool command(string word);
	
	void treetraversal(DirNode *ptr);
	
	string print_parent(DirNode *ptr);
	
	string stripNonAlphaNum(string array);
	
	void execute_files(string word, string word2);
	
	void print();
	
	bool check_EmptyString(string word);

	void case_insensitive(string word);

	void case_sensitive(string word);

private: 
	// the boolean that keeps in track if an insensitive or sensitive search should be done
	bool sensitivity; 
	
	DirNode *object;
	
	FSTree tree;
	
	Hash Index_Structure;
};
#endif