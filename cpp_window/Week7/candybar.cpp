#include "candybar.h"
using namespace std;
void setCandyBar(CandyBar &ch){
    cout << "Call the set function of Passing by reference:" << endl;
    cout << "Enter brand name of a Candy bar: ";
    scanf("\n%[^\n]", ch.brand);
    cout << "Enter weight of the Candy bar: ";
    cin >> ch.weight;
    cout << "Enter calories (an integer value) in the Candy bar: ";
    cin >> ch.calorie;

}
void setCandyBar(CandyBar *ch){
    cout << "Call the set function of Passing by pointer:" << endl;
    cout << "Enter brand name of a Candy bar: ";
    scanf("\n%[^\n]", ch->brand);
    cout << "Enter weight of the Candy bar: ";
    cin >> ch->weight;
    cout << "Enter calories (an integer value) in the Candy bar: ";
    cin >> ch->calorie;

}

void showCandyBar(const CandyBar &ch){
    cout << "Call the show function of Passing by reference:" << endl;
    cout << "Brand:" << ch.brand << endl;
    cout << "Weight: " << ch.weight << endl;
    cout << "Calories: " << ch.calorie << endl;
}

void showCandyBar(const CandyBar *ch){
    cout << "Call the show function of Passing by point:" << endl;
    cout << "Brand:" << ch->brand << endl;
    cout << "Weight: " << ch->weight << endl;
    cout << "Calories: " << ch->calorie << endl;
}