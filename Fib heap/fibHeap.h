#pragma once
#include <iostream>
using namespace std;
class fibNode {
public:
	fibNode* parent;
	fibNode* l;
	fibNode* r;
	fibNode* child;
	int degree;
	double data;
	bool mark;
	fibNode();
	fibNode(double value);
};

class fibHeap {
public:
	fibNode* min;
	int size;

	void add(double value);

	void unionHeaps(fibNode* merge, int mergesize);

	void delMin();

	void consolidate();

	void merge(fibNode* ptr2, fibNode* ptr1);

	fibNode* GetHead();

};

void Dijkstra(fibHeap s, double** Matrix);