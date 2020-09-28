#include<iostream>
using namespace std;
int main(){
    cout << "Enter the quiz, mid-term and final scores:";
    double totalNum = 0;
    for (int i = 0; i < 3;i++){
        double currentNum;
        cin >> currentNum;
        totalNum += currentNum;

    }
    double average = totalNum / 3;
    char grade;
    if(average>=90){
        grade == 'A';
    }else if(average>=70&&average<90){
        grade = 'B';

    }else if(average>=50&&average<70){
        grade = 'C';
    }else{
        grade = 'D';
    }
    cout << "average score = " << average << " grade = " << grade;
}