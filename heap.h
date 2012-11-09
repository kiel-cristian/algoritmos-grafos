#include <math.h>
#include "edge.h"
#include <iostream>

using namespace std;

struct Heap{
	private:
		vector<Edge> heap;
		int elements;
	public:
		void insert(Edge e);
		void heap_insert(Edge e);
		int get_min();
		int delete_min();
		void print(int elem);

		// void propagate_switch();

		Heap(){elements = 0;}

		Heap(Edge e){
            heap.push_back(e);
            elements = 1;
        }
        bool is_empty();
        void delete_all();
        void heapify(A edges);
    private:
		bool empty_at(int elem);

		void propagate_to_last(int elem);
		void propagate_to_root(int elem);
};

void Heap::delete_all(){
	heap.erase(heap.begin(),heap.begin() + heap.size()-1);
	elements = 0;
}

bool Heap::is_empty(){
	return elements == 0;
}

bool Heap::empty_at(int elem){
	return elem >= elements;
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

void Heap::propagate_to_last(int elem){
	Edge e = heap.at(elem);

	if(!empty_at(elem*2+2)){
		Edge r = heap.at(2*elem+2);
		if(r.distance < e.distance){
			heap.at(elem) = r;
			heap.at(2*elem+2) = e;
		}
	}
	else if(!empty_at(elem*2+1)){
		Edge l = heap.at(2*elem+1);
		if(l.distance < e.distance){
			heap.at(elem) = l;
			heap.at(2*elem+1) = e;
		}
	}
}

void Heap::propagate_to_root(int elem){
	if(elem == 0){
		return;
	}

	Edge e = heap.at(elem);
	int father = elem/2;
	Edge f = heap.at(father);

	if(e.distance < f.distance){
		heap.at(father) = e;
		heap.at(elem) = f;
		propagate_to_root(father);
	}
	else{
		return;
	}
}

int Heap::get_min(){
	return heap.at(0).distance;
}

int Heap::delete_min(){
	Edge last = heap.back();
	heap.pop_back();
	propagate_to_last(0);
}

void Heap::insert(Edge e){
	heap.push_back(e);
	propagate_to_root(elements++);
}

void Heap::heap_insert(Edge e){
	heap.push_back(e);
}

void Heap::heapify(A edges){
	Edge e = edges.at(0);
	delete_all();
	for (int i = 1; i < edges.size(); ++i)
	{
		e = edges.at(i);
		heap_insert(e);
	}
	propagate_to_last(0);
}