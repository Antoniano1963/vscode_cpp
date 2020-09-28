#include<iostream>
#include<string>
#include "big_operation.h"

using namespace std;

int main(){
    string str1;
    cin >> str1;
    string str2;
    cin >> str2;
    big number1 = big(str1);
    big number2 = big(str2);
    big result = number1 + number2;
    cout << result.print();
}