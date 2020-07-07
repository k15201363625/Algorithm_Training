#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//稠密图即可
const int N = 110;
int n,m;
int w[N][N],level[N];
int d[N];
bool st[N];
int dijkstra(int down,int up){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    d[0] = 0;
    for(int i=1;i<=n;i++){//n+1个点 只需要找n个点即可
        int target = -1;
        for(int j=0;j<=n;j++){
            if(!st[j] && (target==-1 || d[target]>d[j]))
                target = j;
        }
        st[target] = true;
        for(int j=1;j<=n;j++){
            if(level[j]>=down && level[j]<=up) d[j] = min(d[j],d[target]+w[target][j]);
        }
    }
    return d[1];
}
int main(){
    cin>>m>>n;
    memset(w,0x3f,sizeof w);
    for(int i=1;i<=n;i++){
        int p,cnt;
        cin>>p>>level[i]>>cnt;
        w[0][i] = p;
        while(cnt--){
            int id,cost;
            cin>>id>>cost;
            w[id][i] = min(w[id][i],cost);
        }
    }
    int res = 0x3f3f3f3f;
    //枚举限制区间 国王未必是最高的
    for(int i=level[1]-m;i<=level[1];i++)
        res = min(res,dijkstra(i,i+m));
    cout<<res<<endl;
    return 0;
}