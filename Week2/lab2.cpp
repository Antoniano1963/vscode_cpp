#include <iostream>
#include<string>
#include<cstdio>
using namespace std;
int main(){
    int num;
    cout << "Enter a number of seconds:";
    cin >> num;
    while (cin.fail())
    {
        cin.clear();
        string str;
        cin >> str;
        cout << str << " is a wrong input, please input again: "<<endl;
        cout << num<<endl;
        cin >> num;
    }
    int day, hour, minute, second;
    day = num / 86400;
    hour = (num % 86400) / 3600;
    minute = (num % 3600) / 60;
    second = num % 60;
    printf("%d seconds = %d days, %d hours, %d minutes, %d seconds", num, day, hour, minute, second);
    return 0;
}