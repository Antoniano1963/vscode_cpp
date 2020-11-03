#include<iostream>
#include<string>
using namespace std;
int readScores(double scores[], int max) {
    /*
     *  Please add function body
     */
    cout<<"Enter score for each judge in the range 0 to 10"<<endl;
    cout<<"Enter a blank line to signal the end of the list"<<endl;
    for(int i=0;i<max;i++){
        cout<<"Judge #"<<i+1<<":";
        string str;
        getline(cin,str);
        if(str.length()==0){
            return i;
        }
        else{
            scores[i]=stod(str);
        }

    }
    return max;
}
int main(){
    int max = 10;
    double scores[10];
    int num=readScores(scores, max);
    cout << num << endl;
}