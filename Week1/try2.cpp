#include <iostream>
using namespace std;

void f(int arr[], int k)
{cout << sizeof(arr) <<' '<< arr<<' '<<*arr <<' '<<sizeof(*arr)<<' '<< &arr<<"   " << sizeof(k) << endl;
}

int main()
{ int a[10]={1,2,3,4,5,6,7,8,9,0};
    cout << sizeof(a) << endl;
    f(a, 10);
}
