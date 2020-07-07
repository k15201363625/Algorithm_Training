#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
//贪心 + 逆向思维
const int N = 1e4+10;
long long c[N],y[N],n,s;
int main(){
    cin>>n>>s;
    long long res = 0;
    long long minc = 0,minid = 0;
    for(int i=1;i<=n;i++){
        cin>>c[i]>>y[i];
        if(minid==0){
            minc = c[i]+(n-i)*s;
            minid = i;
        }else if(minc>c[i]+(n-i)*s){
            minc = c[i] + (n-i)*s;
            minid = i;
        }
        res += y[i]*(c[minid]+(i-minid)*s);
    }
    cout<<res<<endl;
    return 0;
}