#include "graph.h"

class KClass{
public:
	E elements;
	BinaryTree b_elements;
	int size;
	KClass(int e){
		elements.push_back(e);
		b_elements.insert_binary(e);
		size = 1;
	}
	bool k_find(int e);
	void k_union(int e);
};

void KClass::k_union(int new_e){
	elements.push_back(new_e);
	b_elements.insert_binary(new_e);
	size++;
}

bool KClass::k_find(int e){
	if( size <= 16){
		for (int i = 0; i < size; ++i){
			if(elements[i] == e)
				return true;
		}
		return false;
	}
	else{
		return b_elements.find_binary(e);
	}
}

void BinaryTree::to_array(E array_nodes){
	if( left!= NULL)
		left->to_array(array_nodes);

	array_nodes.push_back(key);

	if( rigth!= NULL)
		rigth->to_array(array_nodes);
}

E btree_to_e(BinaryTree nodes){
	E array_nodes;
	nodes.to_array(array_nodes);
	return array_nodes;
}

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
	Graph g;
	g.read_file();
	Bheap heap;
	int size = g.edge_size();
	Edge e;
	cout << "Insertando ("<< size << ") vertices" << endl;
	heap.heapify(g.get_edges());

	cout << "Generando MST" << endl;

	// E nodes = g.get_nodes();
	E nodes = btree_to_e(g.get_b_nodes());

	cout << "Número de nodos del grafo : " << nodes.size() << endl;
	cout << "Número de aristas del grafo : "<< size << endl;

	vector<KClass> classes;

	BinaryTree mst_nodes;
	A mst_edges;

	cout << "Creando clases" << endl;

	for (int i = 0; i < nodes.size(); ++i){
		classes.push_back(KClass(nodes[i]));
	}

	Edge min_node;

	cout << "Iniciando algoritmo Kruskal" << endl;

	while(!heap.is_empty()){

		min_node = heap.get_min();

		int u_class = -1, v_class = -1;

		for (int i = 0; i < classes.size() and (u_class == -1 or v_class == -1); ++i){
			if(classes[i].k_find(min_node.u)){
				u_class = i;
			}

			if(classes[i].k_find(min_node.v)){
				v_class = i;
			}

		}

		if( u_class == -1 or v_class == -1){
			cout << "Error!!" << endl;
			cout << "u class: " << u_class << endl;
			cout << "v class: " << v_class << endl;

			cout << "u node: " << min_node.u << endl;
			cout << "v node: " << min_node.v << endl;
			break;
		}


		if( u_class != v_class){
			cout << "Borrando clase: " << v_class << endl;
			classes.erase(classes.begin() + v_class);
			classes[u_class].k_union(v_class);

			/*Agrego nodos a arbol de nodos*/
			mst_nodes.insert_binary(min_node.u);
			mst_nodes.insert_binary(min_node.v);

			/*Agrego arista*/
			mst_edges.push_back(min_node);
		}
		heap.delete_min();
	}

}