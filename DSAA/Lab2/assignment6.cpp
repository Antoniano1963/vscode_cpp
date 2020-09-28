#include<iostream>
#include<string>
using namespace std;
long get_dis(long *robot,long *people){
    return (abs(robot[0]-people[0])+abs(robot[1]-people[1]));
}

int main(){
    long people[2];
    long robot[2];
    cin>>robot[0]>>robot[1]>>people[0]>>people[1];
    int num;
    cin>>num;
    char *str0 = new char[num];
    cin>>str0;
    long result=0;
    bool T=true;
    while(result<1000000&&T){
        for(int i=0;i<num;i++){
            if(str0[i]=='D'){
                robot[1]-=1;
            }
            if(str0[i]=='U'){
                robot[1]+=1;
            }
            if(str0[i]=='L'){
                robot[0]-=1;
            }if(str0[i]=='R'){
                robot[0]+=1;
            }
            result++;
            if(result>=get_dis(robot,people)){
                T=false;
                cout<<result;
                break;
            }

        }
    }
    long testNum=get_dis(robot,people)-result;
    if(T){
        for(int i=0;i<num;i++){
            if(str0[i]=='D'){
                robot[1]-=1;
            }
            if(str0[i]=='U'){
                robot[1]+=1;
            }
            if(str0[i]=='L'){
                robot[0]-=1;
            }if(str0[i]=='R'){
                robot[0]+=1;
            }
            result++;
            if(result>=get_dis(robot,people)){
                T=false;
                cout<<result;
                break;
            }
        }
        if(testNum==get_dis(robot,people)-result){
            T=false;
            cout<<-1;
        }else{
            while(T){
                for(int i=0;i<num;i++){
                    if(str0[i]=='D'){
                        robot[1]-=1;
                    }
                    if(str0[i]=='U'){
                        robot[1]+=1;
                    }
                    if(str0[i]=='L'){
                        robot[0]-=1;
                    }if(str0[i]=='R'){
                        robot[0]+=1;
                    }
                    result++;
                    if(result>=get_dis(robot,people)){
                        T=false;
                        cout<<result;
                        break;
                    }
                }
            }
        }
    }

}
