#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "bheap.h"

class Graph{
private:
	ifstream file;
	E e;
	A a;
public:
	Graph(){
		file.open("NA.cedge", ios::in);
	}
	void read_file();
	void print();

	Edge get_edge(int element);
	int edge_size();

	A radix_sorted_edges();
	A quick_sorted_edges();
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

	}
	file.close();
}
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