#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <stack>
#include <stdlib.h>
#include <time.h>
using namespace std;
using namespace sf;
//#include <iostream>
//#include <sfml/graphics.hpp>
//#include <queue>
//#include <stack>
//#include <stdlib.h>
//using namespace std;
//using namespace sf;
//
//
//
//
//
//
//
//class RDnode {
//public:
//	friend SFML_GRAPHICS_API CircleShape;
//	friend SFML_GRAPHICS_API Vertex;
//
//	int data;
//	RDnode* nextr;
//	RDnode* parent;
//	RDnode* nextl;
//	bool visited;
//	string color;
//	string an;
//	CircleShape circle;
//
//	int x;
//	int y;
//
//	RDnode(bool flag, double value, int x1, int y1,string color,RDnode* parent, RDnode* r = nullptr, RDnode* l = nullptr);
//};
//
//
//
//
//class list {
//public:
//	RDnode* head = nullptr;
//
//	void add(double value, RenderWindow& window, Text& txt);
//
//	void addbalance(RDnode* Insert, RenderWindow& window, Text& txt);
//
//	void leftrotate(RDnode* Insert);
//
//	void rightrotate(RDnode* Insert);
//
//	void bfs(RDnode* head, RenderWindow& window, Text& txt);
//
//};
//
//
//void rdtree();


struct node {
    friend SFML_GRAPHICS_API CircleShape;
    friend SFML_GRAPHICS_API Vertex;
    int data{};
    node* left = nullptr;
    node* right = nullptr;
    node* parent = nullptr;
    string color;
    int x = 1900 / 2;
    int y = 1;
    CircleShape circle;

};

class RDtree {

    node* head;

public:
    RDtree();

    node* GetHead();

    void InsertNode(int stuff);

    void BalanceNode(node* z);

    void LeftRotate(node* x);

    void RightRotate(node* x);

    void bfs(node* head, RenderWindow& window, Text& txt);


};

int RDTree();