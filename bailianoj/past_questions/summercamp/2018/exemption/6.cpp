#include<iostream>
#include<cstring>
#include<algorithm>
#include<unordered_map>
using namespace std;
//判断是否存在负环算法 可以用spfa 接近m(由于可以多次更新 更容易趋近nm 不同于最短路spfa 而且使用stack作为存储可能更快找到环) 
//可以用floyd 查看f[i][i] O(n^3)
typedef unordered_map<string,int> msi;
const int N = 40,M = 2000;
msi mmap;
int n,m;
int h[N],e[M],ne[M],idx = 0;
double w[M];
int cnt[N];//表示不算起点 需要经过多少个点到达目标点 容斥原理
double d[N];

void add(int a,int b,double v){
    e[idx] = b,ne[idx] = h[a],w[idx] = v,h[a] = idx++;
}
void init(){
    idx = 0;
    memset(h,-1,sizeof h);
    memset(cnt,0,sizeof cnt);
    memset(d,0,sizeof d);
}
//循环队列
int q[N];
bool st[N];
bool spfa(){
    int hh = 0,tt = 0;
    // q[++tt] = 1; 此时可以把全部点加入 保证找到所有连通块中结果
    //无需初始化 d但是需要预先设置d不为0
    for(int i=1;i<=n;i++) q[tt++] = i,d[i] = 1,st[i] = true;//需要初始化d
    while(hh!=tt){
        int t = q[hh++];
        if(hh==N) hh = 0; 
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]<d[t]*w[i]){
                d[j] = d[t]*w[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j]>=n) return true;
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false; 
}
int main(){
    string str,str2;
    double w;
    int T = 0;
    while(cin>>n,n){
        for(int i=1;i<=n;i++) cin>>str,mmap[str] = i;
        cin>>m;
        init();
        for(int i=0;i<m;i++){
            cin>>str>>w>>str2;
            add(mmap[str],mmap[str2],w);
            // add(mmap[str2],mmap[str],1/w); 只允许单向兑换
        }
        cout<<"Case "<<++T<<": ";
        if(spfa()) cout<<"Yes"<<endl;
        else cout<<"No"<<endl;
    }
    
    return 0;
}