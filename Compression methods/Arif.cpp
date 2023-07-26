#include "Arif.h"

string frequency(string comp, std::map<char, double>& freq)
{
	int Alphabet = 0;
	for (auto& ch : comp) {
		if (Alphabet == 0) {
			freq[ch]++;
			Alphabet++;
		}
		else {
			if (freq[ch] > 0) {
				freq[ch]++;
			}
			else {
				freq[ch]++;
				Alphabet++;
			}
		}
	}
	
	std::map<char, double> probilityV = {};
	std::map<char, double> probilityN = {};
	double low = 0.0;
	char predCH = ' ';
	double high = 1.0;
	int i = 0;
	for (auto& ch : freq) {
		if (i == 0) {
			probilityV[ch.first] = ch.second / comp.length();
			probilityN[ch.first] = low;
			predCH = ch.first;
			i++;
		}
		else {
			probilityV[ch.first] = ch.second / comp.length()+probilityV[predCH];
			probilityN[ch.first] = probilityV[predCH];
			predCH = ch.first;
		}
	}

	string code = "";
	i = 0;
	predCH = ' ';
	for (auto& ch : comp) {
		double range = high - low;
		high = low + range * probilityV[ch];
		low = low + range * probilityN[ch];
		if (i == comp.length() - 1) {
			code = to_string(high);
		}
		i++;

	}
	return code;
}


string Arifm(string text){
	std::map<char, double> freq = {};
	string code = "";
	code=frequency(text, freq);
	return code;

}


