#include <iostream>
using namespace std;



class Node
{
public:
	int index;
	int data;
	Node* next;
	Node(int index,int flag);
};


Node::Node(int index,int flag){
	int Value;
	if (flag == 0) {
		cout << "Enter value: ";
		cin >> Value;
		this->data = Value;
	}
	this->index = index;
	this->next = nullptr;
}


class List {
public:
	int Size;
	Node* head;

	List();

	void addFirst(int i);

	void deleteFirst();

	void addEnd();

	void deleteEnd();

	void deleteIndex();

	int getIndex();

	void Out();

	void getSize();

	void deleteAll();

	void changeIndex();

	void isEmpty();

	void addList(List lst);
	
};


List::List() {
	head = nullptr;
}


void List::Out() {
	Node* curr = head;
	while (true) {
		if (curr->next == nullptr) {
			break;
		}
		curr = curr->next;
		
	}
;
}


void List::addFirst(int i) {
	int flag = 0;
	Node* curr = new Node(i,flag);
	curr->next = head;
	head = curr;

}


void List::addEnd() {
	int flag = 0;
	if (head == nullptr) {
		head = new Node(0,flag);
	}
	else {
		Node* curr = head;
		while (curr->next != nullptr) {
			curr = curr->next;
		}
		int a = curr->index;
		a++;
		curr->next = new Node(a,flag);
	}
}


void List::deleteEnd() {
	Node* curr = head;
	Node* end = curr;
	while (curr->next != nullptr) {
		end = curr;
		curr = curr->next;
	}
	end->next = nullptr;
	delete curr;
	curr = head;
	while (curr->next != nullptr) {
		curr->index--;
		curr = curr->next;
	}
	curr->index--;

}


void List::deleteFirst() {
	Node* curr = head;
	head=curr->next;
	delete curr;
	curr = head;

	while (curr->next != nullptr) {
		//curr->index--;
		curr = curr->next;
	}

}


void List::deleteIndex() {
	int indexDel;
	cout << "Enter Index to delete: ";
	cin >> indexDel;
	cout << endl;
	Node* curr = head;
	Node* prev = curr;

	while (curr->next!=nullptr) {
		if (curr->index == indexDel) {
			break;
		}
		prev = curr;
		curr = curr->next;
	}
	prev->next = curr->next;
	delete curr;

	curr = head;
	while (curr->next != nullptr) {
		curr->index--;
		curr = curr->next;
	}
	curr->index = 0;


}


int List::getIndex() {
	int indexGet;
	cout << "Enter Index to get: ";
	cin >> indexGet;
	cout << endl;
	Node* curr = head;

	while (curr->next != nullptr) {
		if (curr->index == indexGet) {
			cout << "Requested: " << curr->data << endl;
			return 0;
		}
		curr = curr->next;
	}
	if (curr->index == indexGet) {
		cout << "Requested: " << curr->data << endl;
	}
}


void List::getSize() {
	Node* curr = head;
	int size = 0;
	while (curr->next != nullptr) {
		size++;
		curr = curr->next;
	}
	size++;
	cout << "Size of list is: " << size << endl;
}


void List::deleteAll() {
	Node* curr = head;
	Node* tmp = curr;

	while (curr != nullptr)
	{
		curr = curr->next;
		delete tmp;
		tmp = curr;
	}
	head = nullptr;
}


void List::changeIndex(){

	Node* curr = head;
	int changeIndex = 0;
	int changeValue;

	cout << "Enter index to change: "; cin >> changeIndex; cout << endl;
	cout << "Enter value to change: "; cin >> changeValue; cout << endl;

	while (curr->next != nullptr) {
		if (curr->index == changeIndex) {
			curr->data = changeValue;
			break;
		}
		curr = curr->next;
	}
	if (curr->index == changeIndex) {
		curr->data = changeValue;
	}

}


void List::isEmpty() {
	if (head == nullptr) {
		cout << "List is empty" << endl;
	}
	else {
		cout << "List doesn't empty" << endl;
	}
}


void List::addList(List lst) {
	int flag = 1;
	Node* curr = head;
	Node* curr2 = lst.head;
	while (curr->next != nullptr) {
		curr = curr->next;
	}
	int a = curr->index;
	a++;
	curr->next = new Node(a,flag);
	curr->next = curr2;
}


int main() {
	List lst;
	List lst2;
	
	cout << "First List: " << endl;
	for (int i = 0; i < 10; i++) {
		lst.addFirst(i);
	}
	lst.Out();

	cout << "End was deleted" << endl;
	lst.deleteEnd();
	lst.Out();
	cout << endl;

	cout << "First was deleted" << endl;
	lst.deleteFirst();
	lst.Out();
	cout << endl;

	cout << "Index was deleted" << endl;
	lst.deleteIndex();
	lst.Out();
	cout << endl;

	cout << "Your Index" << endl;
	lst.getIndex();
	cout << endl;

	lst.getSize();
	cout << endl;

	cout << "Index was changed" << endl;
	lst.changeIndex();
	lst.Out();

	cout << endl << endl;
	cout << "Second List: " << endl;
	for (int i = 0; i < 10; i++) {
		lst2.addEnd();
	}

	lst.addList(lst2);
	cout << "New list was added" << endl;

	lst.Out();
	cout << endl;

	lst.deleteAll();
	lst.isEmpty();



	return 0;
}


