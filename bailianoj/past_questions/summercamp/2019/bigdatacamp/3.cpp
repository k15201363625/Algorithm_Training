#include<iostream>
#include<cstring>
using namespace std;
int n,k;
char g[10][10];
int ans = 0;
bool visc[10];
void dfs(int row,int num){
    //当前行数 已经摆放的元素数目
    if(num==k){
        ans++;
        return;
    }
    for(int i=row;i<n;i++){
        if(n-i<k - num) return;
        for(int j=0;j<n;j++){
            if(!visc[j] && g[i][j]=='#'){
                visc[j] = true;
                dfs(i+1,num+1);
                visc[j] = false;
            }
        }
    }
}
int main(){
    while(cin>>n>>k){
        if(n==-1 && k==-1) break;
        for(int i=0;i<n;i++) cin>>g[i];
        ans = 0;
        dfs(0,0);
        cout<<ans<<endl;
    }
    return 0;
}