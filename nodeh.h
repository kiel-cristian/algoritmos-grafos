#include <math.h>
#include "edge.h"
#include <iostream>

using namespace std;

struct NodeH{
	public:
		NodeH* left,*rigth;
		int key,u,v,num_elements;
		void insert(Edge e);
		void heap_insert(Edge e);
		int get_min();
		int delete_min();
		void print();
		void propagate_switch();

		NodeH(Edge e){
            key = e.distance;
            u= e.u;
            v= e.v;
            left = NULL;
            rigth = NULL;
        }
    private:
		NodeH *get_last();
		NodeH *get_last_recursive();
		void update_num_elements();

		NodeH *copy();
		bool is_leaf();
		bool is_empty();
		bool empty_childs();
		bool empty_left();
		bool empty_rigth();

		void switch_with_child(NodeH *child);
		void set(int _key,int _u,int _v);
};

bool NodeH::is_leaf(){
	return num_elements == 0 || num_elements == 1;
}

bool NodeH::is_empty(){
	return num_elements == 0;
}

bool NodeH::empty_childs(){
	return left == NULL and rigth == NULL;
}

bool NodeH::empty_left(){
	return left == NULL;
}

bool NodeH::empty_rigth(){
	return rigth == NULL;
}

void NodeH::print(){
	if(not empty_left()){
		cout << " <- ";
		left->print();
	}
	cout << "key: " << key << endl;

	if(not empty_rigth()){
		cout << " -> ";
		rigth->print();
	}
}

void NodeH::update_num_elements(){
	num_elements = 0;
	if( not empty_rigth())
		num_elements += rigth->num_elements;
	if(not empty_left())
		num_elements += left->num_elements;
	if(not is_empty())
		num_elements++;
}

NodeH *NodeH::copy(){
	Edge e;
	e.set(key,u,v);
	NodeH *copy = new NodeH(e);
	return copy;
}

void NodeH::set(int _key,int _u,int _v){
	key = _key;
	u = _u;
	v = _v;
}

NodeH *NodeH::get_last(){
	if(is_empty())
		return NULL;
	else
		return get_last_recursive();
}

NodeH *NodeH::get_last_recursive(){
	if(empty_childs()){
		NodeH *find  = this->copy();
		return find;
	}

	float log2result = log(num_elements)/log(2.0);
	int base = (int) log2result;
	NodeH *find = NULL;
	bool this_is_last;

	if(log2result < base + 0.5){
		if(!empty_left()){
			find = left->get_last_recursive();
			if(left->empty_childs())
				left = NULL;
		}
		else{
			find = this->copy();
		}
	}
	else{
		if(!empty_rigth()){
			find = rigth->get_last_recursive();
			if(rigth->empty_childs())
				rigth = NULL;
		}
		else{
			find = this->copy();
		}
	}
	update_num_elements();
	return find;
}

void NodeH::switch_with_child(NodeH *child){
	int _key,_u,_v;
	_key = key;
	_u = u;
	_v = v;
	set(child->key,child->u,child->v);
	child->set(_key,_u,_v);
}

void NodeH::propagate_switch(){
	if(is_leaf() or is_empty()){
		return;
	}

	if(!empty_rigth() and key > rigth->key){
		switch_with_child(rigth);
		rigth->propagate_switch();
	}
	else if(!empty_left() and key > left->key){
		switch_with_child(left);
		left->propagate_switch();
	}
}

int NodeH::get_min(){
	if(is_leaf())
		return key;
	else
		return -1;
}

int NodeH::delete_min(){
	if(is_leaf()){
		return -1;
	}
	else{
		NodeH* last = get_last();
		set(last->key,last->u,last->v);
		propagate_switch();
	}
}

void NodeH::insert(Edge e){
	float log2result = log(num_elements + 1)/log(2.0);
	int base = (int) log2result;

	if(log2result < base + 0.5){
		if(empty_left()){
			left = new NodeH(e);
		}
		else{
			left->insert(e);
		}
		if(key > left->key){
			switch_with_child(left);
		}
	}
	else{
		if(empty_rigth()){
			rigth = new NodeH(e);
		}
		else{
			rigth->insert(e);
		}
		if(key > rigth->key){
			switch_with_child(rigth);
		}
	}
	update_num_elements();
}

void NodeH::heap_insert(Edge e){
	float log2result = log(num_elements + 1)/log(2.0);
	int base = (int) log2result;

	if(log2result < base + 0.5){
		if(empty_left()){
			left = new NodeH(e);
		}
		else{
			left->insert(e);
		}
		update_num_elements();
	}
	else{
		if(empty_rigth()){
			rigth = new NodeH(e);
		}
		else{
			rigth->insert(e);
		}
	}
	update_num_elements();
}