#include<iostream>
#include<string>
using namespace std;
int main(){
    string str = "";
    string str1 = "15156";
    str += '5';
    str += '3';
    str += str1.at(1);
    for (int i = 0; i < str1.length();i++){
        str += str1.at(i);
    }
        cout << str;
}