#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <stack>
#include <stdlib.h>
using namespace std;
using namespace sf;







class Node {
public:
	friend SFML_GRAPHICS_API CircleShape;
	friend SFML_GRAPHICS_API Vertex;

	int data;
	int height = 0;
	Node* nextr;
	Node* nextl;
	bool Visited;
	string An;
	CircleShape circle;

	int x;
	int y;

	Node(bool flag, double value, int x1, int y1, Node* r = nullptr, Node* l = nullptr);
};




class List {
public:
	Node* head = nullptr;

	void add(double value, RenderWindow& window, Text& txt);

	Node* GetHead();
};

void dijkstra(List s, double** Matrix,RenderWindow& window, Text& txt);


void BinTree();
