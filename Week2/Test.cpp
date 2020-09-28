#include <stdio.h>
#include<iostream>
using namespace std;
int  main()   
{
    short a = 32767;
    int(a) = int(a + 32768);
    cout << a;
}    
