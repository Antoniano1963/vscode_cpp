#include<iostream>
#include<string>
#include<map>
#include<stack>
#include <stdio.h>  
#include <stdlib.h>
#include<list>
#include<math.h>
#include <string.h>
#include "big_operation.h"


using namespace std;
stack<big> numbers;
stack<char> op;
map<const char, int> operatorMap;
map<const char, double> argumentMap;
list<char> list1;
double cal_Func(string str, double numbers);
int find_Ind(char ch);
double testFuncString2(string str);
bool test_stringnum(string str);
double testFuncString2(string str) {
	string funcString = "";//函数字符串
	string strNumber = "";//数字字符串
	bool T = true;
	bool K = false;
	bool J = true;
	double number;
	for (int i = 0; i < str.length(); i++) {
		if (str.at(i) == '(') {
			T = false;
			K = true;
			continue;
		}
		if (str.at(i) == ')') {
			break;
		}
		if (T) {
			funcString += str.at(i);//记录函数部分的字符串
		}
		if (K) {//记录括号后面的数字部分
			if ((65 <= str.at(i) && str.at(i) <= 90) || (97 <= str.at(i) && str.at(i) <= 122)) {//是未知数，那就从map中获取
				J = false;
				if (find_Ind(str.at(i)) == -1) {//如果没有记录，那么这个字符就是没有定义的
					return -1;
				}
				number = argumentMap[str.at(i)];
				K = false;
				break;
			}
			else {
				strNumber += str.at(i);//用字符串拼接来搞
			}
		}

	}
	if (J) {
		if (test_stringnum(strNumber)) {
			return -1;
		}
	}
	const char* cns_stringNum = strNumber.c_str();
	if (J) {
		number = atof(cns_stringNum);//如果不是未知数，那就进行数字转化
	}
	if (cal_Func(funcString, number) == -1) {
		return -1;
	}
	return cal_Func(funcString, number);
}
double cal_Func(string str, double numbers) {//进行函数调用的函数，如果正确调用返回数值，错误调用返回-1
	const char* newc_str = str.c_str();
	if (str.compare("sqrt") == 0) {
		return sqrt(numbers);
	}
	if (str.compare("cbrt") == 0) {
		return cbrt(numbers);
	}
	if (str.compare("ceil") == 0) {
		return ceil(numbers);
	}
	if (str.compare("floor") == 0) {
		return floor(numbers);
	}
	if (str.compare("abs") == 0) {
		return abs(numbers);
	}
	if (str.compare("cos") == 0) {
		return cos(numbers);
	}
	if (str.compare("sin") == 0) {
		return sin(numbers);
	}
	if (str.compare("tan") == 0) {
		return tan(numbers);
	}
	if (str.compare("exp") == 0) {
		return exp(numbers);
	}
	if (str.compare("log10") == 0) {
		return log10(numbers);
	}
	if (str.compare("log2") == 0) {
		return log2(numbers);
	}
	if (str.compare("log") == 0) {
		return log(numbers);
	}
	return -1;

}
int compareOP(char top, char test) {//比较运算符的优先级，来实现表达式运算
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
int find_Ind(char ch) {//看看未知变量是不是已经预先定义了，如果没有定义返回-1
	for (list<char>::iterator IsItr = list1.begin(); IsItr != list1.end(); IsItr++)
	{
		if (*IsItr == ch) {
			return 1;
		}
	}

	return -1;
}
big calculate_operator(big &num1, big &num2, char ch1) {//这个是传入数字来进行计算
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
	else if (ch1 == '%') {
		return num1 % num2;
	}
	return big();
}
big calculate(string str) {
	operatorMap['-'] = 1;
	operatorMap['+'] = 1;
	operatorMap['*'] = 2;
	operatorMap['/'] = 2;
	operatorMap['%'] = 2;
	operatorMap['('] = 3;
	operatorMap[')'] = 0;
	operatorMap['!'] = -1;
	str += '!';
	int n = 0;
	bool T = true;
	while (n < str.length()) {
		if (str.at(n) >= '0'&&str.at(n) <= '9') {//处理数字，用atof把字符转化成数字
			string str0 = "";
			str0 += str.at(n);
			n++;
			while ((str.at(n) >= '0'&&str.at(n) << '9') || str.at(n) == '.') {
				str0 += str.at(n);
				n++;
			}
			//const char* c_s = str0.c_str();
			numbers.push(big(str0));
			T = false;
		}
		else if ((65 <= str.at(n) && str.at(n) <= 90) || (97 <= str.at(n) && str.at(n) <= 122)) {//用来读入未知数的语句
			n++;
			string str0 = to_string(argumentMap[str.at(n - 1)]);
			numbers.push(big(str0));
			T = false;
			continue;
		}
		else if (str.at(n) == '&') {//处理函数
			string str0 = "";
			n++;
			while (str.at(n) != '&') {
				str0 += str.at(n);
				n++;
			}
			string str1 = to_string(testFuncString2(str0));
			numbers.push(big(str1));
			n++;
		}
		else {//进行运算符的处理
			if (op.empty()) {
				op.push(str.at(n));
				if (str.at(n) == '-'&&n == 0) {
					numbers.push(big());
				}
				n++;
				continue;
			}
			int testNum;
			testNum = compareOP(op.top(), str.at(n));
			if (testNum == -1) {
				op.push(str.at(n));
				if (str.at(n) == '-'&&T == true) {
					numbers.push(big());
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
				big number1, number2, final_number;
				char operator_char;
				number1 = numbers.top();
				numbers.pop();
				number2 = numbers.top();
				numbers.pop();
				operator_char = op.top();
				op.pop();
				if (number1 == big() && operator_char == '/') {
					cout << "The divisor should not be 0, It's going to print minus 1" << endl;
					string str0 = "-1";
					return big(str0);
				}
				final_number = calculate_operator(number2, number1, operator_char);
				numbers.push(final_number);
				continue;
			}

		}

	}
	big result = numbers.top();
	while (!numbers.empty())
	{
		numbers.pop();
	}
	while (!op.empty())
	{
		op.pop();
	}
	return result;;
}
void contAwithN(string str0) {//读入字符串，然后将字符串标记到列表里，然后把未知数和数字绑定起来
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
	num = atof(c_str1);
	argumentMap[ch] = num;
}
int testString(string str) {//检查字符串的函数，可以适当的进行提醒
	if (str.at(0) == '@') {//检查赋值语句是否正确
		if (str.length() < 4) {
			cout << "The length of definition is not right" << endl;
			return -1;

		}
		else {
			if ((65 <= str.at(1) && str.at(1) <= 90) || (97 <= str.at(1) && str.at(1) <= 122)) {
				if (str.at(2) == '=') {
					string str0 = "";
					for (int i = 3; i < str.length(); i++) {
						if (str.at(i) >= '0'&&str.at(i) <= '9' || str.at(i) == '.') {
							str0 += str.at(i);
							continue;
						}
						else {//检查是不是有非法字符
							cout << "The number you typed is in the wrong format" << endl;
							return -1;
						}
					}
					if (test_stringnum(str0)) {
						cout << "We don't have the right number of decimal points" << endl;
						return -1;
					}
					return 1;
				}
				else {
					cout << "The equal sign is not in the right place" << endl;
					return -1;
				}
			}
			else {
				cout << "Unknown format error (a<=x<=z||A<=x<=Z)" << endl;
				return -1;
			}
		}
	}
	int count = 0;
	int count1 = 0;
	for (int i = 0; i < str.length(); i++) {//检查函数标识符数量是否正确
		if (str.at(i) == '&') {
			count1++;
		}
	}
	for (int i = 0; i < str.length(); i++) {
		if (str.at(i) == '(') {
			count++;
		}
		if (str.at(i) == ')') {
			count--;
		}
	}
	if (count != 0) {
		cout << "Incorrect number of parentheses" << endl;
		return -1;
	}
	if ((count1 % 2) != 0)
	{
		cout << "Your func expression is wrong " << endl;
		return -1;
	}

	for (int i = 0; i < str.length(); i++)
	{
		if ((str.at(i) >= '0' && str.at(i) <= '9') || str.at(i) == '.')
		{
			string str0 = to_string(str.at(i));
			i++;
			while ((i < str.length()) && (str.at(i) >= '0'&&str.at(i) <= '9' || str.at(i) == '.')) {
				str0 += str.at(i);
				i++;
			}
			i--;
			if (test_stringnum(str0)) {
				cout << "The number you typed is in the wrong format" << endl;
				return -1;
			}
			continue;
		}
		else if (str.at(i) == '+' || str.at(i) == '-' || str.at(i) == '*' || str.at(i) == '/'||str.at(i)=='%')
		{
			if (str.at(i + 1) == '+' || str.at(i + 1) == '-' || str.at(i + 1) == '*' || str.at(i + 1) == '/'||str.at(i+1)=='%')
			{
				cout << "Your expression is wrong" << endl;
				return -1;
			}
			else
			{
				continue;
			}
		}
		else if (str.at(i) == '(')
		{
			continue;
		}
		else if (str.at(i) == ')')
		{
			continue;
		}
		else if (str.at(i) == '&')//避免检测&函数表达式中的非法字符&这个留到运算的时候再进行检查
		{
			string str0 = "";
			i++;
			while (str.at(i) != '&') {
				str0 += str.at(i);
				i++;
			}
			if (testFuncString2(str0) == -1) {//将字符串输入 尝试能不能调取
				cout << "Your function experission is wrong" << endl;
				return -1;
			}
		}
		else if ((65 <= str.at(i) && str.at(i) <= 90) || (97 <= str.at(i) && str.at(i) <= 122))//检查未知数是否定义
		{
			if (find_Ind(str.at(i)) == -1)
			{
				cout << str.at(i) << " is not defined" << endl;
				return -1;
			}
		}
		else//其他的符号都是非法输入
		{
			cout << "Your argument is wrong" << endl;
			return -1;
		}
	}
	return 0;
}
bool test_stringnum(string str) {
	int count = 0;
	for (int i = 0; i < str.length() - 1; i++) {
		if (str.at(i) == '.') {
			count++;
		}
	}
	if (count > 1) {
		return true;
	}
	return false;
}
int main() {
	bool T = true;
	while (T) {
		string str;
		cout << "Please input your Operational expression:";
		cin >> str;
		if (str.at(0) == '#') {
			T = false;
			continue;
		}
		int testNum = testString(str);
		if (testNum == 1) {
			contAwithN(str);
		}
		else if (testNum == 0) {
			big result = calculate(str);

			cout << result.print() << endl;
		}

	}
}
