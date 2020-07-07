#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/*
int mons[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
bool judge(int year){
    if(year%4==0){
        if(year%400 == 0) return true;
        else if(year%100 == 0) return false;
        return true;
    }   
    return false;
}
int main(){
    int sy,sm,sd,ey,em,ed;
    cin>>sy>>sm>>sd>>ey>>em>>ed;
    int res = 0;
    for(int i=sy;i<ey;i++){
        if(judge(i)) res += 366;
        else res += 365;
    }
    for(int i=1;i<sm;i++){
        if(i==2 && judge(sy)) res -= 29;
        else res -= mons[i-1];
    }
    res -= sd;
    for(int i=1;i<em;i++){
        if(i==2 && judge(ey)) res += 29;
        else res += mons[i-1];
    }
    res += ed;
    cout<<res<<endl;
    return 0;
}
*/
//hash n^2 不能二分
//manacher n
//暴力 n^3
const int N = 110;
char s[N];
int check(int len){
    for(int i=1;i+len-1<=strlen(s+1);i++){
        int mid = i+(len+1)/2-1,l,r;
        if(len%2==0) l = mid,r = mid+1;
        else l = mid - 1,r = mid + 1;
        bool flag = true;
        for(int i=0;i<len/2;i++){
            if(s[l-i]!=s[r+i]){
                flag = false;
                break;
            }
        }
        if(flag) return i;
    }
    return 0;
}
void getmax(){
    int l = strlen(s+1);
    for(int i=l;i>=1;i--){
        if(check(i)){
            l = i;
            break;
        } 
    }
    int st=check(l);
    for(int i=0;i<l;i++) cout<<s[st+i];
    cout<<endl;
}
int main(){
    int n;
    cin>>n;
    while(n--){
        cin>>(s+1);
        getmax();
    }
    return 0;
}