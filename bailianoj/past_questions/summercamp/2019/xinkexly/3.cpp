#include<iostream>
#include<cstring>
using namespace std;
const int N = 55;
long long f[N];
int n,k;
bool judge(int num){
    while(num){
        if(num%10==4) return false;
        num /= 10;
    }
    return true;
}
void getres(){
    memset(f,0,sizeof f);
    f[0] = 1;
    for(int i=1;i<=n;i++){
        for(int j=i-1;j>=i-k && j>=0;j--){
            if(!judge(i-j)) continue;
            f[i] += f[j];
        }
    }
}
int main(){
    while(cin>>n>>k,n||k){
        getres();
        cout<<f[n]<<endl;
    }
    return 0;   
}