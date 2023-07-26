#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <queue>
#include <stack>
#include <iomanip>
#include <stdlib.h>
using namespace std;
using namespace sf;

struct AVLnode
{
	friend SFML_GRAPHICS_API CircleShape;
	friend SFML_GRAPHICS_API Vertex;
	int data;
	int height;
	AVLnode* left;
	bool Visited;
	AVLnode* right;
	CircleShape circle;

	int x=1900/2;
	int y=1;

	AVLnode(int k);
};


int height(AVLnode* p);


int bfactor(AVLnode* p);


void fixheight(AVLnode* p);


AVLnode* rotateright(AVLnode* p);


AVLnode* rotateleft(AVLnode* q);


AVLnode* balance(AVLnode* p);


AVLnode* insert(AVLnode* p, int k);


void BFS(AVLnode* head,RenderWindow& window, Text& txt);


void AVLtree();
