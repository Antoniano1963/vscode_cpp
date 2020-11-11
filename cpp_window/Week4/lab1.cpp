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
    CandyBar Bar1;
    cout << "Enter brand name of a Candy bar: ";
    getline(cin,Bar1.name);
    cout << "Enter weight of he Candy bar: ";
    cin >> Bar1.weight;
    cout << "Enter calories (an integer value ) in the Candy bar: ";
    cin >> Bar1.number;
    cout << "Brand: ";
    cout << Bar1.name<<endl;
    cout << "Weight: ";
    cout << Bar1.weight<<endl;
    cout << "Calories: " << Bar1.number<<endl;

}
