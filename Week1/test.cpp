#include <iostream>
#include<math.h>
#include<string>
int a[] = {1, 3, 5, 7, 9};
int &index(int);
int main(){
    
    using namespace std;
    index(2) = 25;
    const char *cityName = "system";
    cout << cityName;
    cout << endl;
    cout << index(2);
}

int &index(int j){
    return a[j];
}