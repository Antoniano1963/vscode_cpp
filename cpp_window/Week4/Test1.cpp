#include<string>
#include<cstdlib>
#include<iostream>
using namespace std;
int main(){
    string str= "-1.315";
    double num;
    num = stof(str);
    cout << num << endl;
}