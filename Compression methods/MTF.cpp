#include "MTF.h"
//#include <typeinfo>
//string MTF(string MTF)
//{
//	string Alphabet="";
//	for (int i = 0; i < MTF.size(); i++) {
//		if (Alphabet.find(MTF[i])==Alphabet.npos) {
//			Alphabet += MTF[i];
//		}
//	}
//    Alphabet= bubbleSort(Alphabet);
//	string compMTF;
//	char tmp;
//	for (int i = 0; i < MTF.size(); i++) {
//		compMTF += to_string(Alphabet.find(MTF[i]));
//		tmp = MTF[i];
//		Alphabet.erase(Alphabet.find(MTF[i]),1);
//		Alphabet.insert(Alphabet.begin(), tmp);
//	}
//	//ofstream out("out.txt");
//	//out << compMTF;
//	return compMTF;
//}
//
//string bubbleSort(string Alphabet) {
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

string MTF(const string& input)
{
	string output;

	list<char> alphabet;
	for (int i = 0; i <= 255; i++)
		alphabet.push_back((char)i);

	for (char c : input)
	{
		auto c_it = find(alphabet.begin(), alphabet.end(), c);
		output += distance(alphabet.begin(), c_it);
		alphabet.erase(c_it);
		alphabet.insert(alphabet.begin(), c);
	}

	return output;
}


string DeMTF(const string& input)
{
	string output;

	deque<char> alphabet;
	for (int i = 0; i <= 255; i++)
		alphabet.push_back((char)i);

	for (unsigned char n : input)
	{
		char temp_c = alphabet[n];
		output += temp_c;
		alphabet.erase(alphabet.begin() + n);
		alphabet.insert(alphabet.begin(), temp_c);
	}
	return output;
}

