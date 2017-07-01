#include "tree_collection.h"

int TreeCollection::total_tree_count(){
	return treeCount;
}

void TreeCollection::increaseTreeCount(){
	treeCount++;
}

void TreeCollection::insertTree(Tree& x){
	avlTree.insert(x);
	increaseTreeCount();
	if(!treesInBoro.insert(make_pair(x.borough_name(), 1)).second){
		treesInBoro[(x.borough_name())]++;
	}
	if(!TreeSpecies.insert(make_pair(x.common_name(), 1)).second){
		TreeSpecies[x.common_name()]++;
	}
} 
 
int TreeCollection::count_of_tree_species (const string & species_name){
		
	if(!TreeSpecies.empty()&&TreeSpecies.count(species_name)==1){
		return TreeSpecies.at(species_name);
	}
	else 
		return 0;
}

int TreeCollection::count_of_trees_in_boro(const string & boro_name ){

	if(!treesInBoro.empty()&&treesInBoro.count(boro_name)==1){
		return treesInBoro.at(boro_name);
	}
	else 
		return 0;
}

list<string> TreeCollection::get_matching_species(const string & species_name){
	list<string> listOfSpecies;
  	map<string, int>::iterator it;
	
	for(auto &x: TreeSpecies){
		set<string> words;
		string to_check=x.first;
		transform(to_check.begin(), to_check.end(), to_check.begin(), ::tolower);
		words.insert(to_check);
		int beginning=0;
		for(unsigned int j=0; j<to_check.size(); j++){

			if(to_check.at(j)==' '||to_check.at(j)=='-'){ //handle multiword species 
				string word=to_check.substr(0, j);
				words.insert(word);
				word=to_check.substr(beginning, j-beginning);
				words.insert(word);
				string wordwithspace=word;
				string spaceinfront=" ";
				spaceinfront.append(word);
				wordwithspace.append(" ");
				words.insert(wordwithspace);
				words.insert(spaceinfront);

				beginning=j+1;

				word=to_check.substr(beginning, to_check.size()-beginning);
				words.insert(word);

				wordwithspace=word;
				spaceinfront=" ";
				spaceinfront.append(word);
				wordwithspace.append(" ");
				words.insert(wordwithspace);
				words.insert(spaceinfront);
			}
			

			else 			//a single word species
				words.insert(to_check);
		}
	
		if(words.count(species_name)==1){
			listOfSpecies.push_back(x.first);
		}	
	}

//////////////remove
	if(listOfSpecies.size()>0){
		return listOfSpecies;	
	}
	else{
		cout<<"No matches found."<<endl;
		return listOfSpecies;	
	}
		
}


void TreeCollection::printOutforSearch(string &x){
	
	cout<<fixed<<setprecision(2);

	double percent;
	list<string>speciesToSearch=get_matching_species(x);
	int totalTreesMatchingInCity=0;

	list<Tree>::const_iterator it3;
  	list<string>::const_iterator it4;
	list<Tree> totalcountofspecies;

	for(it4 = speciesToSearch.begin(); it4 != speciesToSearch.end(); ++it4 ){
		totalTreesMatchingInCity=totalTreesMatchingInCity+TreeSpecies[*it4];
	}
	
	cout<<setw(20)<<internal<<"NYC"<<setw(15)<<totalTreesMatchingInCity<<"(";
	cout<<total_tree_count()<<") ";
	percent=((totalTreesMatchingInCity*100.00)/total_tree_count());
	cout<<right<<setw(7)<<percent<<"%"<<endl;

	for(auto &x: treesInBoro){
		int amtTreesMatch=0;
		for(it4 = speciesToSearch.begin(); it4 != speciesToSearch.end(); ++it4 ){
			totalcountofspecies=avlTree.findallmatches(searchforFirst(avlTree.root, *it4));
			for(it3 = totalcountofspecies.begin(); it3 != totalcountofspecies.end(); ++it3 ){
				if(it3->borough_name()==x.first){
					amtTreesMatch++;
				}
			}
		}
		if(amtTreesMatch!=0){
			percent=((amtTreesMatch*100.00)/x.second);
			cout<<setw(20)<<internal<<x.first<<setw(15);
			cout<<amtTreesMatch<<"("<<count_of_trees_in_boro(x.first)<<") "<<right<<setw(7)<<percent<<"%"<<endl;
		}
	}	
}
		
Tree& TreeCollection::searchforFirst(AVL_Tree::AvlNode *p, const string x){
    	if (p==NULL||p->element.common_name()==x)
       		return p->element;

    	if (p->element.common_name() < x)
       		return searchforFirst(p->right, x);

    	return searchforFirst(p->left, x);
}
