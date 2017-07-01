#include "tree.h"

Tree::Tree ( int id1, int diam1, string status1, string health1, 
           string spc1, int zip1, string boro1, double x1, double y1 ){

	id=id1;
	diam=diam1;
	status=status1;
	health=health1;
	spc=spc1;
	zip=zip1;
	boro=boro1;
	x=x1;
	y=y1;
}

 bool operator==(const Tree & t1, const Tree & t2){

	return(t1.id==t2.id&&t1.spc==t2.spc);
}

bool samename(const Tree & t1, const Tree & t2){
	return (t1.spc==t2.spc);
}


bool islessname(const Tree & t1, const Tree & t2){
	return (t1.spc<t2.spc);
}

bool operator<(const Tree & t1, const Tree & t2){

	if(t1.spc<t2.spc)
		return true;
	else if(t1.spc==t2.spc){
		if(t1.id<t2.id)
			return true;
		else
			return false;
	}
	else
		return false;
}

ostream& operator<< (ostream & os, const Tree & t ){

	os<<t.spc<<" "<<t.id;
	os<<" "<<t.boro<<" "<<t.zip;
	os<<" "<<t.diam<<" "<<t.status;
	os<<" "<<t.health<<" "<<t.x<<" "<<t.y;
	os<<endl;
	return os;
}
