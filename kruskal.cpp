#include "graph.h"

class BinaryTree{
public:
	BinaryTree *left,*rigth;
	int key;
	BinaryTree(){key = -1; left = NULL; rigth = NULL;}
	bool find_binary(int e);
	void insert_binary(int e);
};

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

	E nodes = g.get_nodes();

	vector<KClass> classes;

	BinaryTree mst_nodes;
	A mst_edges;

	for (int i = 0; i < nodes.size(); ++i){
		classes.push_back(KClass(nodes[i]));
	}

	Edge min_node;

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

		if( u_class != v_class){
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