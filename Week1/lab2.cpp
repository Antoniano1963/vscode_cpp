#include <iostream>

void displayString();
int main(){
    using namespace std;
    displayString();
    displayString();
    displayString();
    std::cout << std::endl;
    displayString();
    displayString();
    cout << endl;
    displayString();
    cout << endl;
    return 0;
}
void displayString(){
    std::cout << "String";
}