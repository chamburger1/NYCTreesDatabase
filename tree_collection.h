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

#ifndef __Tree_Collection_H__
#define __Tree_Collection_H__
#include <string>
#include <iostream>
#include <iomanip>
#include <list>
#include <set>
#include <map>
#include "avl.h"
#include "tree.h"
#include <algorithm>

using namespace std;

class TreeCollection
{
public:

//default constructor and destructor
	TreeCollection (){}
	~TreeCollection (){}

//this returns the total counter integer variable
    	int total_tree_count(); 
//returns the mapped value at the TreesSpecies key passed as species_name
    	int count_of_tree_species ( const string & species_name ); 
//returns the mapped value at the treesInBoro key passed as boro_name
    	int count_of_trees_in_boro( const string & boro_name ); 

//populates and returns a list of matching species given a keyword
//it iterates through the TreeSpecies map and for each species separates into words, adds each word to a set, then before next iteration checks if a search word matches any words in the set, if it does it adds that species to a list.  The iteration ends at the end of the TreeSpecies map and a list is returns


    	list<string> get_matching_species(const string & species_name); 

//insert tree into the underlying avl container~calls the avlTree member's insert fucntion
    	void insertTree(Tree& x);

//this is a print function to display a table for the user based on a search keyword
//it calls the get_matching_species function and uses that list to total how many of the matching species are in the city
//it iterates through the treesInBoro map then iterates through a list(using the searchforFirst function) of matching trees to check 
//how many have matching boroughs at each boro in the map this happens to allow a total of matching trees of that species to be calculated 
	void printOutforSearch(string &x);

private:
/*
Private data: An AVL tree instance, a treecounter integer to check how many trees are in the avl tree.  two maps for the species and bororughs in the AVL tree. Every time a tree is inserted into the avl the count is increased by 1.  The tree's common_name and species are added to the treespecies and treesinboro map.  If there is already a matching entry in either map then the value at that entry is increased by 1
*/
	AVL_Tree avlTree;
	int treeCount=0;
	map<string, int> TreeSpecies;
	map<string, int> treesInBoro;

//simple function to increase the total tree count
//i could've iterated through the treeSpecies map and added the vallues to a total but this is quicker
    	void increaseTreeCount();

//this if a function to allow to print a data table if a user searches the tree collectionit searches for the first instance of a tree 
//with a specified species name passed as x in the function. This then gets passed to thhe AVL tree's find all matches to populate a 
//list of all trees with matching species iterating through this list and seeing if they match the borough allows me to calculate the
//percent of that borough's trees match that species. It is passed a root node and a string for species and finds the first tree 
//that matches that species
	Tree& searchforFirst(AVL_Tree::AvlNode *t, const string x);
};


#endif /* Tree_Collection_H__ */

