#include<iostream>
#include<cstdio>
#include<cstring>
#include<iomanip>
using namespace std;
bool judge(int num){
    if(num%4==0){
        if(num%400==0) return true;
        else if(num%100!=0) return true;
        else return false;
    }
    return false;
}
int monthdays[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int getdaynums(int year,int month){
    int days = 0;
    for(int i=1900;i<year;i++){
        days += judge(i)?366:365;
    }
    for(int i=0;i<month;i++){
        if(i==2 && judge(year)){
            days += 29;
        }else{
            days += monthdays[i-1];
        }
    }
    return days;

}

void printcalender(int year,int month){
    int days = getdaynums(year,month);
    int start = days%7 + 1;
    if(month==2 && judge(year)) days = 29;
    else days = monthdays[month-1];
    const char* weeks[7] = {"Sun","Mon","Tue","Wed","Thu","Fri","Sat"};
    for(int i=0;i<7;i++) cout<<weeks[i]<<" ";
    cout<<endl;
    int stpos = 3;
    if(start==7) stpos = 3;
    else stpos = 3+start*4;

    int outw = stpos;
    for(int i=1;i<=days;i++){
        cout<<setw(outw)<<i;
        stpos += 4;
        outw = 4;
        if(stpos>27){
            cout<<endl;
            stpos = 3;  
            outw = stpos;
        }       
    }
    cout<<endl;
}
int main(){
    int year,month;
    cin>>year>>month;
    printcalender(year,month);
    return 0;
}