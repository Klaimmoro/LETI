#include <iostream>
#include <stack>
#include <iomanip>
#include <charconv>
using namespace std;

class TypeOf
{
public:
	char type;
	double value;

	TypeOf() {};
	~TypeOf() {};


};


bool isOperator(char x) {
	switch (x) {
	case '+':
	case '-':
	case '/':
	case '*':
	case '^':
	case '%':
		return true;
	}
	return false;
}


bool isOperand(char x)
{
	return (x >= 'a' && x <= 'z') ||
		(x >= 'A' && x <= 'Z');
}


string preToInf(string pre_exp) {
	stack<string> s;


	int length = pre_exp.size();


	for (int i = length - 1; i >= 0; i--) {


		if (isOperator(pre_exp[i])) {


			string op1 = s.top();   s.pop();
			string op2 = s.top();   s.pop();


			string temp = "(" + op1 + pre_exp[i] + op2 + ")";


			s.push(temp);
		}


		else {


			s.push(string(1, pre_exp[i]));
		}
	}
	return s.top();
}


string postToInf(string exp)
{
	stack<string> s;

	for (int i = 0; exp[i] != '\0'; i++)
	{

		if (isOperand(exp[i]))
		{
			string op(1, exp[i]);
			s.push(op);
		}


		else
		{
			string op1 = s.top();
			s.pop();
			string op2 = s.top();
			s.pop();
			s.push("(" + op2 + exp[i] +
				op1 + ")");
		}
	}


	return s.top();
}


int Priority(char Oper) {
	if (Oper == '+' or Oper == '-') {
		return 1;
	}
	if (Oper == '*' or Oper == '/') {
		return 2;
	}
	return 0;
}


bool Calc(stack <TypeOf> &Numbers, stack <TypeOf> &Operations,TypeOf& huy) {
	double A,B;
	double result;
	A = Numbers.top().value;
	Numbers.pop();
	switch (Operations.top().type)
	{
	case '+':
		B = Numbers.top().value;
		Numbers.pop();
		result = A + B;
		huy.type = '0';
		huy.value = result;
		//cout << "sum: "  << result << endl;
		Numbers.push(huy);
		Operations.pop();
		break;
	case '-':
		B = Numbers.top().value;
		Numbers.pop();
		result = B - A;
		huy.type = '0';
		huy.value = result;
		//cout << "minus: " << result << endl;

		Numbers.push(huy);
		Operations.pop();

		break;
	case '*':
		B = Numbers.top().value;
		Numbers.pop();
		result = A * B;
		huy.type = '0';
		huy.value = result;
		//cout << "ymnoj: " << result << endl;
		
		Numbers.push(huy);
		//cout << Numbers.top().value << endl;
		Operations.pop();

		break;
	case '/':
		B = Numbers.top().value;
		if (A == 0) { cerr << "ychi yroki debil"; return false; }
		Numbers.pop();
		result = B / A;
		huy.type = '0';
		huy.value = result;
		//cout << "del: " << result << endl;

		Numbers.push(huy);
		Operations.pop();

		break;
	default:
		return false;
		break;
	}
	return true;
}


int main() {
	stack <TypeOf> numbers;
	stack <TypeOf> operations;

	bool sign = 1;
	char ch;
	double value;
	string chh;
	cin >> chh;
	cout << postToInf(chh);
	TypeOf huy;
	/*if (chh[0] == '+' or chh[0] == '-' or chh[0] == '*' or chh[0] == '/') {
		chh=pretoinf(chh);
	}
	if (chh[chh.size()] == '+' or chh[chh.size()] == '-' or chh[chh.size()] == '*' or chh[chh.size()] == '/') {
		chh = posttoinf(chh);
	}*/
	

	for(int i=0;i<chh.size();i++) {
		ch = chh[i];
		//cout << ch << endl;

		if (ch == '\n') { break; }

		if(ch==' '){ continue; }

		if (ch >= '0' and ch <= '9' or (ch=='-' and sign==1)) {
			int j = i;
			string temp;
			while (j!=chh.size()) {
				if (chh[j] == '\n') { break; }
				if (chh[j] == '+') { break; }
				if (chh[j] == '-') { break; }
				if (chh[j] == ')' ) { break; }
				if (chh[j] == '(') { break; }

				if (chh[j] == '*') { break; }
				if (chh[j] == '/') { break; }

				temp += chh[j];
				j++;
			}
			if (j - i > 1) { i=j-1; }
			value = strtod(temp.c_str(),NULL);
			//cout << value << endl;
			huy.type = '0';
			huy.value = value;
			numbers.push(huy);
			sign = 0;
			continue;
		}

		if (ch == '+' or ch == '-' and sign==0 or ch == '*' or ch == '/') {

			if (operations.size() == 0) {
				huy.type = ch;
				huy.value = 0;
				operations.push(huy);
				
				continue;
			}

			if (operations.size() != 0 && Priority(ch) > Priority(operations.top().type)) {
				huy.type = ch;
				huy.value = 0;
				operations.push(huy);
				continue;
			}
			if (operations.size() != 0 && Priority(ch) <= Priority(operations.top().type)) {
				cout << numbers.top().value << endl;
				if (Calc(numbers, operations, huy) == false) {
					return 0;
				}
				i--;
				continue;
			}
		}

		if (ch == 40) {
			
			huy.type = ch;
			huy.value = 0;
			operations.push(huy);
			continue;
		}

		if (ch == 41) {
			
			while (operations.top().type != '(') {
				if (Calc(numbers, operations, huy) == false) {
					return 0;
				}
				
			}
			operations.pop();
		}

		else {
			cout << "incorrect cin" << endl;
			return 0;
		}
	}
	while (operations.size() != 0) {
		//cout << operations.top().type << endl;
		if (Calc(numbers, operations, huy) == false) {
			return 0;
		}

	}
	
	cout << "answer: " << numbers.top().value << endl;
	return 0;
}



