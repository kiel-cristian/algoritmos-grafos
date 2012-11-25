#include <math.h>
#include "edge.h"
#include <iostream>

using namespace std;

struct Heap{
	private:
		vector<Edge> heap;
	public:
		void insert(Edge e);
		void heap_insert(Edge e);
		Edge get_min();
		void delete_min();
		void print(int elem);

		Heap(){size = 0;}

		Heap(Edge e){
            heap.push_back(e);
            size = 1;
        }
        bool is_empty();
        void delete_all();
        void heapify(A edges);
    private:
    	int size;
    	void switch_items(int a,int b);
		bool empty_at(int elem);

		void propagate_to_last(int elem);
		void heap_sort(int elem);
		void propagate_to_root(int elem);
};

void Heap::delete_all(){
	heap.erase(heap.begin(),heap.end());
}

bool Heap::is_empty(){
	return size == 0;
}

bool Heap::empty_at(int elem){
	return elem >= size;
}

void Heap::print(int elem){
	Edge e = heap.at(elem);
	int i = 2*elem;
	if(!empty_at(i+1)){
		cout << " <- ";
		print(i+1);
	}
	cout << "key: " << e.distance << endl;
	if(!empty_at(i+2)){
		cout << " -> ";
		print(i+2);
	}
}

void Heap::switch_items(int a,int b){
	Edge new_b = heap.at(a);
	Edge new_a = heap.at(b);

	heap.at(a) = new_a;
	heap.at(b) = new_b;
}

void Heap::heap_sort(int elem){
	if(elem >= size){
		return;
	}

	Edge e = heap.at(elem);
	Edge l,r;

	int child_l = elem*2+1, child_r = elem*2+2;

	heap_sort(child_l);
	heap_sort(child_r);

	if(!empty_at(child_l) and !empty_at(child_r)){
		l = heap[child_l];
		r = heap[child_r];

		if( l.distance < r.distance and l.distance < e.distance){
			// switch_items(elem,child_l);
			heap[elem] = l;
			heap[child_l] = e;
		}
		else if(r.distance < l.distance and r.distance < e.distance){
			// switch_items(elem,child_r);
			heap[elem] = r;
			heap[child_r] = e;
		}
	}
	else if(!empty_at(child_l)){
		l = heap[child_l];
		if( l.distance < e.distance){
			// switch_items(elem,child_l);
			heap[elem] = l;
			heap[child_l] = e;
		}
	}
	else if(!empty_at(child_r)){
		r = heap[child_r];
		if( r.distance < e.distance){
			// switch_items(elem,child_r);
			heap[elem] = r;
			heap[child_r] = e;
		}
	}
}

void Heap::propagate_to_last(int elem){
	Edge e = heap.at(elem);
	Edge left,rigth;

	int child_l = elem*2+1, child_r = elem*2+2;


	if(!empty_at(child_l) and !empty_at(child_r)){
		left = heap.at(child_l);
		rigth = heap.at(child_r);

		if(left.distance < rigth.distance){
			if(left.distance < e.distance){
				switch_items(elem,child_l);
				propagate_to_last(child_l);
			}
		}
		else if(rigth.distance < e.distance){
			switch_items(elem,child_r);
			propagate_to_last(child_r);
		}
	}
	else if(!empty_at(child_l)){
		left = heap.at(child_l);
		if(left.distance < e.distance){
			switch_items(elem,child_l);
			propagate_to_last(child_l);
		}
	}
	else if(!empty_at(child_r)){
		rigth = heap.at(child_r);
		if(rigth.distance < e.distance){
			switch_items(elem,child_r);
			propagate_to_last(child_r);
		}
	}
}

void Heap::propagate_to_root(int elem){
	if(elem == 0){
		return;
	}
	Edge e = heap.at(elem);

	int father = elem/2;
	if(elem % 2 == 0)
		father--;

	Edge f = heap.at(father);

	if(e.distance < f.distance){
		heap.at(father) = e;
		heap.at(elem) = f;
		propagate_to_root(father);
	}
}

Edge Heap::get_min(){
	return heap.at(0);
}

void Heap::delete_min(){

	Edge last = heap.back();
	heap.pop_back();
	size--;

	if(size == 0)
		return;

	heap.erase(heap.begin());
	heap.insert(heap.begin(),last);

	propagate_to_last(0);
}

void Heap::insert(Edge e){
	heap.push_back(e);
	propagate_to_root(size++);
}

void Heap::heap_insert(Edge e){
	heap.push_back(e);
	size++;
}

void Heap::heapify(A edges){
	Edge e;
	delete_all();
	int s = edges.size();

	for (int i = 0; i < s; ++i)
	{
		e = edges.at(i);
		insert(e);
	}
}