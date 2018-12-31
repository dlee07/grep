#include <iostream> 
#include <string>
#include "stringProcessing.h"
using namespace std; 

/*
Author: Daniel Lee
UTLN: dlee07

Purpose: file contains the implementation of stripNonAlphaNum,
which will strip all non-alphabet and non-numeric characters
from the beginning and end of string.
Also an int main is used to receive a string from the client
and test the stripNonAlphaNum function. 
*/

int main()
{
	string temp;
	cout << "word to be stripped" << endl;
	cin >> temp;
	cout <<	stripNonAlphaNum(temp) << endl;
	return 0;
}
/*
Purpose: strips all non-alphabet and non-numeric chars
at the beginning and end of string

Parameters: a string

Return: the updated string
*/

string stripNonAlphaNum(std::string array)
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
	while(k > 0) // find the index k of concatenated string for the first invalid char
	{	
		if(isalnum(concatenate[k]))
			break;
		k--;
	}
	for(unsigned long j = 0; j <= k; j++) // concatenate all chars from the beginning to k. 
			word += concatenate[j];
	return word;
}