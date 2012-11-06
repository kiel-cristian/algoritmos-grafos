#include "graph.h"

int main(){
	Graph g;
	g.read_file();
	// g.print();

	Bheap heap;
	int size = g.edge_size();

	Edge e;

	// e = g.get_edge(0);
	// heap.insert(e);
	// e = g.get_edge(1);
	// heap.insert(e);
	// e = g.get_edge(2);
	// heap.insert(e);
	// heap.print();

	cout << "Insertando ("<< size << ") vertices" << endl;

	for(int i = 0; i < size; ++i){
		cout << "i :" << i  << endl;
		if(i == 4){
			break;
		}
		e = g.get_edge(i);
		heap.insert(e);
	}
	heap.print();
	return 0;
}