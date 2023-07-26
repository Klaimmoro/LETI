#include "Xaffman.h"
//
//
//Node::Node(char symb, int value, Node* r, Node* l)
//{
//	this->nextr = r;
//	this->nextl = l;
//	this->freq = value;
//	this->symb = symb;
//}
//
//void Frequency(string comp, std::map<char, int>& freq)
//{
//	for (char ch: comp) {
//		freq[ch]++;
//	}
//	
//}
//
//void enCode(Node* code, string str, std::map<char, string>& codes) {
//	
//	if (code == nullptr) { return; }
//
//
//	if (!code->nextl and !code->nextr) {
//		codes[code->symb] = str;
//	}
//	enCode(code->nextl, str + "0",codes);
//	enCode(code->nextr, str + "1",codes);
//
//}
//
//void outHaf(std::map<char, string>& codes, string Haff) {
//
//	ofstream out("out.bin",ios_base::binary );
//	cout << "Compressed string by Haffman: ";
//	for (const auto& elem : Haff) {
//		unsigned char x = 0;
//		for (int i = 0; i < codes[elem].length(); i++) {
//			if (codes[elem][i] == '1') {
//				x |= (1 << i);
//			}
//			else {
//				x &= ~(1 << i);
//			}
//		}
//		out << x;
//	}
//	//cout << endl; cout << endl;
//}
//
//Node* BinTree(std::map<char, int>& freq)
//{
//	List lst;
//	priority_queue<Node*, vector<Node*>,ssort> pq;
//	for (const auto& elem : freq) {
//		Node* curr = new Node(elem.first, elem.second, nullptr, nullptr);
//		pq.push(curr);
//	}
//
//	while (pq.size() != 1) {
//		Node* left = pq.top(); pq.pop();
//		Node* right = pq.top(); pq.pop();
//
//		int sumFreq = left->freq + right->freq;
//		Node* newN = new Node('H', sumFreq, right, left);
//		pq.push(newN);
//	}
//	Node* head = pq.top();
//	return head;
//}
//
//void Haffman(string cm)
//{
//	string HaffMan;
//	Node* haffTree;
//	std::map<char, int> freq = {};
//	HaffMan = cm;
//	
//	Frequency(HaffMan, freq);
//
//	haffTree=BinTree(freq);
//	
//	string cod = "";
//	std::map<char, string> codes = {};
//	enCode(haffTree,cod,codes);
//	
//	outHaf(codes, HaffMan);
//	
//}
//
//

#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;


Node* getNode(char ch, int freq, Node* left, Node* right)
{
	Node* node = new Node();

	node->ch = ch;
	node->freq = freq;
	node->left = left;
	node->right = right;

	return node;
}


void encode(Node* root, string str,unordered_map<char, string>& huffmanCode)
{
	if (root == nullptr)
		return;

	// found a leaf node
	if (!root->left && !root->right) {
		huffmanCode[root->ch] = str;
	}

	encode(root->left, str + "0", huffmanCode);
	encode(root->right, str + "1", huffmanCode);
}

void decode(Node* root, int& index, string str)
{
	if (root == nullptr) {
		return;
	}

	
	if (!root->left && !root->right)
	{
		//cout << root->ch;
		return;
	}

	index++;

	if (str[index] == '0')
		decode(root->left, index, str);
	else
		decode(root->right, index, str);
}

string HaffMan(string text)
{
	
	unordered_map<char, int> freq;
	for (char ch : text) {
		freq[ch]++;
	}


	priority_queue<Node*, vector<Node*>, comp> pq;


	for (auto pair : freq) {
		pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
	}

	
	while (pq.size() != 1)
	{
		
		Node* left = pq.top(); pq.pop();
		Node* right = pq.top();	pq.pop();

		
		int sum = left->freq + right->freq;
		pq.push(getNode('\0', sum, left, right));
	}

	
	Node* root = pq.top();

	
	unordered_map<char, string> huffmanCode;
	encode(root, "", huffmanCode);

	string code = "";
	for (char ch : text) {
		code += huffmanCode[ch];
	}

	/*int index = -1;
	cout << "\nDecoded string is: \n";
	while (index < (int)code.size() - 2) {
		decode(root, index, code);
	}*/

	return code;
}

