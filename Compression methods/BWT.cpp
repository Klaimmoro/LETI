#include "BWT.h"
//string BWT(const string& BWT){
//	const int size = BWT.length() - 1;
//	priority_queue<string,vector<string>> pq;
//	pq.push(BWT);
//
//	string tmp = BWT;
//	for (int i = 1; i <= size; i++) {
//		char tmpS = tmp.back();
//		tmp.pop_back();
//		tmp.insert(tmp.begin(),tmpS);
//		pq.push(tmp);
//	}
//	qsort(pq, pq.size(), size, PQsort);
//	while (pq.size() != 0) {
//		cout << pq.top() << endl;
//		pq.pop();
//	}
//
//	//string code2 = code;
//	//decode(code2,BWT);
//	string code;
//	return code;
//}
//
//void decode(string code, string Ishodniy){
//	string SortCode = BubbleSort(code);
//	const int size = SortCode.length();
//	string** Swap = new string * [size];
//
//	for (int i = 0; i< size; i++) {
//		Swap[i] = new string[size];
//		Swap[i][0] = SortCode[i];
//	}
//	
//	for (int j = 1; j < size; j++) {
//		for (int i = 0; i < size; i++) {
//			Swap[i]->insert(Swap[i]->begin(), code[i]);
//		}
//		SwapSort(Swap, size-1);
//	}
//	
//
//	for (int j = 0; j < size; j++) {
//		if (*Swap[j] == Ishodniy) {
//			cout << *Swap[j];
//			break;
//		}
//	}
//	
//
//}
//
//string BubbleSort(string Alphabet) {
//	char temp;
//	for (int i = 0; i < Alphabet.length(); i++) {
//		for (int j = 0; j < Alphabet.length() - i - 1; j++) {
//			if (Alphabet[j] > Alphabet[j + 1]) {
//				temp = Alphabet[j];
//				Alphabet[j] = Alphabet[j + 1];
//				Alphabet[j + 1] = temp;
//			}
//		}
//	}
//	return Alphabet;
//}
//
//void SwapSort(string** Swap,int size) {
//	for (int i = 0; i < size; i++) {
//		for (int i = 0; i < size; i++) {
//			for (int j = 0; j < size + 1; j++) {
//				if (Swap[i][j] > Swap[i + 1][j]) {
//					swap(Swap[i], Swap[i + 1]);
//					break;
//				}
//				if (Swap[i][j] == Swap[i + 1][j]) {
//					continue;
//				}
//				if (Swap[i][j] < Swap[i + 1][j]) {
//					break;
//				}
//			}
//		}
//	}
//	
//
//}


int cmpfunc(const void* x, const void* y)
{
    struct rotation* rx = (struct rotation*)x;
    struct rotation* ry = (struct rotation*)y;
    return strcmp(rx->suffix, ry->suffix);
}


int* computeSuffixArray(char* input_text, int len_text)
{

    struct rotation suff[5000]; // lenght of text

    char* tmp=input_text;
    for (int i = 0; i < len_text; i++) {
        suff[i].index = i;
        suff[i].suffix = (input_text+i);
       // cout << suff[i].index << ' ' << suff[i].suffix << endl;
    }


    qsort(suff, len_text, sizeof(struct rotation), cmpfunc);


    int* suffix_arr = (int*)malloc(len_text * sizeof(int));
    for (int i = 0; i < len_text; i++) {
        suffix_arr[i] = suff[i].index;
        //cout << suffix_arr[i] << ' ' << suff[i].suffix << endl;
    }

    return suffix_arr;
}


char* findLastChar(char* input_text, int* suffix_arr, int n)
{

    char* code = (char*)malloc(n * sizeof(char));
    int i;
    for (i = 0; i < n; i++) {
        int j = suffix_arr[i] - 1;
        if (j < 0)
            j = j + n;

        code[i] = input_text[j];
    }

    code[i] = '\0';
    return code;
}


char* BWT(char input_text[])
{
    
    int len_text = strlen(input_text);


    int* suffix_arr = computeSuffixArray(input_text, len_text);


    char* bwt_arr = findLastChar(input_text, suffix_arr, len_text);
    //cout << bwt_arr;
    return bwt_arr;
}