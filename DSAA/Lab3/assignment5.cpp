#include<iostream>
#include<algorithm>
using namespace std;
int main(){
    int n, p, q;
    cin >> n;
    cin >> p;
    cin >> q;
    long *array_hp0 = new long[n];
    long *array_atk0 = new long[n];
    long *array_different = new long[n];
    for (int i = 0; i < n;i++){
        cin >> array_hp0[i];
        cin >> array_atk0[i];
    }
    long long hp = 0;
    long num0 = 1;
    for (int i = 0; i < p; i++)
    {
        num0 *= 2;
    }
    for (int i = 0; i < n;i++){
        array_different[i] = array_hp0[i] - array_atk0[i];
    }
    long long testNum1=array_different[0];
    for (int i = 0; i <n ; i++) {
        if(array_different[i]>testNum1){
            testNum1=array_different[i];
        }
    }
    int k = 0;
    for (int i = 0; i < n;i++){
        long long testNum = array_hp0[i] * num0;
        if(testNum>array_atk0[i]){
            if(testNum>hp&&testNum>testNum1){
                hp = testNum;
                k = i;
            }
        }
    }
    long long atk = 0;
    bool T = false;
    if(q>0&&hp>0){
        atk += hp;
        T = true;
        q--;
    }
    for (int i = 0; i < n;i++){
        if(i==k&&T){
            array_different[i] = 0;
            continue;
        }
        array_different[i] = array_hp0[i] - array_atk0[i];
        atk += array_atk0[i];
    }
    sort(array_different, array_different + n);
    int num = n - q;
    if(num<0){
        num = 0;
    }
    for (int i = n - 1; i >= num;i--){
        if(array_different[i]>0){
            atk += array_different[i];
        }
    }
    cout << atk << endl;
}