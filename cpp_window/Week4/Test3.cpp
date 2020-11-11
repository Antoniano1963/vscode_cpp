#include <iostream>
#include <thread>
#include <stdlib.h> //sleep
 
using namespace std;
 
void t1(int n)  //普通的函数，用来执行线程
{
    for (int i = 0; i < 10; ++i)
    {
        cout << "t1111\n";
    }
}
void t2(int n)
{
    for (int i = 0; i < 20; ++i)
    {
        cout << "t22222\n";
    }
}
int main()
{
    thread th1(t1);  //实例化一个线程对象th1，使用函数t1构造，然后该线程就开始执行了（t1()）
    thread th2(t2);
 
    th1.join(); // 必须将线程join或者detach 等待子线程结束主进程才可以退出
    th2.join(); 
 
    //or use detach
    //th1.detach();
    //th2.detach();
 
    cout << "here is main\n\n";
 
    return 0;
}
