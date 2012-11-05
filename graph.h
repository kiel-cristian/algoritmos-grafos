#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

class Edge{
public:
	int u,v;
	int distance;
	void set(int _u,int _v,int _distance){
		u = _u;
		v = _v;
		distance = _distance;
	}
};

typedef vector<int> E;
typedef vector<Edge> A;

class Graph{
private:
	ifstream file;
public:
	E e;
	A a;
	Graph(){
		file.open("NA.cedge", ios::in);
	}
	void read_file(){
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
	void print(){
		Edge e;
		for (int i = 0; i < a.size(); ++i)
		{
			e = a.at(i);
			cout << "Arista (u,v) -> d: (" << e.u << " , " << e.v << ") -> " << e.distance << endl;
		}
	}
};