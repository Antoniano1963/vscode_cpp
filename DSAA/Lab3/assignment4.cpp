#include<iostream>
using namespace std;
int main(){
    int n;
    cin >> n;
    int *array0 = new int[n];
    int *array1 = new int[n];
    for (int i = 0; i < n;i++){
        cin >> array0[n];
    }

}
void mergeSort(int begin,int end,int *array0,int *array1){
    if(begin>end){
        return;
    }
    int middle = (end - begin) / 2 + begin;
    mergeSort(begin, middle,array0, array1);
    mergeSort(middle + 1, end, array0, array1);
    countFunc(begin, end, middle, array0, array1);


}
void countFunc(int begin,int end,int middle,int *array0,int *array1){
    int num1 = begin;
    int num2 = middle + 1;
    int k = begin; 

}