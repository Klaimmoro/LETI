#include <iostream>
#include "binaryTree.h"
#include "fibHeap.h"
using namespace std;

int main() {
	fibHeap Fib{};
	double** MatrixG; int MatrixS = 5;
	MatrixG = new double* [MatrixS];
	for (int i = 0; i < MatrixS; i++) {
		MatrixG[i] = new double[MatrixS];
	}
	cout << "Enter matrix values: " << endl;
	for (int i = 0; i < MatrixS; i++) {
		for (int j = 0; j < MatrixS; j++) {
			cin >> MatrixG[i][j];
		}
	}

	Dijkstra(Fib,MatrixG);

	BinTree();
	

	
	return 0;
}