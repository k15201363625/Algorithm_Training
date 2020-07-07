#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int nums[6] = {0,90,990,9990,99990,999990};
int getmaxstr(int num){
    for(int i=0;i<6;i++){
        if(num>=nums[i] && num<nums[i]+9)
            return num;
        else if(num<nums[i]){
            return nums[i-1]+9;
        }
    }
    return nums[5]+9;
}
int main(){
    int num;
    while(cin>>num,num){
        cout<<getmaxstr(num)<<endl;
    }
    return 0;
}