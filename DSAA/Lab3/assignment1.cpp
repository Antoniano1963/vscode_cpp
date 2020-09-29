#include<iostream>
using namespace std;
void sortFunc(int array0[], int array1[], int end1, int end2);
int main(){
    int n;
    cin >> n;
    for (int i = 0; i < n;i++){
        int num1, num2;
        cin >> num1>>num2;
        int *array0 = new int[num1];
        int *array1 = new int[num2];
        for (int i = 0; i < num1;i++){
            cin >> array0[i];
        }
        for (int i = 0; i < num2;i++){
            cin >> array1[i];
        }
        sortFunc(array0, array1,num1,num2);
        delete array0;
        delete array1;
    }
}
void sortFunc(int array0[],int array1[],int end1,int end2){
    int num1 = 0;
    int num2 = 0;
    int k = 0;
    int *result=new int[end1 + end2];
    while(num1<end1&&num2<end2){
        if(array0[num1]>array1[num2]){
            result[k] = array1[num2];
            num2++;
            k++;
        }else{
            result[k] = array0[num1];
            num1++;
            k++;
        }
    }
    while(num1<end1){
        result[k] = array0[num1];
        num1++;
        k++;
    }
    while (num2<end2)
    {
        result[k] = array1[num2];
        k++;
        num2++;
    }
    for (int i = 0; i < end1 + end2-1;i++){
        cout << result[i] << " ";
    }
    cout << result[end1 + end2 - 1] << endl;
}