#include <vector>
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