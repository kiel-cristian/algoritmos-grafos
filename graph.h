#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "bheap.h"
#include "btree.h"
#include <time.h>

class Graph{
private:
	ifstream file;
	E nodes;
	BinaryTree b_nodes;
	A a;
public:
	Graph(){
		file.open("NA.cedge", ios::in);
	}
	void read_file();
	void print();

	Edge get_edge(int element);
	A get_edges();
	E get_nodes();
	BinaryTree get_b_nodes();
	int edge_size();

	A radix_sorted_edges();
	A quick_sorted_edges();

	vector<A> get_conected_graphs(A _edges);
	int get_random_elem(int size);
	A get_one_random_graph(A _edges);
	A extract_conected_elements(A edges,Edge e);

	// bool find_node(int e);
};

void Graph::read_file(){
	string line;
	string buf;
	vector<string> tokens;
	int u,v,distance;
	Edge e;

	while( file.good() ){
		getline(file,line);
		// cout << line << endl;
		stringstream ss(line);
		while(ss >> buf){
			tokens.push_back(buf);
		}
		// cout << atoi(tokens.at(0).c_str()) << endl;
		u = atoi(tokens.at(1).c_str());
		v = atoi(tokens.at(2).c_str());
		distance = (int)(1000*atof(tokens.at(3).c_str()));
		tokens.clear();
		e.set(u,v,distance);
		a.push_back(e);

		b_nodes.insert_binary(u);
		b_nodes.insert_binary(v);

		// if(!find_node(u))
		// 	nodes.push_back(u);
		// if(!find_node(v))
		// 	nodes.push_back(v);

		// if(!(u < nodes.size() and nodes[u] == u)){
		// 	if(u >= nodes.size()){
		// 		nodes.push_back(u);
		// 	}
		// }
		// if(!(v < nodes.size() and nodes[v] == v)){
		// 	if(v >= nodes.size()){
		// 		nodes.push_back(v);
		// 	}
		// }
	}
	file.close();
}

// bool Graph::find_node(int node){
// 	for (int i = 0; i < nodes.size(); ++i)
// 	{
// 		if(nodes[i] == node)
// 			return true;
// 	}
// 	return false;
// }

void Graph::print(){
	Edge e;
	for (int i = 0; i < a.size(); ++i)
	{
		e = a.at(i);
		cout << "Arista (u,v) -> d: (" << e.u << " , " << e.v << ") -> " << e.distance << endl;
	}
}

Edge Graph::get_edge(int element){
	if(element < a.size() and element >= 0)
		return a.at(element);
	else
		return Edge();
}

int Graph::edge_size(){
	return a.size();
}

A Graph::get_edges(){
	return a;
}

E Graph::get_nodes(){
	return nodes;
}

BinaryTree Graph::get_b_nodes(){
	return b_nodes;
}

int Graph::get_random_elem(int size){
  /* initialize random seed: */
  srand ( time(NULL) );
  /* generate secret number: */
  return rand() % size;
}

A Graph::extract_conected_elements(A _edges,Edge first){
	A result;
	// bool more_elements, more_to_mark;
	Edge e = first;
	result.push_back(e);
	// more_to_mark = false;

	// do{
	for (int i = 0; i < result.size(); ){
		e = result[i];
		if(e.mark){
			i++;
			continue;
		}
		else{
			// more_to_mark = true;
			result[i].mark = true;
			i++;
		}

		// more_elements = false;
		for (int j = 0; j < _edges.size(); ++j){
			if(_edges[j].u == e.u or _edges[j].v == e.u or _edges[j].u == e.v or _edges[j].v == e.v ){
				result.push_back(_edges[j]);
				_edges.erase(_edges.begin() + j);
				// if(!more_elements)
				// 	more_elements = true;
			}
		}
	}
	// }
	// while( more_elements or more_to_mark);

	return result;
}

A Graph::get_one_random_graph(A _edges){
	A graph;
	int elem = get_random_elem(_edges.size());
	graph = extract_conected_elements(_edges,_edges[elem]);
	return graph;
}


vector<A> Graph::get_conected_graphs(A _edges){
	A edges = _edges;
	vector<A> graphs;

	A graph;
	do{
		graph = get_one_random_graph(edges);
		if(graph.size()>0){
			graphs.push_back(graph);
		}
	}
	while(edges.size() > 0);
}