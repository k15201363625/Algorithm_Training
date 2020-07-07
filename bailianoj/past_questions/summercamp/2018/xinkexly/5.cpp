#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
//本质最短路 并且只有0 1 
//双端队列最短路
int n,a,b;
int g[110][110];
int d[110];
int getmin(){
    deque<int> q;
    memset(d,0x3f,sizeof d);
    q.push_back(a);
    d[a] = 0;
    while(q.size()){
        int t = q.front();
        q.pop_front();
        if(t==b) break;
        for(int i=1;i<=n;i++)
            if(g[t][i]==1){
                if(d[i]>d[t]+1){
                    d[i] = d[t] + 1;
                    q.push_back(i);
                } 
            }else if(g[t][i]==0){
                if(d[i]>d[t]){
                    d[i] = d[t];
                    q.push_front(i);
                }
            }
    }
    if(d[b]==0x3f3f3f3f) return -1;
    return d[b];
}
int main(){
    cin>>n>>a>>b;
    int k,tmp;
    memset(g,0x3f,sizeof g);
    for(int i=1;i<=n;i++){
        cin>>k;
        if(k==0) continue;
        cin>>tmp;
        g[i][tmp] = 0;
        for(int j=1;j<k;j++)
            cin>>tmp,g[i][tmp]=1;
    }
    cout<<getmin()<<endl;
    return 0;
}