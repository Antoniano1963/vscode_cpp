#include<iostream>
#include<string>
#include<ctime>
#include<algorithm>
#include<thread>
#include<numeric>
#include<vector>
#include<functional>
#include "big_operation1.1.h"
#include<cmath>
#include<cblas.h>
using namespace std;
bool testNum(string str);
long testFunc(string str);
void creatVector(string str, float *vector);
double vector_DOT(long num, float *vector1, float *vector2);
double vector_DOT1(long num, float *vector1, float *vector2);
void vector_DOT2(long begin, long end, float *vector1, float *vector2, double &result);
big vector_DOT_BIG(long num, float *vector1, float *vector2);
void vector_DOT1_BIG(long begin, long end, float *vector1, float *vector2, big &res);
void vector_DOT2_BIG(long begin, long end, float *vector1, float *vector2, big &res);
int main() {
	bool T = true;
	while (T) {
		cout << "Enter your tpye number(0 means you input two vectors and we give you the result, 1 means system creat two vectors which has 10m elements randomly and give you the answer and the cost time of calculate)" << endl;
		string str0;
		cin >> str0;
		if (str0.length() != 1) {
			cout << "you enter a wrong number" << endl;
		}
		else {
			if (str0.at(0) == '0') {
				cout << "Enter the first vector in [num1,num2,...] format" << endl;
				string str1;
				cin >> str1;
				cout << "Enter the second vector in [num1,num2,...] format" << endl;
				string str2;
				cin >> str2;
				long num1, num2;
				num1 = testFunc(str1);
				num2 = testFunc(str2);
				if (num1 == num2) {
					if (num1 > 0 && num2 > 0) {
						float *vector1 = new float[num1];
						float *vector2 = new float[num2];
						creatVector(str1, vector1);
						creatVector(str2, vector2);
						double result0;
						result0 = vector_DOT(num1, vector1, vector2);
						cout << result0<< endl;
						delete[] vector1;
						delete[] vector2;
					}
				}
				else {
					cout << "Number of vector1's elements is not equals to number of vector2's elements" << endl;
				}
			}
			else if (str0.at(0) == '1') {
				float *vector1 = new float[200000000];
				float *vector2 = new float[200000000];
				srand((int)time(NULL));
				float array0[100];
				for (int i = 0; i < 100; i++) {
					array0[i] = (rand() % 100) + rand() / double(RAND_MAX);
				}
				for (int i = 0; i < 200000000; i++) {
					int num = i % 100;
					vector1[i] = array0[num];
					vector2[i] = array0[num];
				}
				time_t begin, end;
				double ret;
				//最简单的直接乘
				begin = clock();
				float result;
				result = vector_DOT(200000000, vector1, vector2);
				cout << result << endl;
				end = clock();
				ret = double(end - begin);
				cout << "最简单的直接乘 "<<"runtime:   " << ret << "ms"<<endl;
				//直接乘，采用循环展开，展开8个操作
				begin = clock();
				double result1;
				result1 = vector_DOT1(200000000, vector1, vector2);
				cout << result1 << endl;
				end = clock();
				ret = double(end - begin);
				cout << "直接乘，采用循环展开，展开8个操作 "<<"runtime:   " << ret <<"ms"<< endl;
				//采用循环展开的方法，并使用了多线程
				long num_theards = 6;
				long num_size = 200000000 / num_theards;
				vector<double> results_s(num_theards);
				vector<thread> threads_s;
				for (int i = 0; i < num_theards - 1; i++) {
					threads_s.push_back(thread(vector_DOT2, i * num_size, (i + 1) * num_size, vector1, vector2, ref(results_s[i])));
				}
				threads_s.push_back(thread(vector_DOT2, (num_theards - 1) * num_size, 200000000, vector1, vector2, ref(results_s[num_theards - 1])));
				begin = clock();
				for (auto &t : threads_s) {
					t.join();
				}
				double result2 = 0;
				for (int i = 0; i < num_theards; i++) {
					result2 += results_s[i];
				}
				cout << result2 << endl;
				end = clock();
				ret = double(end - begin);
				cout << "采用循环展开的方法，并使用了多线程 "<<"runtime:   " << ret << "ms"<<endl;

				//大数点乘——直接点乘，不采用循环展开

				begin = clock();
				big result_BIG;
				result_BIG = vector_DOT_BIG(200000000, vector1, vector2);
				cout << result_BIG.print() << endl;
				end = clock();
				ret = double(end - begin);
				cout << "大数点乘——直接点乘，不采用循环展开"<<"runtime:   " << ret << "ms"<<endl;

				//大数点乘，多线程直接使用
				num_theards = 4;
				num_size = 200000000 / num_theards;
				vector<big> results(num_theards);
				vector<thread> threads;
				for (int i = 0; i < num_theards - 1; i++) {
					threads.push_back(thread(vector_DOT1_BIG, i * num_size, (i + 1) * num_size, vector1, vector2, ref(results[i])));
				}
				threads.push_back(thread(vector_DOT1_BIG, (num_theards - 1)* num_size, 200000000, vector1, vector2, ref(results[num_theards - 1])));
				begin = clock();
				for (auto &t : threads) {
					t.join();
				}
				big result1_BIG = big();
				for (int i = 0; i < num_theards; i++) {
					result1_BIG = result1_BIG + results[i];
				}
				cout << result1_BIG.print() << endl;
				end = clock();
				ret = double(end - begin);
				cout << "大数点乘，多线程直接使用 "<<"runtime:   " << ret << "ms"<<endl;

				//大数点乘，多线程优化后
				vector<big> resultss(num_theards);
				vector<thread> threadss;
				for (int i = 0; i < num_theards - 1; i++) {
					threadss.push_back(thread(vector_DOT2_BIG, i * num_size, (i + 1) * num_size, vector1, vector2, ref(resultss[i])));
				}
				threadss.push_back(thread(vector_DOT2_BIG, (num_theards - 1)* num_size, 200000000, vector1, vector2, ref(resultss[num_theards - 1])));
				begin = clock();
				for (auto &t : threadss) {
					t.join();
				}
				big result2_BIG = big();
				for (int i = 0; i < num_theards; i++) {
					result2_BIG = result2_BIG + resultss[i];
				}
				cout << result2_BIG.print() << endl;
				end = clock();
				ret = double(end - begin) ;
				cout << "大数点乘，多线程优化后" <<"runtime:   " << ret << "ms"<<endl;
				//method4
				begin = clock();
				float result4 = cblas_sdot(200000000, vector1, 1, vector2, 1);
				cout << result4 << endl;
				end = clock();
				ret = double(end - begin) ;
				cout << "使用openblas"<<"runtime:   " << ret << "ms"<<endl;

				delete[] vector1;
				delete[] vector2;
			}
			else {
				cout << "you enter a wrong number" << endl;
			}
		}
	}

}
double vector_DOT(long num, float *vector1, float *vector2) {
	double dot = 0;
	long register i = 0;
	while (i < num) {
		dot += vector1[i] * vector2[i];
		i++;
	}
	return dot;
}
double vector_DOT1(long num, float *vector1, float *vector2) {
	double dot = 0;
	long register i = 0;
	long num1 = num - 16;
	while (i < num1) {
		dot += vector1[i] * vector2[i]
			+ vector1[i + 1] * vector2[i + 1]
			+ vector1[i + 2] * vector2[i + 2]
			+ vector1[i + 3] * vector2[i + 3]
			+ vector1[i + 4] * vector2[i + 4]
			+ vector1[i + 5] * vector2[i + 5]
			+ vector1[i + 6] * vector2[i + 6]
			+ vector1[i + 7] * vector2[i + 7];
		i += 8;
	}
	while (i < num) {
		dot += vector1[i] + vector2[i];
		i++;
	}
	return dot;
}
void vector_DOT2(long begin, long end, float *vector1, float *vector2, double &result) {
	result = 0;
	long register i = begin;
	long num1 = end - 16;
	while (i < num1) {
		result += vector1[i] * vector2[i]
			+ vector1[i + 1] * vector2[i + 1]
			+ vector1[i + 2] * vector2[i + 2]
			+ vector1[i + 3] * vector2[i + 3]
			+ vector1[i + 4] * vector2[i + 4]
			+ vector1[i + 5] * vector2[i + 5]
			+ vector1[i + 6] * vector2[i + 6]
			+ vector1[i + 7] * vector2[i + 7];
		i += 8;
	}
	while (i < end) {
		result += vector1[i] * vector2[i];
		i++;
	}

}

big vector_DOT_BIG(long num, float *vector1, float *vector2) {
	big dot = big();
	long register i = 0;
	while (i < num) {
		double result = 0;
		result = vector1[i] + vector2[i];
		i++;
		while ((i % 1000000) != 0 && i < num) {
			result += vector1[i] * vector2[i];
			i++;
		}
		string str = to_string(result);
		dot = dot + big(str);

	}
	return dot;
}



void vector_DOT1_BIG(long begin, long end, float *vector1, float *vector2, big &res) {
	res = big();
	double result = 0;
	long register i = begin;
	long num1 = end - 16;
	while (i < num1) {
		result = 0;
		int count = 0;
		while ((count != 10000) && (i < num1)) {
			result += vector1[i] * vector2[i]
				+ vector1[i + 1] * vector2[i + 1]
				+ vector1[i + 2] * vector2[i + 2]
				+ vector1[i + 3] * vector2[i + 3]
				+ vector1[i + 4] * vector2[i + 4]
				+ vector1[i + 5] * vector2[i + 5]
				+ vector1[i + 6] * vector2[i + 6]
				+ vector1[i + 7] * vector2[i + 7];
			i += 8;
			count += 8;
		}
		string str = to_string(result);
		res = res + big(str);
	}
	while (i < end) {
		result = 0;
		result += vector1[i] * vector2[i];
		i++;
	}
	string str = to_string(result);
	res = res + big(str);

}
void vector_DOT2_BIG(long begin, long end, float *vector1, float *vector2, big &res) {
	res = big();
	double result = 0;
	long double result1 = 0;
	long long result2 = 0;
	long register i = begin;
	long num1 = end - 16;
	while (i < num1) {
		result = 0;
		int count = 0;
		while ((count != 1000) && (i < num1)) {
			result += vector1[i] * vector2[i]
				+ vector1[i + 1] * vector2[i + 1]
				+ vector1[i + 2] * vector2[i + 2]
				+ vector1[i + 3] * vector2[i + 3]
				+ vector1[i + 4] * vector2[i + 4]
				+ vector1[i + 5] * vector2[i + 5]
				+ vector1[i + 6] * vector2[i + 6]
				+ vector1[i + 7] * vector2[i + 7];

			i += 8;
			count += 1;
		}
		result1 += fmod(result, 1.0);
		result2 += ceil(result);
	}
	string str1 = to_string(result1);
	string str2 = to_string(result2);
	res = big(str1) + big(str2);
	while (i < end) {
		result = 0;
		result += vector1[i] * vector2[i];
		i++;
	}
	string str = to_string(result);
	res = res + big(str);

}


void creatVector(string str, float *vector) {
	long length = str.length();
	long num = 1;
	long num0 = 0;
	while (num < length) {
		string str1 = "";
		while (str.at(num) != ',' && num < length - 1) {
			str1 += str.at(num);
			num++;
		}
		vector[num0++] = stof(str1);
		num++;
	}
}

long testFunc(string str) {
	long length = str.length();
	if (length < 3) {
		cout << "the length of your vector is not correct" << endl;
		return -1;
	}
	if (str.at(0) != '[') {
		cout << "the vector should begin with [" << endl;
		return -1;
	}
	if (str.at(length - 1) != ']') {
		cout << "the vector should end with ]" << endl;
		return -1;
	}
	long count = 0;
	long num = 1;
	long num0 = 0;
	while (num < length) {
		string str1 = "";
		while (str.at(num) != ',' && num < length - 1) {
			str1 += str.at(num);
			num++;
		}
		if (testNum(str1)) {
			num0++;
		}
		else {
			cout << "the type of your number is not right" << endl;
			return -1;
		}
		num++;
	}
	for (int i = 0; i < length; i++) {
		if (str.at(i) == ',') {
			if (str.at(i - 1) == ',') {
				cout << "the type of your , is not right" << endl;
				return -1;
			}
		}
	}
	return num0;
}

bool testNum(string str) {
	if (str.length() < 1) {
		return false;
	}
	int num = 0;
	if (str.at(0) == '-') {
		num = 1;
	}
	int count = 0;
	for (; num < str.length(); num++) {
		if ((str.at(num) <= '9' && str.at(num) >= '0') || str.at(num) == '.') {
			if (str.at(num) == '.') {
				count++;
			}
		}
		else {
			return false;
		}
	}
	if (count > 1) {
		return false;
	}
	return true;
}
