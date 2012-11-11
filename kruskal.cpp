#include "graph.h"

void test(){
	Graph g;
	g.read_file();
	Bheap heap;
	int size = g.edge_size();
	Edge e;

	cout << "Insertando ("<< size << ") vertices" << endl;

	for(int i = 0; i < size; ++i){
		e = g.get_edge(i);
		heap.insert(e);
	}

	// heap.print();

	for (int i = 0; i < size; ++i){
		// cout << "heap1 min: " << heap.get_min() << endl;
		heap.delete_min();
	}
}

void test2(){
	Graph g;
	g.read_file();
	Bheap heap;
	int size = g.edge_size();
	Edge e;

	cout << "Insertando ("<< size << ") vertices" << endl;

	heap.heapify(g.get_edges());

	// heap.print();

	for (int i = 0; i < size; ++i)
	{
		// cout << "heap2 min: " << heap.get_min() << endl;
		heap.delete_min();
	}
}

int main(){
	// test();
	// test2();

	
}