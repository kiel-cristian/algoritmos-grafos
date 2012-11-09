#include "heap.h"

class Bheap{
private:
	Heap root;
	void create_root();
	bool is_empty();

public:
	void insert(Edge e);
	int get_min();
	void delete_min();
	void print();
	void heapify(A edges);
};

bool Bheap::is_empty(){
	return root.is_empty();
}

void Bheap::print(){
	if(!is_empty())
		root.print(0);
	else
		cout << "Empty Bheap" << endl;
}

int Bheap::get_min(){
	int min;
	if(is_empty())
		return -1;
	else
		return root.get_min();
}

void Bheap::delete_min(){
	if(is_empty())
		return;
	else{
		root.delete_min();
	}
}

void Bheap::insert(Edge e){
	root.insert(e);
}

void Bheap::heapify(A edges){
	root.heapify(edges);
}
