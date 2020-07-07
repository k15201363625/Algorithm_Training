#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//图论+隐形并查集 维护联通性
const int N = 1e3+10,M = 2e6+10;
int h[N],e[M],ne[M],idx=0;
int p[N];
bool st[N];
int n,d;
void init(){
    idx = 0;
    memset(st,0,sizeof st);
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++) p[i] = i;
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
int x[N],y[N];
void conn(int k){
    for(int i=1;i<k;i++){
        if((x[i]-x[k])*(x[i]-x[k])+(y[i]-y[k])*(y[i]-y[k])<=d*d){
            add(i,k);
            add(k,i);
        }
    }
}
void repair(int a){
    int pa = find(a),pb;
    for(int i=h[a];i!=-1;i=ne[i]){
        int j = e[i];
        if(!st[j]) continue;
        pb = find(j);
        if(pa!=pb) p[pb] = pa;
    }
}
int main(){
    cin>>n>>d;
    init();
    for(int i=1;i<=n;i++){
        cin>>x[i]>>y[i];
        conn(i);
    }
    char op;
    int a,b;
    while(cin>>op){
        if(op=='O'){
            cin>>a;
            if(st[a]) continue;
            repair(a);
            st[a] = true;
        }else if(op=='S'){
            cin>>a>>b;
            if(!st[a] || !st[b]) cout<<"FAIL"<<endl;
            else if(find(a)==find(b)) cout<<"SUCCESS"<<endl;
            else cout<<"FAIL"<<endl;
        }
    }
    return 0;
}