#include<iostream>
#include<cstring>
#include<algorithm>
#include<iomanip>
#include<cmath>
using namespace std;
//最小生成树问题
const int N = 510,M = 250010;
int p[N];
struct Edge{
    int a,b,w;
    bool operator<(const Edge &o)const{
        return w<o.w;
    }
}es[M];
int x[N],y[N];
int idx = 0;
int n;
void init(){
    idx = 0;
    for(int i=1;i<=n;i++) p[i] = i;
}
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}

int main(){
    int T,s;
    cin>>T;
    while(T--){
        cin>>s>>n;
        init();
        for(int i=1;i<=n;i++){
            cin>>x[i]>>y[i];
            for(int j=1;j<i;j++)
                es[idx++] = {i,j,(x[i]-x[j])*(x[i]-x[j])+(y[i]-y[j])*(y[i]-y[j])};
        }
        sort(es,es+idx);
        int res = 0,count = 0;
        for(int i=0;i<idx;i++){
            int pa = find(es[i].a),pb = find(es[i].b);
            if(pa!=pb){
                count ++;
                p[pb] = pa;
                if(count==(n-s-1+1)){
                    res = es[i].w;
                    break;
                }
            }
        }
        cout<<fixed<<setprecision(2)<<sqrt(res)<<endl;
    }
    return 0;
}