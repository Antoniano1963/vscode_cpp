#include<iostream>
#include <stdio.h>  
#include <stdlib.h>
#include<string>
using namespace std;

int main(){
    cout << "Enter word(to stop, type the word done>:" << endl;
    int count = 0;
    string str;
    cin >> str;
    while(str.compare("done")!=0){
        count++;
        cin >> str;
    }
    cout << "You entered a total of "<<count<<" words.";

}