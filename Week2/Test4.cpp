#include <iostream>  
#include <algorithm>  
using namespace std;  
  
void printPairSums(int data[], int size, int sum);  
int main(int argc, char* argv[])  
{  
    int data[] = {2,2,2,2,2,2,2};  
    int size = sizeof(data) / sizeof(data[0]);  
    int i;  
    sort(data, data + size);  
    printPairSums(data, size, 4);  
  
    return 0;  
}  
void printPairSums(int data[], int size, int sum)  
{  
    int first = 0;  
    int last = size -1;  
    int s = 0;  
    while (first < last)  
    {  
        s = data[first] + data[last];  
        if (s == sum)  
        {  
            cout << data[first] << " + " << data[last] << " = " << sum << endl;  
            first++;  
            last--;  
        }  
        else if (s < sum)  
        {  
            first++;  
        }  
        else  
        {  
            last--;  
        }  
    }  
}  