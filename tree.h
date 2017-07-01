/***************************************************************************************************************
Title: NYC Tree Collection

Author: Chris Hamburger

Created: 3/20/17

Description: Parsing through a csv file to create a database of trees in NYC's 5 boroughs. 

Purpose: To practice using AVL trees and working with large datasets 

Compile: Navigate to the program directory and run the make command to create an executable file.

Executable name: assignment2

To run: copy command inside the brackets [./assignment2 name_of_text_file_argument.csv]

*****************************************************************************************************************/

#ifndef __Tree_H__
#define __Tree_H__
#include <string>
#include <iostream>

using namespace std;

class Tree
{
public:

//default constructor
	Tree(){}
//parameter constructor for 9 values to construct a tree object
   	Tree (  int id1, int diam1, string status1, string health1, 
           string spc1, int zip1, string boro1, double x1, double y1 );

//friend functiosn to access outside of the class
//this returns true if t1 and t2 have matching id and spc values
   	friend bool operator==(const Tree & t1, const Tree & t2);

//this returns true if t1's spc is less than t2 spc, if they are equal it checks their id values
   	friend bool operator<(const Tree & t1, const Tree & t2);

//overloading <<operator to print a tree's data directly to a stream
	friend ostream& operator<< (ostream & os, const Tree & t );

//returns true if t1 and t2 have matching spc values
	friend bool samename(const Tree & t1, const Tree & t2);

//returns true if t1's spc is alphabetically less than t2's spc
	friend bool islessname(const Tree & t1, const Tree & t2);
//end of friend functions

//getters for the spc value, the diameter value and the boro value
	string common_name()const{		return spc;}
	string borough_name()const{		return boro;}
	int diameter()const{			return diam;}
	

private:
	int id, diam, zip;
	string status, health, spc, boro;
	double x, y;

};
	const Tree  NO_TREE(0,0,"","","",0,"",0,0);
// A Tree object indicating no tree exists


#endif /* __Tree_H__ */


