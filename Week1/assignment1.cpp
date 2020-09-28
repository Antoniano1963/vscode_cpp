#include <iostream>
#include<math.h>
#include<string>
#include<string.h>
#include<assert.h>
using namespace std;
int n;
long *array1;
long myFunc(string str1)
{
	long result = 0;
	for (int i = 0; i < str1.size(); i++) {
        if(str1.at(i)=='-'){
            result = -1;
            continue;
        }
		result = result * 10 + (str1[i] - '0');
	}
	return result;
}
int main() {
	using namespace std;
	cout << "Please input the total number n you want calculate(int n>0)";
	cin >> n;
	while (cin.fail() || n <= 0)
	{
		cin.clear();
		cout << "you input a wrong argument for n.";
		cin.ignore(100, '\n');
		cin >> n;

	}
	array1 = new long[n];
	assert(array1 != NULL);
	for (int i = 0; i < n; i++) {
		string str;
		bool T = true;
		while (T) {
			cout << "input your " << i+1 << "th" << " number (abs(n)<10^9, Decimal not supported)" << endl;
			cin >> str;
			T = false;
			for (int j = 0; j < str.size(); j++) {
                if(str.size()>9){
                    cout << "you input a wrong number "<<endl;
                    T = true;
                    break;
                }
				if (str[j]<'0' || str[j]>'9') {
                    if(str[j]!='-'){
                        T = true;
                        cout << "you input a wrong number "<<endl;
                        break;
                    }
				}
			}
		}
		array1[i] = myFunc(str);
	}
	cout << endl;
    int totalLog = 0;
    long result = 1;
    for (int i = 0; i < n;i++){
        totalLog += log2(array1[i]);

    }
    if(totalLog>=32){
        cout << "The numbers a and b are too big!" << endl;
        cout << "The result is approximately equal to 2^" << totalLog << endl;
    }else{
        for (int i = 0; i < n;i++){
            result *= array1[i];
        }
        cout << "The result of multiplying " << n << " Numbers is going to be " << result << endl;
    }
    delete array1;
}
