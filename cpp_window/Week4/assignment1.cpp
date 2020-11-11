#include<iostream>
#include<string>
#include<ctime>
#include<algorithm>
#include<thread>
#include<numeric>
#include<vector>
#include<functional>
using namespace std;
bool testNum(string str);
long testFunc(string str);
void creatVector(string str, float *vector);
double vector_DOT(long num, float *vector1, float *vector2);
double vector_DOT1(long num, float *vector1, float *vector2);
void vector_DOT2(long begin, long end, float *vector1, float *vector2, double &result);
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
						double result;
						result = vector_DOT(num1, vector1, vector2);
						cout << result << endl;
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
					array0[i] = rand() + rand() / double(RAND_MAX);
				}
				for (int i = 0; i < 200000000; i++) {
					int num = i % 100;
					vector1[i] = array0[num];
					vector2[i] = array0[num];
				}
				time_t begin, end;
				double ret;
				begin = clock();
				double result;
				result = vector_DOT(200000000, vector1, vector2);
				cout << result << endl;
				end = clock();
				ret = double(end - begin) / CLOCKS_PER_SEC;
				cout << "runtime:   " << ret << endl;
				begin = clock();
				double result1;
				result1 = vector_DOT1(200000000, vector1, vector2);
				cout << result1 << endl;
				end = clock();
				ret = double(end - begin) / CLOCKS_PER_SEC;
				cout << "runtime:   " << ret << endl;
				long num_theards = 6;
				long num_size = 200000000 / num_theards;
				vector<double> results(num_theards);
				vector<thread> threads;
				for (int i = 0; i < num_theards - 1; i++) {
					threads.push_back(thread(vector_DOT2, i * num_size, (i + 1) * num_size, vector1, vector2, ref(results[i])));
				}
				threads.push_back(thread(vector_DOT2, 5 * num_size, 200000000, vector1, vector2, ref(results[num_theards - 1])));
				begin = clock();
				for (auto &t : threads) {
					t.join();
				}
				double result2 = 0;
				for (int i = 0; i < num_theards; i++) {
					result2 += results[i];
				}
				cout << result2 << endl;
				end = clock();
				ret = double(end - begin) / CLOCKS_PER_SEC;
				cout << "runtime:   " << ret << endl;

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
		if (str.at(num) <= '9' || str.at(num) >= '0' || str.at(num) == '.') {
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
