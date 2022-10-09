#include<iostream>
#include "btree.h"
using namespace std;

int main(){
	BTree *tree = new BTree(3);
	tree->insert(1);	
	tree->insert(2);
	tree->insert(3);
	tree->insert(4);
	tree->insert(5);
	tree->insert(6);
	tree->insert(7);
	tree->insert(8);
	tree->insert(10);
	tree->insert(11);
	tree->insert(12);
	tree->insert(7);
	tree->insert(7);
	while(true){
	int x;
	cin>>x;
	tree->insert(x);
	tree->print();
	
	}
	return 0;
}
