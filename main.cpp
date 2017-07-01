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

#include <iostream>
#include <algorithm>
#include <string>
#include <ostream>
#include <iomanip>
#include <vector>
#include <fstream>
#include <sstream>
#include <set>
#include "tree.h"
#include "avl.h"
#include "tree_collection.h"

using namespace std;

int main (int argc, char *argv[]){

TreeCollection collection;
AVL_Tree avlTree;

ifstream inFile;
string line, filename;
int count=0;
cout<<fixed<<setprecision(4);

if(argc==1){
	cerr<<"No input file provided"<<endl;
}
else{
	filename=argv[1];
	inFile.open(filename);

}

if(!inFile){
	cerr<<"File unable to be opened"<<endl;
}
else{	
/********************************************
Data Collection Phase
********************************************/
	while(getline(inFile, line)){ //get the line
		char comma;
		string status, health, species, boro;
		int tree_id, diameter, zipcode;
		double xpc, ypc;

		istringstream   linestream(line);
	    if(count>0){

		for(int i=1; i<42; i++){
			string first;

			string quotedtext;
			
			getline(linestream, first,',');
			if(first.size()>0&&first.at(0)=='"'){
				getline(linestream, quotedtext,'"');
				linestream>>comma;
			}
			
			if(i==1){
				try{
					tree_id=stoi(first);
				}
				catch(invalid_argument&){
					cout<<"error with data"<<endl;
				};
			}

			if(i==4){	
				try{
					diameter=stoi(first);
				}
				catch(invalid_argument&){
					cout<<"error with data"<<endl;
				};
			}

			if(i==7)
				status=first;

			if(i==8)
				health=first;

			if(i==10)
				species=first;

			if(i==26){	
				try{
					zipcode=stoi(first);
				}
				catch(invalid_argument&){
					cout<<"error with data"<<endl;
				};
			}

			if(i==30)
				boro=first;

			if(i==40){	
				try{
					xpc=stod(first);
				}
				catch(invalid_argument&){
					cout<<"error with data"<<endl;
				};
			}

			if(i==41){	
				try{
					ypc=stod(first);
				}
				catch(invalid_argument&){
					cout<<"error with data"<<endl;
				};
			}

		}
		if(count>0){
			Tree *newTree =new Tree(tree_id, diameter, status, health, species, zipcode, boro, xpc, ypc);
			collection.insertTree((*newTree));
			avlTree.insert((*newTree));
		}
	    }//end of iff
	    count=1;
	}//end of while
}

/* 	
	*********************************
	********Interactive Mode*********
	*********************************
*/

cout<<"Welcome to NYC Trees Database."<<endl;
string keyword;

while(keyword!="quit"){


	cout<<"Enter the tree species to learn more about it. Quit to exit."<<endl;

	getline(cin, keyword);
	transform(keyword.begin(), keyword.end(), keyword.begin(), ::tolower);
	if(keyword!="quit"){
		list<string> matches;
		matches=collection.get_matching_species(keyword);
		if(!matches.empty()){
			list<string>::const_iterator it;
			cout<<endl;
			cout<<"Matching species:"<<endl;
			cout<<endl;
			for(it = matches.begin(); it != matches.end(); ++it ){
				cout<<*it<<endl;	
			}
			cout<<endl;
			cout<<"Popularity in the city:"<<endl;
			cout<<endl;
			collection.printOutforSearch(keyword);
		}			
	}
}

return 0;
}
