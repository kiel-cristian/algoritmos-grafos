#include <math.h>
#include <iostream>

using namespace std;

class Leaf{
public:
	int key,u,v,num_elements;
	bool bottom;
	void insert(int _key,int _u,int _v){key=_key;u=_u;v=_v;bottom= true;}
	void switch_bottom(){bottom = false;}
};


class Bheap{
public:
	void insert(int _u,int _v,int _key);
	int get_min();
	void delete_min();
	void print();

	Bheap(){key=-1;u=-1;v=-1;num_elements=0;left=NULL;rigth=NULL;}

private:
	int key,u,v,num_elements;
	Bheap *left, *rigth;
	Leaf get_last();
	void update_num_elements();

	bool is_leaf();
	bool is_empty();
	bool empty_childs();
	bool empty_left();
	bool empty_rigth();

	void switch_with_child(Bheap *child);
	void propagate_switch();
	void set(int _key,int _u,int _v);
};

bool Bheap::is_leaf(){
	return num_elements == 1;
}

bool Bheap::is_empty(){
	return num_elements == 0;
}

bool Bheap::empty_childs(){
	return left == NULL and rigth == NULL;
}

bool Bheap::empty_left(){
	return left == NULL;
}

bool Bheap::empty_rigth(){
	return rigth == NULL;
}

void Bheap::print(){
	if(not empty_left()){
		left->print();
	}
	cout << "key: " << key << endl;

	if(not empty_rigth()){
		rigth->print();
	}
}

void Bheap::update_num_elements(){
	num_elements = 0;
	if( not empty_rigth())
		num_elements += rigth->num_elements;
	if(not empty_left())
		num_elements += left->num_elements;
	if(not is_empty())
		num_elements++;
}

Leaf Bheap::get_last(){
	if(empty_childs()){
		Leaf find;
		find.insert(u,v,key);
		// this = NULL;
		// *this = Bheap();
		return find;
	}

	float log2result = log(num_elements)/log(2.0);
	int base = (int) log2result;
	Leaf find;

	if(log2result < base + 0.5){
		find = left->get_last();
		if(find.bottom){
			left = NULL;
			find.switch_bottom();
		}
	}
	else{
		find = rigth->get_last();
		if(find.bottom){
			rigth = NULL;
			find.switch_bottom();
		}find.switch_bottom();
	}
	update_num_elements();
	return find;
}


void Bheap::switch_with_child(Bheap *child){
	int _key,_u,_v;
	_key = key;
	_u = u;
	_v = v;

	set(child->key,child->u,child->v);
	child->set(_key,_u,_v);
}

void Bheap::propagate_switch(){
	if(is_leaf() or is_empty()){
		return;
	}

	if(!empty_rigth() and key > left->key){
		switch_with_child(left);
		left->propagate_switch();
	}
	else if(!empty_left() and key > rigth->key){
		switch_with_child(rigth);
		rigth->propagate_switch();
	}
}

void Bheap::set(int _key,int _u,int _v){
	key = _key;
	u = _u;
	v = _v;
}

int Bheap::get_min(){
	int k = key;
	delete_min();
	return k;
}

void Bheap::delete_min(){
	if(is_leaf()){
		key = -1;u=-1,v=-1,left=NULL,rigth=NULL,num_elements=0;
		return;
		// *this = Bheap();
	}
	else{
		Leaf last = get_last();
		set(last.key,last.u,last.v);
		propagate_switch();
	}
}

void Bheap::insert(int _key,int _u,int _v){
	if(is_empty()){
		key = _key;
		u = _u;
		v = _v;
		num_elements = 1;
		// *left = Bheap();
		// *rigth = Bheap();
		return;
	}

	float log2result = log(num_elements + 1)/log(2.0);
	int base = (int) log2result;

	if(log2result < base + 0.5){
		if(empty_left())
			*left = Bheap();

		left->insert(_key,_u,_v);
		update_num_elements();

		if(key > left->key){
			switch_with_child(left);
		}
	}
	else{
		if(empty_rigth())
			*rigth = Bheap();

		rigth->insert(_key,_u,_v);
		update_num_elements();

		if(key > rigth->key){
			switch_with_child(rigth);
		}
	}
}