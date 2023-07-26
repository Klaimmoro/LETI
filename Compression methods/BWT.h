#pragma once
#include <iostream>
using namespace std;

//struct PQsort
//{
//	bool operator()(string* l, string* r)
//	{
//		return l > r;
//	}
//};
//
//string BWT(const string& BWT);
//
//void decode(string code,string Ishodniy);
//
//string BubbleSort(string Alphabet);
//
//void SwapSort(string** Swap,int size);

struct rotation {
    int index;
    char* suffix;
};

int cmpfunc(const void* x, const void* y);

int* computeSuffixArray(char* input_text, int len_text);

char* findLastChar(char* input_text, int* suffix_arr, int n);

char* BWT(char input_text[]);