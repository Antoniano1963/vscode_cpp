#include<iostream>
using namespace std;
int main(){
    for (int i = 0; i < 7;i++){
        for (int j = 0; j <= i;j++){
            cout << (j + 1);
        }
        for (int k = i; k < 6;k++){
            cout << '*';
        }
        cout << endl;
    }
}