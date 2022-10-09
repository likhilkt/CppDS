#include <iostream>
#include <cstring>
#define line "______________________________________________________________________________"<<endl;
#define trace /*cout<<__LINE__<<endl;*/
using namespace std;


class BTreeNode{
/* All public */
public:
	int *array; /* Keys */
	BTreeNode **childNodes; /* Array of child nodes */
	int t; /* degree */
	int n; /* number of keys */
	bool leaf; /* if leaf or not */
	
	BTreeNode():array(nullptr),childNodes(nullptr),t(0),n(0),leaf(false){}	
	BTreeNode(int t, bool leaf):array(nullptr),childNodes(nullptr),t(t),n(0),leaf(leaf){
		
		array = new int[t];
		childNodes = new BTreeNode*[t+1];
	
	}	
	
	void insertNonFull(int k);
	void split(BTreeNode *parent, BTreeNode* child);
	
	void print(){
		cout<<"[ ";
		for(int i=0;i<n;++i)
			cout<<array[i]<<", ";
		cout<<" ]"<<endl<<"child"<<endl;
		
		for(int i=0;i<=n;++i){
			if(childNodes[i])
				childNodes[i]->print();
		}
	}
};

class BTree{
private:
	void insert(BTreeNode* parent, BTreeNode* child, int value);
public:
	BTreeNode *root;
	//int t;
	int tt;
	
	BTree(int t1){
		tt = (2*t1) -1;
	//	t = t1;
		root = new BTreeNode(tt,true);
		
	}
	
	~BTree(){
		delete root;
	}
	
	void insert(int);
	void split(BTreeNode*, BTreeNode*);
	void print();
	int find(int k);
};

int BTree::find(int k){
	return 0;

}

void BTree::print(){
	cout<<line;
	BTreeNode* curr = root;
	while(curr){
		curr->print();
		curr = nullptr;
	}

}

void BTree::split(BTreeNode* parent, BTreeNode* child){

	int key = child->array[child->t/2];
	int i = 0;
	for(i = 0; i < parent->n; ++i){
		if(key <parent->array[i])
			break;
	
	}
	if(i != parent->n)
	{
		memmove(&(parent->array[i+1]), &(parent->array[i]), (parent->n-i)* sizeof(int));
		parent->array[i] = key;
		memmove(&(parent->childNodes[i+1]), &(parent->childNodes[i]), (parent->n-i + 1)* sizeof(BTreeNode*));
	}
	else{
		i = parent->n;
		parent->array[i] = key;
	}
	
	BTreeNode* _new = new BTreeNode(tt, child->leaf);
	parent->childNodes[i+1] = _new;
	parent->childNodes[i] = child;
	trace
	for(int i = child->t/2 + 1;i<child->n;++i){
		trace
		_new->array[_new->n] = child->array[i];
		_new->childNodes[_new->n] = child->childNodes[i];
		_new->n++;
		child->array[i] = 0;
		child->childNodes[i] = nullptr;
		trace
	}
	//* move last pointer -> n+1
	_new->childNodes[_new->n] = child->childNodes[child->n];
	child->childNodes[ child->n ] = nullptr;
	parent->n++;
	child->n = child->t/2 ;
	child->array[child->n + 1] = 0;
	trace;
	
}

void BTree::insert(int k){
	cout<<"ins start : "<<k<<endl;
	insert(nullptr, root, k);
	cout<<"ins end : "<<k<<endl;
}

void BTree::insert(BTreeNode* parent, BTreeNode*  node, int k){
	
	trace
	if(node->leaf){
		trace
		node->insertNonFull(k);
		trace
	}
	else{
		trace
		int i = 0;
		while(node->array[i] < k && i<node->n){
			i++;
		}
		trace
		//cout<<"i : "<<i<<endl;
		//cout<<" n : "<<node->n<<endl;
		insert(node, node->childNodes[i], k );
		trace
	}
	
	if(node->n == node->t ){
		cout<<"inter++++"<<endl;
		print();
		cout<<"end inter ++++"<<endl;
		if(parent){
			split(parent, node);
		}
		else{
			root = new BTreeNode(tt,false);
			split(root, node);
		}
	}
	trace
	
}

void BTreeNode::insertNonFull(int k){
	bool ins = false;
	for(int i=0;i<n;++i){
		if(array[i] > k){
			cout<<"moveeee"<<endl;
			for(int q=0;q<n;++q)
				cout<<array[q]<<",";
			cout<<endl;
			memmove(&array[i+1], &array[i], (n-i)* sizeof(int));
			
			for(int q=0;q<n;++q)
			cout<<array[q]<<",";
			cout<<endl;
			array[i]=k;
			n++;
			ins = true;
			for(int q=0;q<n;++q)
			cout<<array[q]<<",";
			cout<<endl;
			break;
		}
	}
	if(!ins){
		array[n++] = k;
	}
	else{
		//n++;
	}
	//cout<<"\nn : "<<n<<", t : "<<t<<endl;
}
