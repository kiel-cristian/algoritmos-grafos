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

	Bheap(){create_root();}
};

bool Bheap::is_empty(){
	return root == NULL;
}

void Bheap::create_root(){
	root = NULL;
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
		int min = root.delete_min();
		if(min < 0){
			root = NULL;
		}
	}
}

void Bheap::insert(Edge e){
	if(is_empty())
		root = new Heap(e);
	else
		root.insert(e);
}

void Bheap::heapify(A edges){
	Edge e = edges.at(0);
	root = new Heap(e);
	for (int i = 1; i < edges.size(); ++i)
	{
		e = edges.at(i);
		root.heap_insert(e);
	}

	root.propagate_switch();
}
