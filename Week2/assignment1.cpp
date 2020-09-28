#include<iostream>
#include<string>
#include<map>
#include<stack>
#include <stdio.h>  
#include <stdlib.h>
#include<list>


using namespace std;
stack<double> numbers;
stack<char> op;
map<const char, int> operatorMap;
map<const char, double> argumentMap;
list<char> list1;
int compareOP(char top, char test) {
	if (top == '(' && test == ')') {
		return 0;
	}
	else if (top == '(') {
		return -1;
	}
	else if (operatorMap[top] >= operatorMap[test]) {
		return 1;
	}
	else if (operatorMap[top] < operatorMap[test]) {
		return -1;
	}

	return 0;
}
int find_Ind(char ch){
	for (list<char>::iterator IsItr = list1.begin(); IsItr != list1.end();IsItr++)
	{
		if(*IsItr==ch){
			return 1;
		}
	}
	
	return -1;
}
double toLong(const char *str) {
	double  nValude = 0;
	sscanf(str, "%1f", &nValude);
	return nValude;


}
double calculate_operator(double num1, double num2, char ch1) {
	if (ch1 == '+') {
		return num1 + num2;
	}
	else if (ch1 == '-') {
		return num1 - num2;
	}
	else if (ch1 == '*') {
		return num1 * num2;
	}
	else if (ch1 == '/') {
		return num1 / num2;
	}
	return 0;
}
double calculate(string str) {
	operatorMap['-'] = 1;
	operatorMap['+'] = 1;
	operatorMap['*'] = 2;
	operatorMap['/'] = 2;
	operatorMap['('] = 3;
	operatorMap[')'] = 0;
	operatorMap['!'] = -1;
	str += '!';
	int n = 0;
	bool T = true;
	while (n < str.length()) {
		if (str.at(n) >= '0'&&str.at(n) <= '9') {
			string str0 = "";
			str0 += str.at(n);
			n++;
			while ((str.at(n) >= '0'&&str.at(n) << '9') || str.at(n) == '.') {
				str0 += str.at(n);
				n++;
			}
			const char* c_s = str0.c_str();
			numbers.push(atof(c_s));
			T = false;
		}
		else if('A'<=str.at(n)<='Z'||'a'<=str.at(n)<='z'){
			numbers.push(argumentMap[str.at(n)]);
		}else {
			if (op.empty()) {
				op.push(str.at(n));
				if (str.at(n) == '-'&&n == 0) {
					numbers.push(0);
				}
				n++;
				continue;
			}
			int testNum;
			testNum = compareOP(op.top(), str.at(n));
			if (testNum == -1) {
				op.push(str.at(n));
				if (str.at(n)=='-'&&T==true) {
					numbers.push(0);
				}
				T = true;
				n++;
				continue;
			}
			else if (testNum == 0) {
				op.pop();
				n++;
			}
			else if (testNum == 1) {
				double number1, number2, final_number;
				char operator_char;
				number1 = numbers.top();
				numbers.pop();
				number2 = numbers.top();
				numbers.pop();
				operator_char = op.top();
				op.pop();
				final_number = calculate_operator(number2, number1, operator_char);
				numbers.push(final_number);
				continue;
			}

		}

	}
	return numbers.top();
}
void contAwithN(string str0){
	char ch;
	double num;
	ch = str0.at(1);
	list1.push_back(ch);
	string str1 = "";
	for (int i = 3; i < str0.length(); i++)
	{
		str1 += str0.at(i);
	}
	const char* c_str1 = str1.c_str();
	num =atof(c_str1);
	argumentMap[ch] = num;
}
int testString(string str){
	if(str.at(0)=='@'){
		if('A'<=str.at(1)<='Z'||'a'<=str.at(1)<='z'){
			if(str.at(2)=='='){
				for (int i = 3; i < str.length();i++){
					if(str.at(i) >= '0'&&str.at(i) <= '9'||str.at(i)=='.'){
						continue;
					}else{
						cout << "The number you typed is in the wrong format" << endl;
						return -1;
					}
				}
				return 1;
			}else{
				cout << "The equal sign is not in the right place" << endl;
				return -1;
			}
		}else{
			cout << "Unknown format error (a<=x<=z||A<=x<=Z)" << endl;
			return -1;
		}
	}
	int count = 0;
	for (int i = 0; i < str.length();i++){
		if(str.at(i) >= '0'&&str.at(i) << '9'||str.at(i) == '.'){
				continue;
		}else if(str.at(i)=='+'||str.at(i)=='-'||str.at(i)=='*'||str.at(i)=='/'){
			if(str.at(i)=='+'||str.at(i)=='-'||str.at(i)=='*'||str.at(i)=='/'){
				cout << "Your expression is wrong" << endl;
				return -1;
			}else{
				continue;
			}
		}else if(str.at(i)=='('){
			count++;
		}else if(str.at(i)==')'){
			count--;
			if(count<0){
				cout << "Your expression is wrong" << endl;
				return -1;
			}
		}else if('A'<=str.at(1)<='Z'||'a'<=str.at(1)<='z'){
			if(find_Ind(str.at(i))==-1){
				cout << str.at(i) << " is not defined" << endl;
				return -1;
			}
		}
	}
		return 0;
}
int main() {
	bool T = true;
	while(T){
		string str;
		cout << "Please input your Operational expression:";
		cin >> str;
		int testNum = testString(str);
		if(testNum==1){
			contAwithN(str);
		}else if(testNum==0){
			cout << calculate(str) << endl;
		}else if(str.at(0)=='#'){
			T = false;
		}
		
	}
}