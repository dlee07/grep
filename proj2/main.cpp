#include <iostream> 
#include <string> 
#include "Query.h"
#include <cstdio>
#include <cstdlib>

using namespace std;
/*
The interface of the gerp search engine
*/
int main(int argc, char *argv[])
{	// if a directory is passed
	if(argc == 2)
	{	
		// receives the directory and stores all the words into the hash table
		Query program(argv[1]); 
		//runs the query search
		program.run();
		// prints the capacity and number of items in hash table
		//program.print();
	}
	// if an invalid command argument is passed. 	
	else{
		cerr << " Usage:  gerp directory  " << endl;
		cerr <<	"			  where:  directory is a valid directory " << endl;
        return 1;
	}

	return 0;
}