#include "LZ78.h"

string LZ78(string LZ78){
	string code;
	std::map<string, int> tabl;
	string tmp = "";
	string tmp2 = "";
	int index = 0;
	char symb;

	/*for (int i = 0; i < LZ78.length(); i++) {
		if (tmp.find(LZ78[i]) == tmp.npos) {
			tmp2 = LZ78[i];
			tmp += LZ78[i];
			tabl[tmp2] = index;
			index++;
		}
	}*/
	
	
	
	for (int i = 0; i < LZ78.length(); i++) {
		symb = LZ78[i];
		if (tabl.find(tmp+symb)!=tabl.end()) {
			tmp = tmp + symb;
		}
		else {
			code+=tabl[tmp];
			tabl[tmp + symb] = index;
			index++;
			tmp = symb;
		}
	}
	code+=tabl[tmp];
	/*for (int i = 0; i < LZ78.length(); i++) {
		if (i == LZ78.length() - 1) {
			tmp = LZ78[i];
			out << tabl[tmp];
			return;
		}
		tmp += LZ78[i];
		bool est = false;
		for (const auto elem : tabl) {
			if (elem.first == tmp) {
				est = true;
				break;
			}
		}
		if (est == true) { continue; }
		else {
			string tmp3 = "";
			for (int i = 0; i < tmp.length() - 1; i++) {
				tmp3 += tmp[i];
			}
			code = tabl[tmp3];
			out << code;
			tabl[tmp] = index;
			index++;
			tmp = LZ78[i];
		}
		
	}*/	
	cout << code;
	return code;
}
