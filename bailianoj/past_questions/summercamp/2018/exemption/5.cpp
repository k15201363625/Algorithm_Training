#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//由于数目很少 所以可以用暴力枚举确定第一问结果 之后暴力枚举第一问结果得到第二问
//从第一问的关键点枚举 才能保证可能是合格的分割点 否则无法保证可以到达划分后的所有点
//第一问算是第二问的提示
//即设置状态控制后的dfs
const int N = 55,M = 5010;
int h[N],e[M],ne[M],idx = 0;
int n;
int st[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void init(){
    idx = 0;
    memset(st,0,sizeof st);
    memset(h,-1,sizeof h);
}
bool dfs(int u){
    st[u] = 1;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(j==n) return true;
        if(st[j]) continue;
        if(dfs(j)) return true;
    }
    return false;
}
void dfs2(int u){
    st[u] = 1;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(st[j]) continue;
        dfs2(j);
    }
}
bool dfs3(int u){
    st[u] = 2;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(st[j]==1) return false;
        if(st[j]==2) continue;
        if(!dfs3(j)) return false;
    }
    return true;
}
int ans1[N],ans2[N];
int main(){
    int b;
    init();
    while(cin>>b){
        if(b==-1) break;
        add(n,b);
        while(cin>>b,b!=-2) add(n,b);
        n++;
    }
    int cnt = 0,cnt2 = 0;
    for(int i=1;i<=n-1;i++){
        memset(st,0,sizeof st);
        st[i] = 1;
        if(dfs(0)) continue;
        ans1[cnt++] = i; 
    }
    cout<<cnt<<" ";
    for(int i=0;i<cnt;i++) cout<<ans1[i]<<" ";
    cout<<endl;
    for(int i=0;i<cnt;i++){
        memset(st,0,sizeof st);
        st[ans1[i]] = 2;
        dfs2(0);
        if(dfs3(ans1[i])) ans2[cnt2++] = ans1[i];
    }
    cout<<cnt2<<" ";
    for(int i=0;i<cnt2;i++) cout<<ans2[i]<<" ";
    cout<<endl;
    return 0;
}