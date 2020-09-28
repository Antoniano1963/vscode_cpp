#include<iostream>
#include<string>
#include<map>
#include<stack>
#include <stdio.h>  
#include <stdlib.h>
using namespace std;
map<const char,double >operatorMap;
int main(){
    string str0;
    char ch1,ch2;
    double number1,number2;
    cin>>ch1>>ch2;
    cin>>number1>>number2;
    operatorMap[ch1]=number1;
    operatorMap[ch2] = number2;
    string str1;
    cin >> str1;
    cout << operatorMap[str1.at(0)];
}
