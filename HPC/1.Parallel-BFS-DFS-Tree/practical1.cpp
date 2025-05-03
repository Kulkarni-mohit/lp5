#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>

using namespace std;

struct treenode{
    int data;
    vector<treenode*> children;
    treenode(int val) : data(val) {}
};

class Tree{
    treenode* root;

public:
    Tree(int val){
        treenode* newNode = new treenode(val);
        root = newNode;
    }

    void addChild(treenode* parent, int val){
		treenode* temp = new treenode(val);
		parent->children.push_back(temp);
	}
	
	treenode* getroot(){
		return root;
	}
	
	void parallelDFS(treenode* node){
		cout<<node->data<<" ";
		
		#pragma omp parallel for
		for(size_t i=0; i<node->children.size() ; ++i)
            #pragma omp critical
			parallelDFS(node->children[i]);
	}

    void parallelBFS(){
        queue<treenode*> q;
        q.push(root);

        while(!q.empty()){
            treenode* current = q.front();
            q.pop();
            cout << current->data << " ";

            #pragma omp parallel for
            for(size_t i = 0; i < current->children.size(); ++i) {
                #pragma omp critical
                q.push(current->children[i]);
            }
        }
    }

};

int main(){
	Tree tree(1);
	
	treenode* root = tree.getroot();
	tree.addChild(root,2);
	tree.addChild(root,3);
	tree.addChild(root,4);
	
	treenode* node2 = root->children[0];
	tree.addChild(node2,5);
	tree.addChild(node2,6);
	
	tree.parallelDFS(root);

    cout<<"\n";
    tree.parallelBFS();
    return 0;	
}