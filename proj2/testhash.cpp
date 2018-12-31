#include <iostream>
#include "Hash.h"

/*
File that tests the implementation of the Hash Class
*/
using namespace std;

int main()
{
	Hash table;
	
	/*order for insert to work, one must call
	insert_line, insert_filepath, and set_bool
	Or else, a segmentation fault will happen 
	as the numbers inserted into the insert function
	will try to acess a value that is out of scope
	of the 3 vectors*/
	table.insert("key", "Key", 2, 4, 6); 
	table.insert("key", "Key", 2, 4, 6);
	table.insert("key", "Key", 2, 4, 6);
	cout << table.getitems() << endl;
	cout << table.getCapacity() << endl;
	
	table.print_sensitive("key", "Key");
	
	table.printallindex();

	return 0;
}