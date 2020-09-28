#include<iostream>
#include<list>
using namespace std;
int main()
{
    list<int> l1;
    list<int> l2(2,0);
    list<int>::iterator iter;
    l1.push_back(1);
    l1.push_back(2);
    l2.push_back(3);
    l1.merge(l2,greater<int>());//合并后升序排列，实际上默认就是升序
    iter = l1.begin();
    cout << *iter<<endl;
    for(iter = l1.begin() ; iter != l1.end() ; iter++)
    {
        cout<<*iter<<" ";
    }
    cout<<endl<<endl;
    if(l2.empty())
    {
        cout<<"l2 变为空 ！！";
    }
    cout<<endl<<endl;
    return 0;
}