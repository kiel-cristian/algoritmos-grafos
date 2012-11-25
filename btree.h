#include <stdlib.h>
class BinaryTree{
public:
	BinaryTree *left,*rigth;
	int key;
	BinaryTree(){key = -1; left = NULL; rigth = NULL;}
	bool find_binary(int e);
	void insert_binary(int e);
	void to_array(E array_nodes);

	void print();
};

void BinaryTree::print(){
	if(left != NULL){
		cout << " <- ";
		left->print();
	}
	cout << "key: " << key << endl;
	if(rigth != NULL){
		cout << " -> ";
		rigth->print();
	}
}

void BinaryTree::insert_binary(int e){
	if(key == -1){
		key = e;
		return;
	}
	else{
		if(e > key){
			if(rigth == NULL){
				rigth = new BinaryTree();
			}
			rigth->insert_binary(e);
		}
		else{
			if(left == NULL){
				left = new BinaryTree();
			}
			left->insert_binary(e);
		}
	}
}

bool BinaryTree::find_binary(int e){
	if(key == -1)
		return false;
	else if( key == e)
		return true;

	if( e > key and rigth != NULL){
		rigth->find_binary(e);
	}
	else if(left!= NULL){
		left->find_binary(e);
	}
	return false;
}