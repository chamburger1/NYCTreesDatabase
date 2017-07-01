#include "avl.h"

list<Tree> AVL_Tree::findAllHelper(AvlNode *p, const Tree & x, 	list<Tree> helper)const{
	bool found=false;
      	const Tree  NO_TREE(0,0,"","","",0,"",0,0);

	if(p==NULL&&!found){
		helper.push_back(NO_TREE);
	}
	else if(islessname(p->element,x)){
       		return findAllHelper(p->right, x, helper);
		
	}
	else if(islessname(x,p->element)){
		return findAllHelper(p->left, x, helper);
	}

	else if(samename(p->element, x)){
		helper.push_back(p->element);
		found=true;

		if(p->left)
			helper=(findAllHelper(p->left, x, helper));
		if(p->right)
			helper=(findAllHelper(p->right, x, helper));		
	}

	return helper;
}

list<Tree> AVL_Tree::findallmatches ( const Tree & x ) const{
	list<Tree> matches;
	return 	findAllHelper(root, x, matches);
}


const Tree& AVL_Tree::find (const Tree & x ) const{
	return search(root, x);			
}

const Tree& AVL_Tree::search(AvlNode *p, const Tree & x)const{
    	if (p==NULL||p->element==x)
       		return p->element;

    	if (p->element < x)
       		return search(p->right, x);

    	return search(p->left, x);
}

const Tree& AVL_Tree::findMin () const{
	return findMin(root);
}

const Tree& AVL_Tree::findMin(AvlNode * p) const{
	if (p==NULL){
		cout<<"The tree is empty"<<endl;
	}
	else{
		while(p->left !=NULL){
			p=p->left;
		}
		return p->element;
	}
}

const Tree& AVL_Tree::findMax () const{
	return findMax(root);
}

const Tree& AVL_Tree::findMax(AvlNode* p) const {
	if (p==NULL){
		cout<<"The tree is empty"<<endl;
	}
	else{
		while(p->right !=NULL){
			p=p->right;
		}
		return p->element;
	}
}

void AVL_Tree::print(ostream& out) const{
	if(!root){
		cout<<"Empty tree."<<endl;
	}
	else
		inOrder(root, out);
}

void AVL_Tree::inOrder(AvlNode* p, ostream& out)const {
	if (p!=NULL){
       		inOrder(p->left, out);
       		out<<p->element<<" ";
       		inOrder(p->right, out);
    	}
}

AVL_Tree::AVL_Tree ( const AVL_Tree & tree){
	root=copyTree(tree.root);
}
	
AVL_Tree::AvlNode* AVL_Tree::copyTree(AvlNode *p)const{
	AvlNode *newNode;
    	if(p == NULL){
        	return NULL;
    	}
    	else{
   		newNode=new AvlNode{p->element, NULL, NULL};
    	}
    	newNode->left = copyTree(p->left); 
    	newNode->right = copyTree(p->right); 
    	return newNode;
}
    
void AVL_Tree::insert(const Tree& x){
	insert(x, root);
}

void AVL_Tree::clearhelper(AvlNode *& n){

	if(n != NULL){
      		clearhelper(n->left);   
		clearhelper(n->right);  
		n=NULL;
		delete n;         
	}
}                      

// empty the tree

void   AVL_Tree::clear(){
	clearhelper(root);
}

void AVL_Tree::remove( const Tree& x){
	remove(x, root);
}

static const int ALLOWED_IMBALANCE = 1;

void AVL_Tree::balance(AvlNode *&t){
	if(t == NULL)
		return;
	if(height(t->left)-height(t->right) > ALLOWED_IMBALANCE){
		if( height(t->left->left)>=height(t->left->right))
			rotateWithLeftChild(t);
		else
			doubleWithLeftChild(t);
	}
	else if(height(t->right )-height(t->left)>ALLOWED_IMBALANCE){
		if( height(t->right->right)>=height(t->right->left))
			rotateWithRightChild(t);
		else
			doubleWithRightChild(t);
	}
		
	t->height = max(height(t->left), height(t->right))+1;
}

void AVL_Tree::rotateWithLeftChild( AvlNode * & k2 ){
	AvlNode *k1 = k2->left;

	k2->left = k1->right;
	k1->right = k2;
	k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->left ), k2->height ) + 1;
	k2 = k1;
}

void AVL_Tree::doubleWithLeftChild( AvlNode * & k3 ){
	rotateWithRightChild( k3->left );
	rotateWithLeftChild( k3 );
}

void AVL_Tree::remove(const Tree & x, AvlNode *&t){
	if(t== NULL)
		return;   // Item not found; do nothing
	if(x<t->element )
		remove(x, t->left);
	else if(t->element<x)
		remove(x, t->right);
	else if(t->left != NULL && t->right != NULL)  // Two children
	{
		t->element = findMin(t->right);
		remove(t->element, t->right);
	}
	else
	{
		AvlNode *oldNode = t;
		t = (t->left != NULL) ? t->left : t->right;
		delete oldNode;
	}
	
	balance(t);
}

void AVL_Tree::rotateWithRightChild( AvlNode *& k2 ){
	AvlNode *k1 = k2->right;

	k2->right = k1->left;
	k1->left = k2;
	k2->height = max( height( k2->right ), height( k2->right ) ) + 1;
	k1->height = max( height( k1->right ), k2->height ) + 1;
	k2 = k1;
}

void AVL_Tree::doubleWithRightChild( AvlNode *& k3 ){
	rotateWithLeftChild( k3->right );
	rotateWithRightChild( k3 );
}


void AVL_Tree::insert(const Tree & x, AvlNode *&t)
{
	if(t==NULL)
		t=new AvlNode{x, NULL, NULL};

	else if(x < t->element)
		insert(x, t->left);
	else if(t->element < x)
		insert(x, t->right);
	balance(t);
}

int AVL_Tree::height(AvlNode *t) const{
	return t == NULL ? -1 : t->height;
}
