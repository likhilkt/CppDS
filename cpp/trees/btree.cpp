#include <iostream>
#include <cstring>
#define line "______________________________________________________________________________"<<endl;
#define trace /*cout<<__LINE__<<endl;*/
using namespace std;

class Node{
public:
    int t;
    int* key;
    Node** child;
    int n;
    int keyMax, nodeMax;
    bool leaf;

    void show(){

        /*if(!leaf){
            for(int i=0;i<n+1; ++i){
                child[i]->show();
            }
        }
        cout<<"[";
        for(int i=0;i<n;++i){
            cout<<key[i]<<", ";
        }
        cout<<"]"<<endl;
        */
         int i;
        for (i = 0; i < n; i++)
        {
            // If this is not leaf, then before printing key[i],
            // traverse the subtree rooted with child C[i].
            if (leaf == false)
                child[i]->show();
            cout << " " << key[i];
        }
    
        // Print the subtree rooted with last child
        if (leaf == false)
            child[i]->show();

    }

    Node(int t1){
        t = t1;
        nodeMax = 2*t;
        keyMax = nodeMax - 1;
        n = 0;
        key = new int[keyMax];
        child = new Node*[nodeMax];
        leaf = false;
    }

    void splitChild(int I, Node* node){
        Node* newNode = new Node(t);
        newNode->leaf = node->leaf;
        newNode->n = t-1;

        for(int i=0;i<t-1; ++i){
            newNode->key[i] = node->key[i + t];
        }
        for(int i=0;i<t; ++i){
            newNode->child[i] = node->child[i + t];
            node->child[i+t] = nullptr;
        }
        node->n = t-1;

        for(int i=n;i>=I+1;--i){
            child[i+1] = child[i];
        }        
        child[I+1] = newNode;
        for(int i=n-1;i>=I;--i){
            key[i+1] = key[i];
        }
        key[I] = node->key[t-1];
        n++;
    }
    void insertNonFull(int value){
        if(leaf){
            int i = n-1;
            for(; i>=0 && value < key[i];--i){
                key[i+1] = key[i];
            }
            //cout<<"\noomb : "<<i<<"\n";
            key[i+1] = value;
            n++;
        }
        else{
            int i = n-1;
            while(value <= key[i] && i>=0)
                i--;
            if(child[i+1]->n == keyMax){
                splitChild(i+1, child[i+1]);
                if(key[i+1] < value){
                    cout<<"\n i going to ++ "<<i<<endl;
                    i++;
                }
            }
            cout<<"\n i value in else "<<i+1<<endl;
            child[i+1]->insertNonFull(value);
        }
    }

    

};

class BTree{
public:
    Node* root;
    int t;

    BTree(int x):t(x),root(nullptr){}

    void insert(int value){
        cout<<"start START"<<endl;
        if(!root){
            root = new Node(t);
            root->key[0] = value;
            root->n = 1;
            root->leaf = true;
        }
        else{
            if(root->n == root->keyMax){
                Node* node = new Node(t);
                node->child[0] = root;

                node->splitChild(0,root);

                if(node->key[0]>value){
                    node->child[0]->insertNonFull(value);
                }
                else{
                    node->child[1]->insertNonFull(value);
                }

                root = node;
            }
            else{
                root->insertNonFull(value);
            }
        }

        printf("\nAfter inserting [%d]\n",value);
        //show();
    }
   

    void show(){
        root->show();
    }
};


int main(){

    BTree* tree = new BTree(3);
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
    //tree->show();
	while(true){
	int x;
	cin>>x;
	tree->insert(x);
	tree->show();
	
	}

    return 0;
}