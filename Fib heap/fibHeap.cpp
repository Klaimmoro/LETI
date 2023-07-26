#include "fibHeap.h"

fibNode::fibNode()
{
}

fibNode::fibNode(double value){
	this->parent = nullptr;
	this->l = nullptr;
	this->r = nullptr;
	this->child = nullptr;
	this->data = value;
	this->mark = false;
	this->degree = 0;
}

void fibHeap::add(double value){
	fibNode* newNode = new fibNode(value);
	if (size == 0) {
		min = new fibNode(value);
		min->l = min;
		min->r = min;
	}
	else {
		fibNode* prevR = min->r;
		min->r = newNode;
		newNode->l = min;
		newNode->r = prevR;
		prevR->l = newNode;
	}
	if (min->data > newNode->data) {
		min = newNode;
	}
	size++;

}

void fibHeap::unionHeaps(fibNode* merge, int mergesize){
	if (merge == nullptr) return;
	if (min == nullptr) {
		min = merge;
		size = mergesize;
	}
	else {
		fibNode* l = merge->l;
		cout << l->data << endl;
		fibNode* r = min->r;
		cout << r->data << endl;
		min->r = merge;
		merge->l = min;
		l->r = r;
		r->l = l;
		size += mergesize;
	}
}

void fibHeap::delMin(){
	if (min == nullptr)
		cout << "The heap is empty" << endl;
	else {
		fibNode* tmp = min;
		fibNode* pntr;
		pntr = tmp;
		fibNode* x = NULL;
		if (tmp->child != NULL) {

			x = tmp->child;
			do {
				pntr = x->r;
				(min->l)->r = x;
				x->r = min;
				x->l = min->l;
				min->l = x;
				if (x->data < min->data)
					min = x;
				x->parent = NULL;
				x = pntr;
			} while (pntr != tmp->child);
		}

		(tmp->l)->r = tmp->r;
		(tmp->r)->l = tmp->l;
		min = tmp->r;
		if (tmp == tmp->r && tmp->child == NULL)
			min = NULL;
		else {
			min = tmp->r;
			consolidate();
		}
		size--;
	}
}

void fibHeap::consolidate(){
	int temp1;
	float temp2 = (log(size));
	int temp3 = temp2;
	fibNode** arr;
	arr = new fibNode * [temp3 + 1];
	for (int i = 0; i <= temp3; i++)
		arr[i] = NULL;
	fibNode* ptr1 = min;
	fibNode* ptr2;
	fibNode* ptr3;
	fibNode* ptr4 = ptr1;
	do {
		ptr4 = ptr4->r;
		temp1 = ptr1->degree;
		while (arr[temp1] != nullptr) {
			ptr2 = arr[temp1];
			if (ptr1->data > ptr2->data) {
				ptr3 = ptr1;
				ptr1 = ptr2;
				ptr2 = ptr3;
			}
			if (ptr2 == min)
				min = ptr1;
			merge(ptr2, ptr1);
			if (ptr1->r == ptr1)
				min = ptr1;
			arr[temp1] = NULL;
			temp1++;
		}
		arr[temp1] = ptr1;
		ptr1 = ptr1->r;
	} while (ptr1 != min);
	min = NULL;
	for (int j = 0; j <= temp3; j++) {
		if (arr[j] != NULL) {
			arr[j]->l = arr[j];
			arr[j]->r = arr[j];
			if (min != NULL) {
				(min->l)->r = arr[j];
				arr[j]->r = min;
				arr[j]->l = min->l;
				min->l = arr[j];
				if (arr[j]->data < min->data)
					min = arr[j];
			}
			else {
				min = arr[j];
			}
			if (min == NULL)
				min = arr[j];
			else if (arr[j]->data < min->data)
				min = arr[j];
		}
	}
}

void fibHeap::merge(fibNode* ptr2, fibNode* ptr1){
	(ptr2->l)->r = ptr2->r;
	(ptr2->r)->l = ptr2->l;
	if (ptr1->r == ptr1)
		min = ptr1;
	ptr2->l = ptr2;
	ptr2->r = ptr2;
	ptr2->parent = ptr1;
	if (ptr1->child == NULL)
		ptr1->child = ptr2;
	ptr2->r = ptr1->child;
	ptr2->l = (ptr1->child)->l;
	((ptr1->child)->l)->r = ptr2;
	(ptr1->child)->l = ptr2;
	if (ptr2->data < (ptr1->child)->data)
		ptr1->child = ptr2;
	ptr1->degree++;
}

fibNode* fibHeap::GetHead()
{
	return min;
}


void Dijkstra(fibHeap s, double** Matrix)
{
	//cout << "End startPoint: ";
	int a = 4;
	//cout << "Enter finishPoint: ";
	int key = 1;
	int Dist[5];
	Dist[a] = 0;
	for (int i = 0; i < 5; i++) {
		if (i != a) {
			Dist[i] = 100000;
		}
	}
	bool marked[5];
	marked[a] = true;
	s.add(a);
	for (int i = 0; i < 5; i++) {
		if (i != a) {
			marked[i] = false;
		}
	}
	int currVersh = a;
	while (marked[key] != true) {
		for (int j = 0; j < 5; j++) {
			if (Matrix[currVersh][j] != 0) {
				if (marked[j] == false) {
					if (Matrix[currVersh][j] + Dist[currVersh] < Dist[j]) {
						Dist[j] = Matrix[currVersh][j] + Dist[currVersh];
					}
				}
			}
		}
		int min = 100000;
		int minInd = 0;
		for (int j = 0; j < 5; j++) {
			if (marked[j] == false) {
				if (min > Dist[j]) {
					min = Dist[j];
					minInd = j;
				}
			}
		}
		marked[minInd] = true;
		if (Matrix[minInd][key] != 0) { s.add(minInd); }
		if (minInd == key) { s.add(minInd); break; }
		currVersh = minInd;
	}
	cout << "quickest way: " << Dist[key] << endl;
	fibNode* cons = s.GetHead();
	while (cons->r != s.GetHead()) {
		cout << cons->data << "--";
		cons = cons->r;
	}
	cout << cons->data;

}
