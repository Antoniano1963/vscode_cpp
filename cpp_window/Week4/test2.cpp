#include<iostream>
using namespace std;
int main(){
    float *vector = new float[200000000];
    float *vector1 = new float[200000000];
    for (int i = 0; i < 200000000;i++){
        vector[i] = 1;
        vector1[i] = 1;
    }
    cout << vector[10000000]<<" "<<vector1[10000000];
}