//
// Created by Antoniano on 2021/1/5.
//

#ifndef FINAL_PROJECT_MYEXCEPTION_H
#define FINAL_PROJECT_MYEXCEPTION_H
#include<exception>
#include "string"
using namespace std;

class MyException:public exception
{
public:
    string wrong;
    MyException(string wrong);
};

#endif //FINAL_PROJECT_MYEXCEPTION_H
