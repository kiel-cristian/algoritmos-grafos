#include <vector>
using namespace std;

class Edge{
public:
	int u,v;
	int distance;
	bool mark;
	void set(int _u,int _v,int _distance){
		u = _u;
		v = _v;
		distance = _distance;
	}
	Edge(){mark = false;}
};

typedef vector<int> E;
typedef vector<Edge> A;