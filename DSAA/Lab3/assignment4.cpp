#include<iostream>
using namespace std;

void mergeSort(int begin, int end, int *array0, int *array1);
void countFunc(int begin, int end, int middle, int *array0, int *array1);
int main(){
    int n;
    cin >> n;
    int *array0 = new int[n];
    int *array1 = new int[n];
    for (int i = 0; i < n;i++){
        cin >> array0[n];
    }
    mergeSort(0, n - 1, array0, array1);
    for (int i = 0; i < n;i++){
        cout << array0[i] + " ";
    }
}
void mergeSort(int begin,int end,int *array0,int *array1){
    if(begin>=end){
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
    while((num1<=middle)&&(num2<=end)){
        if(array0[num1]>array0[num2]){
            array1[k] = array0[num2];
            k++;
            num2++;
        }else{
            array1[k] = array0[num1];
            k++;
            num1++;
        }
    }
    while (num1<=middle)
    {
        array1[k] = array0[num1];
        num1++;
    }
    while(num2<=end){
        array1[k] = array0[num2];
        k++;
        num2++;
    }
    for (int i = begin; i <= end;i++){
        array0[i] = array1[i];
    }
}