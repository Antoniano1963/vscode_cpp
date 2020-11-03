#include <iostream>
using namespace std;

template <typename T>
T max5(T array[5]){
    T max0=array[0];
    for (int i = 1; i < 5;i++){
        if(array[i]>max0){
            max0 = array[i];
        }
    }
    return max0;
}
int main(){
    int array0[5] = {1, 2, 3, 4, 5};
    double array1[5] = {1.1, 2.0, 3.0, 4.0, 5.5};
    cout << "Max int = " << max5(array0) << endl;
    cout << "Max double = " << max5(array1) << endl;
}