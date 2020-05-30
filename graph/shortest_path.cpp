#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#include<iomanip>//格式化输出
using namespace std;
typedef pair<int,int> pii;

//最短路算法
//基础模板
//dijkstra -- 没有负权 朴素n^2 堆优化mlogm(logn) 
//bellman-ford -> spfa (m*n)->km/mn spfa用队列/栈作为优化 可以负权 可以判断负环
//双端队列广搜(值只有01)
//广搜(值只有1/全部相等)
//朴素dijkstra (贪心)
//多源最短路有 floyd(贪心) 多起点时得到每个点距离这些起点最短路--多起始点广搜/添加虚拟源节点dj 
/*
const int N = 1e3+10;
const int M = 1e5+10;

int d[N];
bool st[N];
int g[N][N];
int n,m;
//朴素版通常用邻接矩阵存储版
void dijksra(int rt){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    d[rt] = 0;
    for(int i=1;i<n;i++){
        int x = -1;
        for(int j=1;j<=n;j++)
            if(!st[j] && (x==-1||d[j]<d[x])) x=j;
        st[x] = 1;
        for(int j=1;j<=n;j++)
            d[j] = min(d[j],d[x]+g[x][j]);
    }
}
//堆优化版本
//通常用邻接表存储
//节点可能多次出对入队 只有第一次是有效数据
int h[N],e[N],ne[N],w[N],idx;
void add(int a,int b,int v){
    e[idx] = b,ne[idx] = h[a],w[idx] = v,h[a] = idx++;
}

void dijkstra(int rt){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    d[rt] = 0;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,rt});
    while(pq.size()){
        int t = pq.top().second;
        pq.pop();
        if(st[t]) continue;
        st[t] = true;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+w[i]){
                d[j] = d[t] + w[i];
                pq.push({d[j],j});
            }
        }
    }
}
//bellman-ford 算法
//还是使用三角不等式进行更新 但是这次基于三角不等式 [如果所有边都满足三角不等式<=d数组就是最短路](双向？？)
// 扫描所有边 知道没有更新发生 最多n-1次 
//本质是基于边数目不是边长度 所以不怕负权
struct edge{
    int a,b,v;
}gg[M];
void bellman(int rt){
    memset(d,0x3f,sizeof d);
    d[rt] = 0;
    for(int i=0;i<n-1;i++){
        bool update = false;
        for(int j=0;j<m;j++){
            int u = gg[j].a,v = gg[j].b;
            if(d[v] < d[v],d[u]+gg[j].v)
                d[v] = d[v],d[u]+gg[j].v,update = true;
        }
        if(!update) return; 
    }
}
//spfa 队列优化的bellmanford
//每次能够进行更新的必然是当前已经被更新过的节点连出得边 其余边没有效果
//st用于记录当前节点是否在队列中 节点可以多次入队多次出对 每个节点最多入队n-1次
//需要使用queue(c++内置的循环队列) 或者手写循环队列
void spfa(int rt){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    d[rt] = 0,st[rt] = true;
    queue<int> q;
    q.push(rt);
    while(q.size()){
        int t = q.front();q.pop();
        st[t] = false;
        for(int i=h[t];i=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+w[i]){
                d[j] = d[t] + w[i];
                if(!st[j]) q.push(j),st[j] = true;
            }
        }
    }
}
*/

//模板题 热浪
// const int N = 2510,M = 6200*2+10;
/*
const int N = 1e5+10,M = 4e5+10;

int h[N],e[M],ne[M],w[M],idx;
int d[N],q[N];
bool st[N];
int n,m,S,T;
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
void spfa(){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    int hh=0,tt=1;
    q[0] = S,st[S] = true,d[S]=0;
    while(hh!=tt){//循环队列套路
        int t = q[hh++];
        if(hh==N) hh=0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+w[i]){
                d[j] = d[t]+w[i];
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt=0;
                    st[j] = true;
                }
            }
        }
    }
}
//luogu p4779过不去 只能尝试dij
void dijkstra(int rt){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    d[rt] = 0;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,rt});
    while(pq.size()){
        int t = pq.top().second;
        pq.pop();
        if(st[t]) continue;
        st[t] = true;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+w[i]){
                d[j] = d[t] + w[i];
                pq.push({d[j],j});
            }
        }
    }
}
*/

// int main(){
//     cin>>n>>m>>S;
//     memset(h,-1,sizeof h);
//     for(int i=0;i<m;i++){
//         int a,b,c;
//         cin>>a>>b>>c;
//         add(a,b,c),add(b,a,c);
//     }
//     // spfa();//p4779过不去 只能尝试dj
//     dijkstra(S);
//     for(int i=1;i<=n;i++) cout<<d[i]<<" ";
//     return 0; 
// }
// int main(){
//     cin>>n>>m>>S>>T;
//     memset(h,-1,sizeof h);
//     for(int i=0;i<m;i++){
//         int a,b,c;
//         cin>>a>>b>>c;
//         add(a,b,c),add(b,a,c);
//     }
//     spfa();
//     cout<<d[T]<<endl;
//     return 0;
// }

//信使 数据范围很小 直接用floyd
/*
const int N = 110;
int n,m;
int d[N][N];
int main(){
    cin>>n>>m;
    memset(d,0x3f,sizeof d);
    //d[i][i]更新的时候如果使用floyd不会用到
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        d[a][b]  = d[b][a] = min(d[a][b],c);//可能重边
    }
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
    int res = 0;
    for(int i=1;i<=n;i++)
        if(d[1][i] == 0x3f3f3f3f){
            res = -1;
            break;
        }else{
            res = max(res,d[1][i]);
        }
    cout<<res<<endl;
    return 0;
}
*/
//香甜的黄油 多源汇最短路 
// 由于使用floyd会超时 使用暴力枚举点的spfa/dijkstra
/*
const int N = 810,M = 2910;
int n,p,m;
int id[N];
int h[N],e[M],ne[M],w[M],idx;
int d[N],q[N];
bool st[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
int spfa(int S){
    memset(d,0x3f,sizeof d);
    d[S] = 0;
    int hh = 0,tt = 1;
    q[0] = S,st[S] = true;//每次最后都会清空 所以不需要使用memset
    while(hh!=tt){
        int t = q[hh++];
        if(hh==N) hh = 0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+w[i]){
                d[j] = d[t] + w[i];
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt=0;
                    st[j] = true;
                }
            }
        }
    } 
    int res = 0;
    for(int i=0;i<n;i++){
        int j = id[i];
        if(d[j]==0x3f3f3f3f) return 0x3f3f3f3f;
        res += d[j];
    }
    return res;
}
int main(){
    cin>>n>>p>>m;
    for(int i=0;i<n;i++) cin>>id[i];
    memset(h,-1,sizeof h);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c),add(b,a,c);
    }
    int res = 0x3f3f3f3f;
    for(int i=1;i<=p;i++) res = min(res,spfa(i));
    cout<<res<<endl;
}
*/
//最小花费
// 可以通过取对数运算发现还是求最短路问题 但是可以方便的直接使用乘法下的三角不等式进行计算
// 最短路 最长路 最大最小乘积都可以直接用三角不等式更新 spfa通用dj会有限制(+不能有负数 *不能有<1数字)
// 这里由于每个数字严格保证w[i]<1所以可以使用dj求解最大乘积
/*
const int N = 2010;
int n,m,S,T;
double g[N][N];
double d[N];
bool st[N];
void dijkstra(){
    d[S] = 1;
    for(int i=1;i<=n-1;i++){
        int t = -1;
        for(int j=1;j<=n;j++){
            if(!st[j] && (t==-1 || d[t]<d[j]))
                t = j;
        }
        st[t] = true;
        for(int j=1;j<=n;j++) d[j] = max(d[j],d[t]*g[t][j]);
    }
}
int main(){
    cin>>n>>m;
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        double z = (100.0-c)/100;
        g[a][b] = g[b][a] = max(g[a][b],z);
    }
    cin>>S>>T;
    dijkstra();
    // printf("%.8lf\n",100/d[T]);
    cout<<setprecision(8)<<fixed<<100/d[T]<<endl;
    return 0;
}
*/
//p2384 luogu 最短路 乘积最小
//可能有>1 <1所以用spfa
/*
#include<cmath>
const int N = 1010,M = 1e6+10;
const int mod = 9987;
int n,m;
int id[N];
int h[N],e[M],ne[M],w[M],idx;
int q[N];
// int d[N];
double d[N];
double logw[M];
bool st[N];
int p[N],last[N];//最短路径前驱节点
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,logw[idx] = log10(c),h[a] = idx++;
}
void spfa(){
    for(int i=1;i<=n;i++) d[i] = 5e3;//1000*4
    // d[1] = 1;
    d[1] = 0;
    int hh = 0,tt = 1;
    q[0] = 1,st[1] = true;//每次最后都会清空 所以不需要使用memset
    while(hh!=tt){
        int t = q[hh++];
        if(hh==N) hh = 0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+logw[i]){
                d[j] = d[t]+logw[i];
                p[j] = i,last[j] = t;
                // d[j] = d[t]*w[i]%9987;
                //错误 不能这样 因为不是要取摸下的最小值 而是要最小值取摸
                //所以为了防止越界需要用log
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt=0;
                    st[j] = true;
                }
            }
        }
    } 
    // return d[n];
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        // add(a,b,c);
        add(a,b,c);
    }
    spfa();
    int now = n;
    int res = 1;
    while(now!=1){
        res = res*w[p[now]]%mod;
        now = last[now];
    }
    cout<<res<<endl;
    //直接计算精度不足 只能记录路径处理了
    // double res = spfa();
    // int ans = 1;
    // for(int i=0;i<(int)res/4;i++)
    //     ans = ans*(int)1e4%mod;
    // ans = ans*(int)pow(10,res - (int)res/4*4)%mod;
    return 0;
}
*/
//最优乘车
// 换乘次数最少 并且是单向的 只需要向能到达的连1边 复杂度n*n(一次边数目)*m 总边数
// 由于只有1 可以用bfs得到
// 难点：题目中没告诉一行读入多少数字 需要使用sstream读入技巧
//      getline处理上次残留的换行
/*
#include<sstream>
const int N = 510;
int m,n;
bool g[N][N];
int d[N],stop[N];
int q[N];//普通队列
void bfs(){
    int hh = 0,tt = -1;
    memset(d,0x3f,sizeof d);
    q[++tt] = 1,d[1] = 0;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=1;i<=n;i++)
            if(g[t][i] && d[i]>d[t]+1){//d此时也代表着是偶遍历过 取代了st数组
                d[i]= d[t]+1;
                q[++tt] = i;
            }
    }
}
int main(){
    cin>>m>>n;
    string line;
    getline(cin,line);
    while(m--){
        getline(cin,line);
        //使用字符流不需要自己解析字符串 就能得到输入并且自动获取类型
        stringstream ssin(line);
        int cnt = 0,p;
        while(ssin>>p) stop[cnt++]=p;
        for(int i=0;i<cnt;i++)
            for(int j=i+1;j<cnt;j++)
                g[stop[i]][stop[j]] = true;
    }
    bfs();
    if(d[n]==0x3f3f3f3f) cout<<"NO"<<endl;
    else cout<<d[n]-1<<endl;
    return 0;
}
*/

//昂贵的聘礼
//关键1 虚拟节点 
//关键2 枚举区间 区间限制从而删去部分边
/*
const int N = 110;
int n,m;
int w[N][N],level[N];//稠密图用n^2
int d[N];
bool st[N];
int dijkstra(int down,int up){
    memset(st,0,sizeof st);
    memset(d,0x3f,sizeof d);
    d[0] = 0;
    for(int i=1;i<=n;i++){//n次
        int t = -1;
        for(int j=0;j<=n;j++){//0-n节点
            if(!st[j] && (t==-1||d[t]>d[j]))
                t = j;
        }
        st[t] = true;
        for(int j=1;j<=n;j++){
            if(level[j]>=down && level[j]<=up) d[j] = min(d[j],d[t]+w[t][j]);
        }
    }
    return d[1];
}
int main(){
    cin>>m>>n;
    memset(w,0x3f,sizeof w);
    // for(int i=1;i<=n;i++) w[i][i] = 0;
    for(int i=1;i<=n;i++){
        int price,cnt;
        cin>>price>>level[i]>>cnt;
        w[0][i] = price;
        while(cnt--){
            int id,cost;
            cin>>id>>cost;
            w[id][i] = min(w[id][i],cost);//可能有重边 小心
        }
    }
    int res = 0x3f3f3f3f;
    //枚举区间 获得最小
    for(int i=level[1]-m;i<=level[1];i++) res = min(res,dijkstra(i,i+m));
    cout<<res<<endl;
    return 0;
}
*/
//新年好
// 最短路暴力枚举
//note:如果数组作为参数传入 无法正确计算sizeof 因为会按照指针计算
//dij得到分别的最短路
/*
const int N = 50010,M = 200010;
int q[N],dist[6][N];
int source[6];
int h[N],e[M],ne[M],w[M],idx;
bool st[N];
int n,m;
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}

void dijkstra(int start,int dist[]){
    //sizeof dist错误
    memset(dist,0x3f,4*N);
    memset(st,0,sizeof st);
    dist[start] = 0;
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    pq.push({0,start});
    while(pq.size()){
        int t = pq.top().second;
        pq.pop();
        if(st[t]) continue;
        st[t] = true;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(dist[j]>dist[t]+w[i]){
                dist[j] = dist[t] + w[i];
                pq.push({dist[j],j});
            }
        }
    }
}
//st有另外的作用
int dfs(int u,int dis,int start){//枚举排列数同事得到最终结果
    if(u>5) return dis;
    int res = 0x3f3f3f3f;
    for(int i=1;i<=5;i++)
        if(!st[i]){
            int v = source[i];
            st[i] = true;
            res = min(res,dfs(u+1,dis+dist[start][v],i));
            //千万记得回溯
            st[i] = false;
        }
    return res;
}
int main(){
    cin>>n>>m;
    source[0] = 1;
    for(int i=1;i<=5;i++) cin>>source[i];
    memset(h,-1,sizeof h);
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c),add(b,a,c);
    }
    for(int i=0;i<6;i++) dijkstra(source[i],dist[i]);
    memset(st,0,sizeof st);
    cout<<dfs(1,0,0)<<endl;
    return 0;
}
*/
//通信线路 显然可以采用二分 不同于题目p4568飞行路线(求最小数值 需要用分层图/dp)
// 性质：从1-N 最少经过长度>x的边的数目是否<=k x越大越容易满足
// 判断较容易(check)：将边分类为0 1(<= >) 则可以采用双端队列广搜得到是否可以满足的判定
/*
const int N = 1010;
const int M = 2e4+10;
int h[N],e[M],ne[M],w[M],idx;
int d[N];
bool st[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
int n,m,k;
bool check(int up){
    //双端队列广搜 需要头插元素 数组实现的队列不方便模拟 会越界
    deque<int> q;
    int hh=0,tt=0;
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    d[1] = 0;
    q.push_back(1);
    while(q.size()){
        int t = q.front();
        q.pop_front();
        if(st[t]) continue;
        st[t] = true; 
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            // 错误 一个节点可能多次入队 但是只有在可以更新的时候才入队
            // 但是一个节点第一次出队的时候必然是最小的时候
            // 所以直接用d判断就可以确定是否需要入队
            // if(!st[j]){ 
            //     if(w[i]<=up) d[j] = d[t],q.push_back(j);
            //     else d[j] = d[t]+1,q.push_back(j);
            // }
            int x = w[i]>up;
            if(d[j]>d[t]+x){
                d[j] = d[t]+x;
                if(x) q.push_back(j);
                else q.push_front(j);
            }
        }
    }
    if(d[n]<=k) return true;
    return false;
}
int main(){
    cin>>n>>m>>k;
    memset(h,-1,sizeof h);
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c),add(b,a,c);
    }
    //为了方便判断是否不存在路径 可以扩大边界为1000001 当不存在路径表示为1000001
    //也有可能结果为0 表示没有消耗 
    //合理设置二分边界重要
    int l=0,r=1000001;
    while(l<r){
        int mid = (l+r)>>1;
        if(check(mid)) r = mid;
        else l = mid+1;
    }
    if(l==1000001) cout<<-1<<endl;
    else cout<<l<<endl;
    return 0;
}
*/

//神题 道路与航线 
//由于又有有向边 又有无向边 并且保证有向边不存在环==>有向边构成拓扑图
//由于无法spfa通过 dj不能用 考虑别的排序方式 topsort
//无向边特性：可以构成联通快 所以只需要在联通快缩点后的图上跑topsort即可 dj卡不了 top先行线性复杂度
//不需要真的缩点 只需要分先后记录联通快 并且在topsort处理的时候不单单书ind--操作 而要一边dj一边ind--
/*
const int N = 25010,M = 1e6+10;
int h[N],e[M],ne[M],w[M],idx;
int d[N];
bool st[N];
queue<int> q;
vector<int> block[N];
int bcnt;
int id[N];
int ind[N];

int n,p,r,ss;
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
void dfs(int u,int bid){
    id[u] = bid,block[bid].push_back(u);
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(id[j]) continue;//为了方便判断 id从1开始
        dfs(j,bid);
    }
}
void dijkstra(int t){
    memset(st,0,sizeof st);
    priority_queue<pii,vector<pii>,greater<pii>> pq;
    for(int i=0;i<block[t].size();i++)
        pq.push({d[block[t][i]],block[t][i]});
    while(pq.size()){
        int t = pq.top().second;
        pq.pop();
        if(st[t]) continue;
        st[t] = true;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            //重点 要检查是否需要ind-- 以及入堆操作 但是更新检查是都需要的
            if(id[j]!=id[t] && --ind[id[j]]==0) q.push(id[j]);
            if(d[j]>d[t]+w[i]){
                d[j] = d[t] + w[i];
                if(id[j]==id[t]) pq.push({d[j],j});
            } 
        }
    }

}
void topsort(){
    memset(d,0x3f,sizeof d);
    d[ss] = 0;
    for(int i=1;i<=bcnt;i++)
        if(ind[i]==0) 
            q.push(i);
    while(q.size()){
        int t = q.front();
        q.pop();
        dijkstra(t);//过程中完成q入队 
    }
}
int main(){
    cin>>n>>p>>r>>ss;
    int a,b,c;
    memset(h,-1,sizeof h);
    while(p--){
        cin>>a>>b>>c;
        add(a,b,c),add(b,a,c);
    }
    //求联通快
    for(int i=1;i<=n;i++){
        if(!id[i])
            dfs(i,++bcnt);//为了方便后续判断
    }
    while(r--){
        cin>>a>>b>>c;
        add(a,b,c);
        ind[id[b]] ++;
    }
    topsort();
    for(int i=1;i<=n;i++)
        // if(d[i]==0x3f3f3f3f) cout<<"NO PATH"<<endl;
        if(d[i]>=0x3f3f3f3f/2) cout<<"NO PATH"<<endl;//通常dj不需要判断 spfa也不需要 但是topsort中无法到达的点可能会被负有向边更新d
        else cout<<d[i]<<endl;
    return 0;
}
*/

//最短路--dp关系 dp是拓扑图上最短路 最短路可以借助dp思想得到非拓扑图上问题解决
//关于使用spfa/dij两种理解：
    // 1 理解1：是否有负边权（点权可以转化为边权理解 边权==点权差值） 如果有不能用dj 只能用spfa
    //     (当然可以通过)建立虚拟节点 使得边权重新定义 导致dij也可以运行 比如本题目变成虚拟节点连w单向边 其余为0
    // 2 理解2：spfa中一个点可以被多次更新 而dij中一个点只能被一次更新 所以dij无法满足 除非特殊情况下
    //     而spfa正确性在于bellman中n-1次用三角不等式更新 不依赖于边权 而是依赖于边数 
    //     由于实际问题有解 不存在特殊环 所以可以得到正确结果(n-1次更新足够)
//dp没有后效性质表示没有环 最短路的d会有后效性 
//本题由于可以重复走 所以有后效性 而本题目把买入卖出分段可以变成求解最值问题(最优化) 从而可以利用最短路 特别注意需要有在当前点本身买入/卖出选择
//只需要求一次以1为起点的最短路(使用点权三角不等式更新 不需要使用边权 做差效果相同)
//再同理为了得到多个不同起点到n最长路 只需要反向建图最长路(从n开始)即可
//最后用dmax-dmin即可得到(错误) 本质需要枚举分界点 其实是用max(dmax[k]-dmin[k])得到 需要两次最短路+O(n)枚举比较
//这里由于建新图麻烦 所以使用spfa通用
//note：通常除非被卡 一般用spfa解决dp类似问题
/*
const int N = 1e5+10,M = 1e6+10;
int h[N],hs[N],e[M],ne[M],idx;
int w[N];
bool st[N];
int dmin[N],dmax[N];
int q[N];
int n,m;
//需要用到建立反向图
void add(int h[],int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void spfa(int d[],int h[],int type){
    memset(st,0,sizeof st);
    int hh = 0,tt = 1;
    if(type==1){//最短路
        memset(d,0x3f,4*N);
        d[1] = w[1];
        q[0] = 1;
    }else{
        memset(d,0,sizeof 4*N);
        d[n] = w[n];//点权不等式与边权不等式
        q[0] = n;
    }
    while(hh!=tt){
        int t = q[hh++];
        if(hh==N) hh=0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if((type==1 && d[j]>min(d[t],w[j])) || (type==2 && d[j]<max(d[t],w[j]))){
                if(type==1) d[j] = min(d[t],w[j]);
                else    d[j] = max(d[t],w[j]);
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt = 0;
                    st[j] = true;
                }
                
            }
        }
    }
}
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++) scanf("%d",&w[i]);
    int a,b,c;
    memset(h,-1,sizeof h);
    memset(hs,-1,sizeof hs);
    for(int i=0;i<m;i++){
        scanf("%d%d%d",&a,&b,&c);
        if(c==1){
            add(h,a,b),add(hs,b,a);
        }else{
            add(h,a,b),add(hs,b,a);
            add(hs,a,b),add(hs,b,a);
        }
    }
    spfa(dmin,h,1);
    spfa(dmax,hs,2);
    int res = 0;
    for(int i=1;i<=n;i++)
        res = max(res,dmax[i]-dmin[i]);
    printf("%d\n",res);
    return 0;
}
*/
// 观光
// 维护最短路 次短路 同时统计方案数目 方案数目统计有dp思想
//方案数目统计可以用dj / spfa
//为了求解次短路 如果使用dj 可以拆点 将点考虑成最短+次短 全部放入候选集合进行选择
//             如果使用spfa 只需要在更新的时候判断一下
/*
const int N = 1010, M = 20010;
struct Ver{
    int id,type,dist;//多维护一个类型
    bool operator>(const Ver& o)const {
        return dist > o.dist;//重载>
    }
};
int n, m, S, T;
int h[N], e[M], w[M], ne[M], idx;
int d[N][2], cnt[N][2];
bool st[N][2];
pair<int,int> q[N];
void add(int a, int b, int c)
{
    e[idx] = b,w[idx] = c,ne[idx] = h[a],h[a] = idx ++ ;
}
void dijkstra(){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    memset(cnt,0,sizeof cnt);
    d[S][0] = 0,cnt[S][0] = 1;
    priority_queue<Ver,vector<Ver>,greater<Ver>> pq;
    pq.push({S,0,0});
    //需要分成两类点入堆 并且进行更新
    while(pq.size()){
        Ver t = pq.top();
        pq.pop();
        int vid = t.id,type = t.type,dist = t.dist,count = cnt[vid][type];
        if(st[vid][type]) continue;
        st[vid][type] = true;
        for(int i=h[vid];i!=-1;i=ne[i]){
            int j = e[i];
            //考虑最短此短更新 由于加入了最短此短于pq中 所以不会遗漏情况
            //保证是严格次短路
            if(d[j][0]>dist+w[i]){
                d[j][1] = d[j][0],cnt[j][1] = cnt[j][0];
                pq.push({j,1,d[j][1]});
                d[j][0] = dist + w[i],cnt[j][0] = count;
                pq.push({j,0,d[j][0]});
            }else if(d[j][0]==dist+w[i]){
                cnt[j][0] += count;
            }else if(d[j][1]>dist+w[i]){
                d[j][1] = dist+w[i],cnt[j][1] = count;
                pq.push({j,1,d[j][1]});
            }else if(d[j][1] == dist+w[i]){
                cnt[j][1] += count;
            }
        }
    }
}
//无法通过??
//无论最短路 次短路都是通过最多n-1条边更新得到 
//一边求解一边统计 但是也需要存储次短最短两种 如果实现更新就要尝试加入队列 
void add_queue(int j,int type,int&tt){//只在需要的时候才加入 否则只更新结果
    if(!st[j][type]){
        q[tt++] = {j,type};
        if(tt==N) tt=0;
        st[j][type] = true;
    }
}
void spfa(){
    memset(d,0x3f,sizeof d);
    memset(st,0,sizeof st);
    memset(cnt,0,sizeof cnt);
    d[S][0] = 0,cnt[S][0] = 1;
    int hh = 0,tt = 1;
    q[0] = {S,0},st[S][0] = true;//每次最后都会清空 所以不需要使用memset
    while(hh!=tt){
        pair<int,int> now = q[hh++];
        if(hh==N) hh = 0;
        int type = now.second,t = now.first,count = cnt[t][type],dist = d[t][type];
        st[t][type] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j][0]>dist+w[i]){
                d[j][1] = d[j][0],cnt[j][1] = cnt[j][0];
                d[j][0] = dist + w[i],cnt[j][0] = count;
                add_queue(j,0,tt);
                add_queue(j,1,tt);
            }else if(d[j][0]==dist+w[i]){
                cnt[j][0] += count;
            }else if(d[j][1]>dist+w[i]){
                d[j][1] = dist+w[i],cnt[j][1] = count;
                add_queue(j,1,tt);
            }else if(d[j][1] == dist+w[i]){
                cnt[j][1] += count;
            }
        }
    } 
}
int main(){
    int cases;
    int a,b,c;
    cin>>cases;
    while(cases--){
        memset(h,-1,sizeof h);
        idx = 0;//不然会可能超过存储范围
        cin>>n>>m;
        for(int i=0;i<m;i++){
            cin>>a>>b>>c;
            add(a,b,c);
        }
        cin>>S>>T;
        //确实存在错误统计问题
        spfa();
        for(int i=1;i<=T;i++) cout<<cnt[i][0]<<" "<<cnt[i][1]<<endl;
        cout<<"----------------"<<endl;
        dijkstra();
        for(int i=1;i<=T;i++) cout<<cnt[i][0]<<" "<<cnt[i][1]<<endl;
        int res = cnt[T][0];
        if(d[T][1]==(1+d[T][0])) res += cnt[T][1];
        cout<<res<<endl;
    }
    return 0;
}
*/
//求方案数
//思路
    //先求出全局最小值是多少
    //分别求出每个子集中等于全局最小值的元素个数

//最短路树（拓扑图）上保证不存在边权为0的环，否则答案的方案数则为正无穷。
//本题用BFS或Dijkstra做没有问题，但是不能用spfa
//note:超级重点 观光一题错误原因 --使用bfs dij可以保证天然满足最短路树拓扑序列 所以用dfs球的方案书正确
//     但是使用spfa即便没有负边权 由于还可以再次更新(不满足最短路树拓扑序)出现dp后效性 比如更新了某个节点cnt 会将下一个节点cnt变成old+new多次累加 错误

//总结求方案数目：
    //如果可以bfs dij则ok 天然满足 计算时候更新即可
    //如果有负权 必须用spfa处理（先建树 在统计）：
        //求方案数时如果有负权边，则先用spfa求一遍最短路，再循环遍历每一条边，
        //若该边满足三角不等式，则加入最短路树中，最后将最短路树建好，再由拓扑序求最短路树上的方案数。
//note:次短路统计问题：1 为了完整性需要两种节点(最短此短都统计) spfa dij都可以
//      但是如果要统计方案数目 必须先用spfa得到最短路次短路两棵树 之后通过拓扑序dp计算

//最短路计数 使用bfs即可
/*
const int N = 100010, M = 400010, mod = 100003;
int n, m;
int h[N], e[M], ne[M], idx;
int d[N], cnt[N];
int q[N];

void add(int a, int b)
{
    e[idx] = b, ne[idx] = h[a], h[a] = idx ++ ;
}
void bfs(){
    memset(d,0x3f,sizeof d);//同时充当st 不需要dij单独使用st 每个节点只会出入一次
    d[1] = 0,cnt[1] = 1;
    int hh=0,tt = 0;
    q[0] = 1;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+1){
                d[j] = d[t] + 1;
                cnt[j] = cnt[t];
                q[++tt] = j;
            }else if(d[j] == d[t]+1){
                cnt[j] = (cnt[j]+cnt[t])%mod;
            }
        }
    }
}
int main()
{
    cin>>n>>m;
    memset(h, -1, sizeof h);
    while (m -- )
    {
        int a, b;
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    bfs();
    for(int i=1;i<=n;i++) cout<<cnt[i]<<endl;
    return 0;
}
*/
//简单多源点寻找最短路问题 
//  1 可以采用反向建图从终点得到结果(暴力一次min)
//  2 可以建立虚拟节点连向每一条边 转化为单源点最短路
/*
const int N = 1010, M = 20010, INF = 0x3f3f3f3f;
int n, m, T;
int h[N], e[M], w[M], ne[M], idx;
int dist[N], q[N];
bool st[N];
void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}
void spfa()
{
    int scnt;
    scanf("%d", &scnt);
    memset(dist, 0x3f, sizeof dist);

    int hh = 0, tt = 0;
    while (scnt -- )//建边过程省略 直接插入到开始的队列中就可以 
    {
        int u;
        scanf("%d", &u);
        dist[u] = 0;
        q[tt ++ ] = u;
        st[u] = true;
    }
    while (hh != tt)
    {
        int t = q[hh ++ ];
        if (hh == N) hh = 0;
        st[t] = false;
        for (int i = h[t]; ~i; i = ne[i])
        {
            int j = e[i];
            if (dist[j] > dist[t] + w[i])
            {
                dist[j] = dist[t] + w[i];
                if (!st[j])
                {
                    q[tt ++ ] = j;
                    if (tt == N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
}
int main()
{
    while (scanf("%d%d%d", &n, &m, &T) != -1)
    {
        memset(h, -1, sizeof h);
        idx = 0;
        while (m -- )
        {
            int a, b, c;
            scanf("%d%d%d", &a, &b, &c);
            add(a, b, c);
        }
        spfa();
        if (dist[T] == INF) dist[T] = -1;
        printf("%d\n", dist[T]);
    }
    return 0;
}
*/

//孤岛营救问题//拯救大兵瑞恩
// 很多题目需要拆点 即变成分层图 ---有key影响 需要拆成2^k个点 表示钥匙状态
// 对于分层图通常优先考虑dp方式
// 但是本题显然出现了循环依赖 后效性
// 但是这道题并不能按照DP的方式来写，因为一般能够用DP方式写的题目都需要保证在计算某个状态之前，所有能够更新它的状态都已经被更新了，即其状态与状态之间满足拓扑序。但是这道题某些点之间是可以相互到达的，因此存在环。所以还是要用最短路的方式来写。
//状态计算：
/*
(x,y)这里有一些钥匙，那么可以直接将所有钥匙拿起：
    建立权值为0的边
向上下左右四个方向走。
（1）没有门和墙
（2）有门，且有匹配的钥匙，之后走到了(a,b)：
    建立权值为1的边
由于只有0 1 可以使用双端队列bfs
保证复杂度：100*1000线性实现 乍看可以用搜索 但是状态导致暴力搜索超时
*/
//边数目计算 只需要得到基本的连接关系边 9*10*2*2=360 + 0边有1000*100最多
//为了避免重复加边 需要采用set记录墙门信息
//x y 信息压缩为一维
/*
#include<set>
const int N = 11,M = 370;
const int P = 1024+10;
int n,m,k,p;
int h[N*N],e[M],ne[M],w[M],idx;
int g[N][N];
int key[N*N];//钥匙状态
int d[N*N][P];
bool st[N*N][P];
set<pii> edges;
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
void build_graph(){
    int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1};
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            for(int k=0;k<4;k++){
                int x=i+dx[k],y=j+dy[k];
                if(!x || x>n || !y || y>m) continue;
                int a = g[i][j],b = g[x][y];
                if(edges.count({a,b})==0)
                    add(a,b,0);
            }
}

int bfs(){
    //双端队列广搜
    memset(d,0x3f,sizeof d);
    d[1][0] = 0;
    deque<pii> q;
    q.push_back({1,0});
    while(q.size()){
        pii t = q.front();
        q.pop_front();
        //双端队列广搜 只有第一次才需要计算并且拓展
        if(st[t.first][t.second]) continue;
        st[t.first][t.second] = true;
        if(t.first == n*m) return d[t.first][t.second];//只要第一次到达  就可以返回 不许需要最后对比
        //对于不同的边动态判断并且扩展
        //钥匙边
        if(key[t.first]){
            int state = t.second | key[t.first];
            if(d[t.first][state]>d[t.first][t.second]){
                d[t.first][state] = d[t.first][t.second];
                q.push_back({t.first,state});
            }
        }
        //普通边/门边--需要看有没有钥匙
        for(int i=h[t.first];i!=-1;i=ne[i]){
            int j = e[i];
            if(w[i] && !(t.second>>(w[i]-1)&1)) continue;
            if(d[j][t.second]>d[t.first][t.second]+1){
                d[j][t.second] = d[t.first][t.second]+1;
                q.push_back({j,t.second});
            }
        }
    }
    return -1;
}
int main(){
    cin>>n>>m>>p>>k;
    //通过g得到对应的一维编号
    for(int i=1,t=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            g[i][j] = t++;
    memset(h,-1,sizeof h);
    int x1,y1,x2,y2,type;
    while(k--){
        cin>>x1>>y1>>x2>>y2>>type;
        int a = g[x1][y1],b = g[x2][y2];
        edges.insert({a,b}),edges.insert({b,a});
        if(type) add(a,b,type),add(b,a,type);//特殊边 bfs中是0/1乣需要特殊判断
    }
    build_graph();
    int s,x,y,c;
    cin>>s;
    while(s--){
        cin>>x>>y>>c;
        key[g[x][y]] |= 1<<(c-1);
    }
    cout<<bfs()<<endl;
    return 0;
}
*/
//floyd 
//多源多汇最短路
//传递闭包（得到连通性）--有时可以用并查集、差分约束解决
//找最小环(每个环可以看成是两条边(k,a),(k,b)与d[a,b]组成 d[a,b]不经过k)
//恰好经过k条边的最短路(使用dp 看似与floyd类似 但是实际是基于倍增 只是代码类似)
//note:floyd bellmen-ford spfa 基于dp
//     dijkstra基于贪心
//floyd d[k][i][j] = d[k-1][i][k] + d[k-1][k][j] 关键能否省掉一个维度
//      每次更新需要用到d[k-1][i][k] d[k-1][k][j] 而发现d[k][i][k] d[k][k][j]会始终保持为d[k-1][i][k] d[k-1][k][j]所以可以正确更新
//      （要求初始化d[i][i]为0/>0的数字）

//牛的旅行 (需要求出每个点上的maxd)
/*
#include<cmath>
typedef pair<double,double> pdd;
#define x first 
#define y second
const int N = 160;
const double inf = 1e15;//n*n*1e5
char g[N][N];
pdd q[N];
double d[N][N];
double maxd[N];
int n;
double getdis(pdd a,pdd b){
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return sqrt(dx*dx + dy*dy);
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>q[i].x>>q[i].y;
    for(int i=0;i<n;i++) cin>>g[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(i==j) d[i][j] = 0;
            else if(g[i][j]=='1') d[i][j] = getdis(q[i],q[j]);
            else d[i][j] = inf;  
    for(int k=0;k<n;k++)  
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                d[i][j] = min(d[i][j],d[i][k]+d[k][j]);
    double res1 = 0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++)    
            if(d[i][j]<inf) maxd[i] = max(maxd[i],d[i][j]);
        res1 = max(res1,maxd[i]);
    }
    double res = inf;
    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(d[i][j]==inf)//可能出现double精度不够 可以使用inf/2 inf=1e20计算更保险
                res = min(res,maxd[i]+maxd[j]+getdis(q[i],q[j]));
    cout<<fixed<<setprecision(6)<<max(res,res1)<<endl;
    return 0;
}
*/

//排序
//传递闭包 26*26*26*m(表示枚举每次加入关系后的传递闭包)
//若使用增量算法变成了m*26*26
//因为只有一种关系 所以可以用
/*
const int N = 26;
bool g[N][N],d[N][N];
bool st[N];
int n,m;

void floyd(){
    memcpy(d,g,sizeof d);
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                d[i][j] |= d[i][k] && d[k][j];//传递闭包模板 小心
}
//为了提升速度 不需要每次都做一次传递闭包 尝试使用增量算法
// 每次加入一个关系之后 a<b 只可能改变对应的一系列关系 d[x][a] d[b][y] d[x][y]
// 所以每次只需要改变一系列关系就可以
void incre_trans(int a,int b){
    //初始化不要忘记 不能在里面
    d[a][b] = 1;
    for(int x=0;x<n;x++){
        if(d[x][a]) d[x][b] = 1;
        if(d[b][x]) d[a][x] = 1;
        for(int y=0;y<n;y++)
            if(d[x][a] && d[b][y]) d[x][y] = 1;
    }
}
int check(){
    //如果有的d[i][i] = 0 / d[i][j]=d[j][i]=1矛盾
    for(int i=0;i<n;i++)
        if(d[i][i]) return 2;
    for(int i=0;i<n;i++)
        for(int j=0;j<i;j++)
            if(d[i][j]==d[j][i] && d[i][j]==0)
                return 0;
    return 1;
}


char getmin(){
    for(int i=0;i<n;i++){
        if(!st[i]){
            bool flag = false;
            for(int j=0;j<n;j++)
                if(!st[j] && d[j][i]){
                    flag = true;
                    break;
                }
            if(flag == false){
                st[i] = true;
                return 'A'+i;
            }
        }
    }
}
int main(){
    while(scanf("%d%d",&n,&m),n||m){
        // memset(g,0,sizeof g);
        memset(d,0,sizeof d);
        int judge = 0,times = 1;
        for(int i=1;i<=m;i++){
            char relation[4];
            scanf("%s",relation);
            int a = relation[0] - 'A', b = relation[2] - 'A';
            if(!judge){
                // g[a][b] = 1;
                // floyd();
                incre_trans(a,b);//只需要增量计算就可以
                judge = check();
                times = i;
            }
        }
        if(!judge) cout<<"Sorted sequence cannot be determined."<<endl;
        else if (judge == 2) printf("Inconsistency found after %d relations.\n",times);
        else{
            memset(st,0,sizeof st);
            printf("Sorted sequence determined after %d relations: ",times);
            for (int i = 0; i < n; i ++ ) printf("%c",getmin());
            puts(".");
        }
    }
}
*/
//观光之旅
//求解最小环问题
//n*n*n复杂度求最小环
//每个环 为了保重不重不漏 需要有从小到大枚举每个k 当前环是0-k中节点构成的 这样不会遗漏不会重复
//按顺序是指按照环上顺序 从谁开始不重要
/*
const int N = 110;
const int M = 10010;
const int inf=0x3f3f3f3f;
int g[N][N],d[N][N],sep[N][N];
int circle[N],cnt=0,nowlen = inf;
int n,m;
void getpath(int a,int b){
    //边缘点不需要分(只有两边的点不会加入 所以在外面单独处理)
    if(!sep[a][b]) return;//怎么判断取决于pos怎么更新
    int k = sep[a][b];
    getpath(a,k);
    circle[cnt++] = k;
    getpath(k,b);
}
void getmincircle(){    
    memcpy(d,g,sizeof d);
    for(int k=1;k<=n;k++){
        for(int i=1;i<k;i++)
            for(int j=i+1;j<k;j++){//避免重复枚举向连边 小心取值范围
                //先检查 后更新
                if(g[k][i]<inf && g[k][j]<inf && d[i][j]<inf)
                    if(nowlen > g[k][i]+g[k][j]+d[i][j]){
                        nowlen = g[k][i]+g[k][j]+d[i][j];
                        // cnt = 0;
                        // circle[cnt++] = k;
                        // circle[cnt++] = i;
                        // getpath(i,j);
                        // circle[cnt++] = j;
                    }
            }
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                //更新距离以及sep
                //对于单点的不会更新 pos[i][i]=0
                //对于一条边相连的 不会更新 pos[i][j]=0
                //对于不相连接的pos[i][j]=0 
                if(d[i][j]>d[i][k]+d[k][j]){
                    d[i][j] = d[i][k] + d[k][j];
                    sep[i][j] = k;
                }
    }   
}
int main(){
    cin>>n>>m;
    int u,v,l;
    memset(g,0x3f,sizeof g);
    for(int i=1;i<=n;i++) g[i][i] = 0;
    while(m--){
        cin>>u>>v>>l;
        g[u][v] = g[v][u] = min(l,g[u][v]);
    }
    getmincircle();
    if(nowlen==inf) cout<<"No solution."<<endl;
    else{
        // for(int i=0;i<cnt;i++) cout<<circle[i]<<" ";
        // cout<<endl;
        cout<<nowlen<<endl;
    } 
    return 0;
}
*/
//牛站 cow relays
//只经过k跳边的最短路 要求可以环路 即便负环也有结果
/*
d[k][i][j]表示经过kk跳边最短路 
可以得到d[a+b][i][j] = min(d[a][i][k] + d[b][k][j])按照中点进行划分 
而a b需要枚举所有可能 这样复杂度变成了kk*n*n*(n*kk)复杂度太高了
观察d[a][i][j]有满足结合律 a=1+2+4+... =(1+2)+4=1+(2+4)不满足交换律但是满足结合律
由于想到了快速幂实现技巧中关键点 满足结合律 不需要交换律 
所以这道题看似不是乘法 但是可以将操作看成乘法(传递操作) 使用快速幂拆分计算
时间复杂度改为 logkk*n*n*n 有规律组合使用结合律省掉了kk 同时拆分kk变成了logkk
dp优化者利用到两点--1减少状态 2减少转移消耗
*/
//note:本题目可以采用离散化 使得复杂度可以接受
//为了节省空间 可以讲d[i][j][k]表示2^k路径中的k消去 只需要一边快速米计算一边乘上去就可以了
//写法类比快速米 使用了二进制拆分
//其实可以看成是快速加法 只是这个加法操作如果看成*就是快速幂 同时这个操作时利用当前已有信息更新更长路径信息 
/*
#include<map>
const int N = 210;
int k,n,m,ss,ee;
int g[N][N];
int res[N][N];
void mul(int c[][N],int a[][N],int b[][N]){//二维数组第二个参数必须确定
    //此时不需要枚举组合(a+b=x+y)只需要将给出的组合进行更新检查
    static int tmp[N][N];
    memset(tmp,0x3f,sizeof tmp);
    //转移复杂度变成了n 只需要枚举k 但是需要计算当前的n*n个状态
    for(int k=1;k<=n;k++)//不同于floyd的k表示状态中的一个维度 这里的k仅仅表示枚举转移
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                tmp[i][j] = min(tmp[i][j],a[i][k]+b[k][j]);
    memcpy(c,tmp,sizeof tmp);
}
void qmi(){
    //所谓乘法 就是在当前res基础上用另一个距离矩阵更新一次
    //得到了拆分之后的结果 2+4 即用4的矩阵更新2变成6的矩阵
    //需要有表示1的(2^0)的矩阵 
    //res初始表示0步矩阵
    memset(res,0x3f,sizeof res);
    for(int i=1;i<=n;i++) res[i][i] = 0;
    while(k){
        if(k&1) mul(res,res,g);
        k>>=1;
        mul(g,g,g);
    }
}
int main(){
    cin>>k>>m>>ss>>ee;
    //需要离散化点
    map<int,int> ids;
    ids[ss] = ++n;
    ids[ee] = ++n;
    ss = ids[ss],ee = ids[ee];
    int a,b,c;
    memset(g,0x3f,sizeof g);//表示经过一条边的 所以g[i][i]初始化为inf
    while(m--){
        cin>>c>>a>>b;
        if(!ids.count(a)) ids[a] = ++n;
        if(!ids.count(b)) ids[b] = ++n;
        a = ids[a],b = ids[b];
        g[a][b] = g[b][a] = min(g[a][b],c); 
    }
    qmi();
    cout<<res[ss][ee]<<endl;
    return 0;
}
*/
