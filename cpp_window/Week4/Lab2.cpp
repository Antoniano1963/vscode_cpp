#include<iostream>
using namespace std;
#include<string>

struct CandyBar
{
    string name;
    double weight;
    int number;

};

int main(){
    CandyBar array[3];
    for (int i = 0; i < 3;i++){
        cout << "Enter brand name of a Candy bar: ";
        getline(cin,array[i].name);
        cout << "Enter weight of he Candy bar: ";
        cin >> array[i].weight;
        cout << "Enter calories (an integer value ) in the Candy bar: ";
        cin >> array[i].number;
        cin.get();
    }
    for (int i = 0; i < 3;i++){
        cout << "Brand: "<< array[i].name<<endl;
        cout << "Weight: "<< array[i].number<<endl;
        cout << "Calories: " << array[i].weight<<endl;
    }
}