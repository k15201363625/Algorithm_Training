#include<iostream>
#include<cstring>
using namespace std;
const int N = 100010;
int primes[N],cnt = 0;
bool st[N];
//线性筛
int n;
void getprimes(){
    st[1] = true;
    for(int i=2;i<n;i++){
        if(!st[i]) primes[cnt++] = i;
        //保证每个数字被最小素因子筛掉
        for(int j=0;primes[j]<=n/i;j++){
            st[primes[j]*i] = true;
            if(i%primes[j]==0) break;
        }
    }
}
int start,ed;
bool judge(int x){
    int rx = 0,tmp = x;
    while(true){
        rx += tmp%10;
        tmp/=10;
        if(!tmp) break;
        rx*=10;
    }
    if(!st[x]) return !st[rx];
    return false;
}
int main(){
    cin>>start>>ed;
    n = 1;
    while(n<ed) n*=10;
    getprimes();
    bool flag = false;
    for(int i=start;i<=ed;i++){
        if(judge(i)){
            if(flag) cout<<","<<i;
            else{
                cout<<i;
                flag = true;
            }
        }
    } 
    if(!flag) cout<<"No";
    cout<<endl;
    return 0;
}