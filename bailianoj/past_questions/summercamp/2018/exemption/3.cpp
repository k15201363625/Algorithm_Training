#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//二分图判断问题 染色法 也可以带权并查集
const int N = 2010,M = 2e6+10;
int h[N],e[M],ne[M],idx = 0;
int n,m;
int st[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void init(){
    memset(h,-1,sizeof h);
    memset(st,0,sizeof st);
    idx = 0;
}
bool dfs(int u,int fa){
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(j==fa) continue;
        if(!st[j]){
            st[j] = 3-st[u];
            if(!dfs(j,u)) return false;
        }else if(st[j]==st[u]) return false;
    }
    return true;
}
int main(){
    int T,a,b;
    cin>>T;
    for(int i=1;i<=T;i++){
        cin>>n>>m;
        init();
        for(int i=0;i<m;i++){
            cin>>a>>b;
            add(a,b),add(b,a);
        }
        cout<<"Scenario #"<<i<<":"<<endl;
        bool res = true;
        for(int i=1;i<=n;i++){
            if(st[i]) continue;
            st[i] = 1;
            if(!dfs(i,0)){
                res = false;
                break;
            } 
        }
        if(res) cout<<"No suspicious bugs found!"<<endl;
        else cout<<"Suspicious bugs found!"<<endl;
        cout<<endl;
    }
    return 0;
}

/*
const int N = 2010;
int p[N],d[N];
int n,m;
int mod(int x){
    return (x%2+2)%2;
}
int find(int x){
    if(p[x]==x) return p[x];
    int t = find(p[x]);
    d[x] = mod(d[x]+d[p[x]]);
    return p[x] = t;
}
int main(){
int T,a,b;
    cin>>T;
    for(int i=1;i<=T;i++){
        cin>>n>>m;
        for(int i=1;i<=n;i++) p[i] = i,d[i] = 0;
        int pa,pb;
        bool res = true;
        for(int i=0;i<m;i++){
            cin>>a>>b;
            if(!res) continue;
            pa = find(a),pb = find(b);
            if(pa==pb){
                if(d[a] != d[b]) continue;
                else res = false;
            }else{
                p[pa] = pb;
                //d[pa] + d[a] = d[b] + 1
                d[pa] = mod(d[b]-d[a]+1);
            }
        }
        cout<<"Scenario #"<<i<<":"<<endl;
        if(res) cout<<"No suspicious bugs found!"<<endl;
        else cout<<"Suspicious bugs found!"<<endl;
        cout<<endl;
    }
    return 0;
}
*/
