#include <vector>

class Vertex{
public:
	int key;
};

class Arist{
public:
	Vertex u,v;
	int distance;
};

typedef vector<Vertex> E;
typedef vector<Arist> A;

class Graph{
public:
	E e;
	A a;
};