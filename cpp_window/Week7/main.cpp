#include "candybar.h"

int main(){
    CandyBar bar;
    setCandyBar(&bar);
    showCandyBar(&bar);
    setCandyBar(bar);
    showCandyBar(bar);
}