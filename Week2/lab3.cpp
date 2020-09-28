#include<iostream>
#include<cstdio>
#include<string>
using namespace std;
int main(){
    char char1;
    cout << "Please Enter a Character :";
    cin >> char1;
    while (cin.fail())
    {
        cin.clear();
        string str;
        cin >> str;
        cout << str << "is a wrong char, please input again: ";
        cin >> char1;
    }
    int intNum;
    cout << "Please Enter an Interger Value :";
    cin >> intNum;
    while (cin.fail())
    {
        cin.clear();
        string str;
        cin >> str;
        cout << str << " is a wrong Interger, please input again: ";
        cin >> intNum;
    }
    float floatNum;
    cout << "Please Enter Float Value: ";
    cin >> floatNum;
    while (cin.fail())
    {
        cin.clear();
        string str;
        cin >> str;
        cout << str << " is a wrong Float, please input again: ";
        cin >> floatNum;
    }
    cout << "The variables you entered were:" << endl;
    printf("The Character value that you entered is %c \n", char1);
    printf("The Interger value that you entered is %d \n", intNum);
    printf("The Float value that you entered is %.4f \n", floatNum);
    return 0;
}