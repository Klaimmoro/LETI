#pragma once
#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

//class Node {
//public:
//
//	int freq;
//	char symb;
//	Node* nextr;
//	Node* nextl;
//
//	Node(char symb,int value,Node* r, Node* l);
//
//
//
//
//};
//
//
//class ssort {
//public:
//	bool operator()(Node* l, Node* r) {
//		return l->freq > r->freq;
//	}
//};
//
//
//class List {
//public:
//	Node* head = nullptr;
//
//};
//
//void outHaf(std::map<char, string>& codes, string Haff);
//
//void Frequency(string comp, std::map<char, int>& freq);
//
//void enCode(Node* code,string str, std::map<char, string>& codes);
//
//Node* BinTree(std::map<char, int>&);
//
//
//void Haffman(string cm);

struct Node
{
	char ch;
	int freq;
	Node* left, * right;
};

struct comp
{
	bool operator()(Node* l, Node* r)
	{

		return l->freq > r->freq;
	}
};

void encode(Node* root, string str, unordered_map<char, string>& huffmanCode);

void decode(Node* root, int& index, string str);

string HaffMan(string text);

Node* getNode(char ch, int freq, Node* left, Node* right);