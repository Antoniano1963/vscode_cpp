#include<iostream>

using namespace std;
int main(){
    int sum = 0;
    int inputNumber = -1;
    while(inputNumber!=0){
        cout << "Enter an integer number:";
        cin >> inputNumber;
        sum += inputNumber;
        cout <<"The cumulative sum of the entries to date is :" << sum << endl;
    }
}