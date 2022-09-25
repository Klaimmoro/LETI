#include <iostream>
#include <string>
#include <tgmath.h>
#include <cstdlib>
#include <cmath>
#include <algorithm>
using namespace std;



int typeShift() {

	int valueShift;
	cout << "1 - short type" << endl;
	cout << "2 - double type" << endl;
	cout << "3 - exit" << endl;
	cout << "Enter: ";
	while (!(cin >> valueShift))
	{
		cin.clear();
		cout << "Invalid value" << endl;
		cout << "Enter: ";
		char c;
		cin >> c;
	}
	return valueShift;
}


string convers(int value,string valuebin) {

	while (value != 0) {
		valuebin += to_string(value%2);
		value /= 2;
	}
	return valuebin;
}


int returnNumber(string valuebin) {
	int digit = valuebin.length()-1;
	int value = 0;

	for (int i = 0; i < valuebin.length(); i++) {
		if (valuebin[i] == '1') {
			value += pow(2, digit);
		}
		digit--;
	}
	return value;
}


string reverseBytes(string valuebin) {

	for (int i = 0; i < valuebin.length(); i++) {
		if (valuebin[i] == '0') { valuebin[i] = '1'; continue; }
		if (valuebin[i] == '1') { valuebin[i] = '0'; continue; }
	}

	return valuebin;
}


string addBytes(string valuebin) {
	int bytesCount = 0;
	if (valuebin.length() < 8) { bytesCount = 8; }
	else if ( 8 < valuebin.length() < 16 ) { bytesCount = 16; }
	else if (16 < valuebin.length() < 32) { bytesCount = 32; }
	else if (32 < valuebin.length() < 64) { bytesCount = 64; }
	for(int i=valuebin.length(); i<bytesCount; i++) {
		valuebin.insert(0, "0");
	}

	return valuebin;

}


int shortShift() {
	Begin:
	double value = 0;
	string valuebin = {};
	cout << "Please, enter the short value:";
	while (!(cin >> value))
	{
		cin.clear();
		cout << "Invalid value" << endl;
		cout << "Enter: ";
		char c;
		cin >> c;
	}
	if (-32768 < value and value < 32767) {
		if (value > 0) {

			valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());

			valuebin = addBytes(valuebin);

			cout << "The result: " << valuebin << endl;

			return value;

		}

		else {

			value = abs(value);

			valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());

			valuebin = addBytes(valuebin);

			valuebin = reverseBytes(valuebin);

			value = returnNumber(valuebin) + 1;

			valuebin = ""; valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());

			cout << "The result: " << valuebin << endl;

			return value;


		}
	}

	else { cout << "You have gone beyond short" << endl; goto Begin; }

}


double doubleShift() {
	double value = 0;
	string valuebinint = {};
	string valuebinfract = {};

	cout << "Please, enter the double value:"; cout << endl;
	while (!(cin >> value))
	{
		cin.clear();
		cout << "Invalid value" << endl;
		cout << "Enter: ";
		char c;
		cin >> c;
	}
	if ( -1.7e-308 < value and value < 1.7e308) {
		double intPart = int(value);
		double fractPart = abs(value - int(value));

		/*Integer Part*/
		if (intPart > 0) {

			valuebinint = convers(intPart, valuebinint);

			std::reverse(valuebinint.begin(), valuebinint.end());

			valuebinint = addBytes(valuebinint);


		}

		else {

			intPart = abs(intPart);

			valuebinint = convers(intPart, valuebinint);

			reverse(valuebinint.begin(), valuebinint.end());

			valuebinint = addBytes(valuebinint);

			valuebinint = reverseBytes(valuebinint);

			intPart = returnNumber(valuebinint) + 1;

			valuebinint = ""; valuebinint = convers(intPart, valuebinint);

			reverse(valuebinint.begin(), valuebinint.end());


		}

		/*            */


		/*Fractional Part*/
		for (int i = 0; i < 20; i++) {
			fractPart *= 2;
			valuebinfract += to_string(int(fractPart));
			fractPart = fractPart - int(fractPart);
		}

		/*               */

		cout << "The result: " << valuebinint + '.' + valuebinfract << endl;
		return value;
	}
	return 0;
}


void bitShift(int value) {
	int side;
	string valuebin;
	cout << "In what side you want to shift?" << endl;
	cout << "1 - left" << endl;
	cout << "2 - right" << endl;
	BeginShift:
	cout << "Enter: ";cout << endl;
	while (!(cin >> side))
	{
		cin.clear();
		cout << "Invalid value" << endl;
		cout << "Enter: ";
		char c;
		cin >> c;
	}
	
	

	if (side == 2) {
		cout << "How many bits would you like to shift?" << endl;
		int count = 0;
		cout << "Enter: "; cout << endl;
		while (!(cin >> count))
		{
			cin.clear();
			cout << "Invalid value" << endl;
			cout << "Enter: ";
			char c;
			cin >> c;
		}
		value /= pow(2, count);
		if (value > 0) {

			valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());
			valuebin = addBytes(valuebin);

			cout << "The result: " << valuebin << endl;


		}

		else {

			value = abs(value);

			valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());


			valuebin = reverseBytes(valuebin);

			value = returnNumber(valuebin) + 1;

			valuebin = ""; valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());

			cout << "The result: " << valuebin << endl;


		}

	}

	if (side == 1) {
		cout << "How many bits would you like to shift?" << endl;
		int count = 0;
		cout << "Enter: "; cout << endl;
		while (!(cin >> count))
		{
			cin.clear();
			cout << "Invalid value" << endl;
			cout << "Enter: ";
			char c;
			cin >> c;
		}
		value *= pow(2, count);


		if (value > 0) {

			valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());
			valuebin = addBytes(valuebin);

			cout << "The result: " << valuebin << endl;


		}

		else {

			value = abs(value);

			valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());


			valuebin = reverseBytes(valuebin);

			value = returnNumber(valuebin) + 1;

			valuebin = ""; valuebin = convers(value, valuebin);

			std::reverse(valuebin.begin(), valuebin.end());

			cout << "The result: " << valuebin << endl;


		}

	}

	if(side!=2 and side!=1) {
		cout << "Invalid value" << endl;
		goto BeginShift;
	}
}


void doubShift(double value) {

	string valuebinint = {};
	string valuebinfract = {};
	BeginShift:
	cout << "In what side you want to shift?" << endl;
	cout << "1 - left" << endl;
	cout << "2 - right" << endl;
	int side;
	string valuebin;
	cout << "Enter: ";cout << endl;
	while (!(cin >> side))
	{
		cin.clear();
		cout << "Invalid value" << endl;
		cout << "Enter: ";
		char c;
		cin >> c;
	}


	if (side == 2) {
		cout << "How many bits would you like to shift?" << endl;
		int count = 0;
		cout << "Enter: "; cout << endl;
		while (!(cin >> count))
		{
			cin.clear();
			cout << "Invalid value" << endl;
			cout << "Enter: ";
			char c;
			cin >> c;
		}
		value /= pow(2, count);

		double intPart = int(value);
		double fractPart = abs(value - int(value));

		/*Integer Part*/
		if (intPart > 0) {

			valuebinint = convers(intPart, valuebinint);

			std::reverse(valuebinint.begin(), valuebinint.end());

			valuebinint = addBytes(valuebinint);

		}

		else {

			intPart = abs(intPart);

			valuebinint = convers(intPart, valuebinint);

			std::reverse(valuebinint.begin(), valuebinint.end());
			

			valuebinint = reverseBytes(valuebinint);

			intPart = returnNumber(valuebinint) + 1;

			valuebinint = ""; valuebinint = convers(intPart, valuebinint);

			std::reverse(valuebinint.begin(), valuebinint.end());


		}

		/*            */


		/*Fractional Part*/
		for (int i = 0; i < 20; i++) {
			fractPart *= 2;
			valuebinfract += to_string(int(fractPart));
			fractPart = fractPart - int(fractPart);
		}

		/*               */

		cout << "The result: " << valuebinint + '.' + valuebinfract << endl;

	}

	if (side == 1) {
		cout << "How many bits would you like to shift?" << endl;
		int count = 0;
		cout << "Enter: "; cout << endl;
		while (!(cin >> count))
		{
			cin.clear();
			cout << "Invalid value" << endl;
			cout << "Enter: ";
			char c;
			cin >> c;
		}
		value *= pow(2, count);

		double intPart = int(value);
		double fractPart = abs(value - int(value));

		/*Integer Part*/
		if (intPart > 0) {

			valuebinint = convers(intPart, valuebinint);

			std::reverse(valuebinint.begin(), valuebinint.end());

			valuebinint = addBytes(valuebinint);


		}

		else {

			intPart = abs(intPart);

			valuebinint = convers(intPart, valuebinint);

			std::reverse(valuebinint.begin(), valuebinint.end());

			valuebinint = reverseBytes(valuebinint);

			intPart = returnNumber(valuebinint) + 1;

			valuebinint = ""; valuebinint = convers(intPart, valuebinint);

			std::reverse(valuebinint.begin(), valuebinint.end());
			valuebinint = addBytes(valuebinint);



		}

		/*            */


		/*Fractional Part*/
		for (int i = 0; i < 20; i++) {
			fractPart *= 2;
			valuebinfract += to_string(int(fractPart));
			fractPart = fractPart - int(fractPart);
		}

		/*               */

		cout << "The result: " << valuebinint + '.' + valuebinfract << endl;
		

	}

	if(side!=1 and side!=2) {
		cout << "Invalid value" << endl;
		goto BeginShift;
	}

}


int main() {

	cout << "Welcome to the binary calculator of double and short data types! " << endl;;
	cout << "What king of type you want to conver?" << endl;
	
Begin:

	int valueShift;
	valueShift = typeShift();
	double value = 0;
	int shiftIt = 0;

	
	if (valueShift == 1) {
		value = shortShift();
		BeginShift:
		cout << "Would you like to shift it?" << endl;
		cout << "1 - Yes" << endl << "2 - No" << endl;

		cout << "Enter: "; cout << endl;
		while (!(cin >> shiftIt))
		{
			cin.clear();
			cout << "Invalid value" << endl;
			cout << "Enter: ";
			char c;
			cin >> c;
		}

		if (shiftIt == 1) {
			bitShift(value);
		}
		if (shiftIt == 2) {

			goto Begin;
		}

		if (shiftIt != 1 and shiftIt != 2) { goto BeginShift; }
	}

	else if (valueShift == 2) {

		value = doubleShift();
		BeginShiftD:
		cout << "Would you like to shift it?" << endl;
		cout << "1 - Yes" << endl << "2 - No" << endl;

		cout << "Enter: "; cout << endl;
		while (!(cin >> shiftIt))
		{
			cin.clear();
			cout << "Invalid value" << endl;
			cout << "Enter: ";
			char c;
			cin >> c;
		}

		if (shiftIt == 1) {
			doubShift(value);
		}
		if (shiftIt == 2) {
			goto Begin;
		}
		if (shiftIt != 1 and shiftIt != 2) { goto BeginShiftD; }
	}

	else if (valueShift == 3) {
		return 0;
	}

	else if (valueShift != 1 or valueShift != 2 or valueShift != 3) {
		cout << "Invalid value" << endl;
		goto Begin;
	}
	goto Begin;

	

	return 0;

}