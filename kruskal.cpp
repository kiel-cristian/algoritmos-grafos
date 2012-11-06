#include "graph.h"
#include "bheap.h"

int main(){
	Graph g;
	g.read_file();
	// g.print();

	Bheap heap;
	int size = g.edge_size();

	Edge e;

	e = g.get_edge(0);
	heap.insert(e.distance,e.u,e.v);
	// e = g.get_edge(1);
	// heap.insert(e.distance,e.u,e.v);
	heap.print();

	cout << "Insertando ("<< size << ") vertices" << endl;

	// int i = 0;

	// for(i = 1; i < size; ++i){
		// cout << "Algo extraño pasa" << endl;
	// 	cout << "i :" << i  << endl;
	// 	if(i == 3){
	// 		break;
	// 	}
		// e = g.get_edge(i);
		// heap.insert(e.distance,e.u,e.v);
	// }
	// heap.print();
	return 0;
}