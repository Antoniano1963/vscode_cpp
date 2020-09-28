#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main(){
    string str;
    getline(cin,str);
    ofstream myfile("f1.txt");
    if(myfile.is_open()){
        for (int i = 0; i < str.length();i++){
            if((str.at(i)>='a'&&str.at(i)<='z')||(str.at(i)>='A'&&str.at(i)<='Z')||str.at(i)==' '){
                myfile << str.at(i);
            }
        }
        myfile.close();
    }else{
        cout << "Unable to open the file";
    }
    ofstream yourfile("f0.txt");
    if(yourfile.is_open()){
        for (int i = 0; i < str.length();i++){
            if((str.at(i)>='a'&&str.at(i)<='z')||(str.at(i)>='A'&&str.at(i)<='Z')||str.at(i)==' '){
                if(str.at(i)>='a'&&str.at(i)<='z'){
                    yourfile << char(str.at(i)-'a'+'A');
                }else{
                    yourfile << str.at(i);
                }
            }
        }
        yourfile.close();
    }
}   