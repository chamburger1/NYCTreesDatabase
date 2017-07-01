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

#ifndef __AVL_H__
#define __AVL_H__
#include <string>
#include <algorithm>
#include <iostream>
#include <list>
#include "tree.h"

using namespace std;

class AVL_Tree
{
public:
    	AVL_Tree  ( ){}                    	// default
//copy constructor calls copyHelper private function~passed root
    	AVL_Tree  ( const AVL_Tree & tree);  	// copy constructor
    	~AVL_Tree ( ){}                     	// destructor
      
    // Search methods:
//calls private search funtion~passed root and x  
    	const Tree& find    ( const Tree & x ) const;

//calls findMin private function~passed root  
   	const Tree& findMin () const; 

//calls findMax private function~passed root
	const Tree& findMax () const; 

//calls findAllHelper private function~passes root, x, and a list of Trees
    	list<Tree> findallmatches ( const Tree & x ) const;
    
    // Displaying the tree contents:
//calls inorder private function~passed the root and out
    	void   print   ( ostream& out ) const;  
   
    // Tree modifiers:
//clear calls clearhelper private function~passed root
    	void   clear();                       // empty the tree //done

//calls insert private functon~passed tree element and root
    	void   insert( const Tree& x);  // insert element x done

//calls remove private function and is passed root and Tree element
    	void   remove( const Tree& x);  // remove element x done

//a nested struct node that holds a pointer to left and right, a Tree element, a variable to measure its height
//constructors are from the text book, passed a tree element and a pointer to left and right and initializes data
	struct AvlNode
	{
		Tree element;
		AvlNode *left;
		AvlNode *right;
		int height;
		~AvlNode(){}

		AvlNode(const Tree &ele, AvlNode *lt, AvlNode *rt, int h=0): element {ele}, left{lt}, right{rt}, height{h}{}

		AvlNode(const Tree && ele, AvlNode *lt, AvlNode *rt, int h=0): element {std::move (ele)}, left{lt}, right{rt}, height{h}{}
	};

//root initialized to NULL
	AvlNode * root=NULL;


private:
/*
These are all helpers for the public functions to allow recursive calls to take advanatge of AVL trees speed
*/

//helper for copy constructor, starts at the node p and recurses if p is not NULL 
//in the public function root is set to the return node of this function thus a tree is constructed from the root down of another tree
	AvlNode* copyTree(AvlNode *p)const;

//this starts at node t and if its null inserts the tree element there, if its not then it checks if the Tree element there is less
//than or greater than x and will either resurce to the t->left or t->right
	void insert(const Tree & x, AvlNode *&t); 

//this is a helper for the findallmatches public function.  It returns a list and uses the samename and islessname fucntions as 
//defined in the Tree class.  It takes a node, tree, and list as arguments.  If the node is Null and the local bool is never true it 
//pushes bask a NO_TREE.  If the tree at p is less than the tree argument it recurses to the right, if x is less tan the tree at p it
// recurses to the left.  If samename for tree at p and x returns true, then it pushes back the tree at p and goes to the left and 
//right child if they are not null.  The fully populated list is returned at the end of the call
	list<Tree> findAllHelper(AvlNode *p, const Tree & x, list<Tree> helper)const;

//this function recurses down from the root and finds the height of each node-uses ternary conditional operator 
	int height( AvlNode *t ) const;	

//this function starts at the root and recurses down searching for the first tree that returns true on the == overloaded tree
//operator against the argument x
	const Tree& search(AvlNode *t, const Tree & x)const;

//this ia a remove helper functon that starts at the root and recurses down checking if x==Tree at the node, it uses the overloaded ==
//operator
	void remove(const Tree & x, AvlNode *&t);

//these are rotation algoritms as listed in the text books
//they are called in the balance private function in order to make sure the avl tree mainatins is avl property
//the balance function relies on these and height
	void doubleWithLeftChild(AvlNode *& k3);	//this calls rotate right then rotate left
	void rotateWithLeftChild( AvlNode *& k2 );	//this rotates to the left one node
	void doubleWithRightChild(AvlNode *& k3);	//this calls rotate left child and then rotate right child
	void rotateWithRightChild( AvlNode *& k2 );	//this rotates the tree right one node

//this is a funtion to rebalance the avl tree.  it gets cvalled at the end of insert and at the end of remove
	void balance(AvlNode *&t);

//these are both helpers for the find min and max public functions.  They both start at the root and recurse til the ends to find
//max and min tree objects.  The find mind recurses left while the find max recurses right
	const Tree& findMax(AvlNode* p)const; // find a node with maximal key in a p tree 
	const Tree& findMin(AvlNode * p)const; // find a node with maximal key in a p tree 

//this is an inorder traversal with the added functon of printing node's Tree element to the ostream out argument
//it starts at the root, goes left all the way, prints, then goes to the root prints, and the recurses to the right to print
	void inOrder(AvlNode* p, ostream& out)const;

//this is a clear helper function to start at the root and recursively set each node to NULL and delete the pointer to it
//this effectively clears the tree however access to that memory will display garbage. 
	void clearhelper(AvlNode *& n);
};

#endif /* __AVL_H__ */

