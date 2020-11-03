#ifndef EXE_CANDYBAR_H
#define EXE_CANDYBAR_H
#include<iostream>
#include<string>

const int LEN = 30;
struct CandyBar{
    char brand[LEN];
    double weight;
    int calorie;
};

void setCandyBar(CandyBar &ch);
void setCandyBar(CandyBar *ch);
void showCandyBar(const CandyBar &ch);
void showCandyBar(const CandyBar *ch);

#endif