#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
#include<cstdio>
#include<map>
using namespace std;
//最小生成树
//无向边(否则是朱刘算法最小树形图)
//prim 算法 n^2（可以看成贪心类似dij）优化后mlogm(mlogn) 但是优化后算法不如kruskal
//kruskal 贪心 mlogm+km 直接存边 特征：从中途开始仍然具有正确性 从中途结束仍然具有正确性
//证明：采用替换法反正 如果当时不选 则加上这条边 形成环 之后去掉那一条更长的边 一定会使得生成树更小(这个证明是用于以上两种算法)
//最短网络
//稠密图最小生成树 使用prim
/*
const int N = 110;
int g[N][N];
int n;
bool st[N];
int d[N];
int prim(){
    int res = 0;
    memset(st,0,sizeof st);
    memset(d,0x3f,sizeof d);
    d[1] = 0;
    for(int i=0;i<n;i++){//需要第一次加入1节点本身
        int t = -1;
        for(int j=1;j<=n;j++){
            if(!st[j] && (t==-1||d[t]>d[j]))
                t = j;
        }
        res += d[t],st[t] = true;
        for(int j=1;j<=n;j++)
            d[j] = min(d[j],g[t][j]);
    }
    return res;
}

int main(){
    cin>>n;
    memset(g,0x3f,sizeof g);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>g[i][j];
    cout<<prim()<<endl;
    return 0;
}
*/

//局域网 
//求解最小生成森林
//如果用prim需要多加判断出连通性 并且多次prim 
//使用kruskal尽管没形成完整生成树 但是由于prim性质保证正确性
//可以用Prim算法时一定可以用Kruskal算法，但用Kruskal算法时不一定可以用Prim算法（例如本题）
/*
const int N = 110;
const int M = 410;
struct edges{
    int a,b,c;
    bool operator<(const edges& o) const{
        return c<o.c;
    }
}e[M];
int p[N];
int n,m;
int find(int x){
    if(p[x]==x) return x;
    return p[x] = find(p[x]);
}
int main(){
    cin>>n>>m;
    int res = 0;
    int a,b,c;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        e[i] = {a,b,c};
        res += c; 
    }
    sort(e,e+m);
    for(int i=1;i<=n;i++) p[i] = i;
    for(int i=0;i<m;i++){
        int pa = find(e[i].a),pb = find(e[i].b);
        if(pa==pb)
            continue;
        else{
            p[pa] = pb;
            res -= e[i].c;
        }
    }
    cout<<res<<endl;
    return 0;
}
*/
//繁忙的都市
//最小生成树在本题中意义变为 求解最大边权值最小的生成树
//prim未必满足 但是kruskal天然满足
/*
const int N = 310;
const int M = 8010;
struct edges{
    int a,b,c;
    bool operator<(const edges& o)const{
        return c<o.c;
    }
}e[M];
int p[N];
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
int n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) p[i] = i;
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        e[i] = {a,b,c};
    }
    sort(e,e+m);
    int res = 0;
    for(int i=0;i<m;i++){
        int pa = find(e[i].a),pb = find(e[i].b);
        if(pa==pb) continue;
        p[pa] = p[pb];
        res = e[i].c;
    }
    cout<<n-1<<" "<<res<<endl;
    return 0;
}
*/
//联络员 
//Kruskal算法：可以只实现前一半，也可以在已经有边的前提下继续做后一半
//关键强大的地方就在这里
//必须选的边直接加入并查集 非必须选的边按照kruskal跑一边 可以证明仍然正确
/*
const int N = 2010;
const int M = 10010;
struct edges{
    int a,b,c;
    bool operator<(const edges& o)const{
        return c<o.c;
    }
}e[M];
int p[N];
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
int n,m;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) p[i] = i;
    int cnt = 0;
    int res = 0;
    for(int i=0;i<m;i++){
        int type,a,b,c;
        cin>>type>>a>>b>>c;
        if(type==1){
            res += c;
            int pa = find(a),pb = find(b);
            if(pa!=pb) p[pa] = pb;
        }else{
            e[cnt++] = {a,b,c};
        }
    }
    sort(e,e+cnt);
    for(int i=0;i<m;i++){
        int pa = find(e[i].a),pb = find(e[i].b);
        if(pa==pb) continue;
        p[pa] = p[pb];
        res += e[i].c;
    }
    cout<<res<<endl;
    return 0;
}
*/

//连接格点 
//看似是最小生成树 实际上可以优化掉 不需要排序 klogk->k
//普通测评器上容易冲突而变量名字：prev next y1 hash
//技巧：1 二维变一位 2 先纵边后横边 省掉排序
/*
const int N = 1010;
const int M = N*N*2;
struct edges{
    int a,b,c;
    bool operator<(const edges& o)const{
        return c<o.c;
    }
}e[M];
int p[N*N];
int ids[N][N];
int cnt = 0;
int n,m;

int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
void getedges(){
    int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1},w[4] = {1,2,1,2};
    for(int z=0;z<2;z++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=m;j++)
                for(int u=0;u<4;u++){
                    if(u%2==z){
                        int x = i+dx[u],y = j+dy[u];
                        if(x<0 || x>n || y<0 || y>m) continue;
                        int a = ids[i][j],b = ids[x][y];
                        if(a<b) e[cnt++] = {a,b,w[u]};//小心重复
                    }
                }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n*m;i++) p[i] = i;
    int t = 1;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            ids[i][j] = t++;
    
    int res = 0;
    int a,b,c,d;
    while(cin>>a>>b>>c>>d){
        int x = ids[a][b],y = ids[c][d];
        p[find(x)] = find(y);
    }
    getedges();
    for(int i=0;i<cnt;i++){
        int pa = find(e[i].a),pb = find(e[i].b);
        if(pa==pb) continue;
        p[pa] = p[pb];
        res += e[i].c;
    }
    cout<<res<<endl;
    return 0;
}
*/
//最小生成树扩展应用
// 基础定理：任意一棵最小生成树一定可以包含无向图中权值最小的边
// 拓展：给定一张无向图G=(V,E),n=|V|,m=|E|。从E中选出k<n-1条边构成G的加一个生成森林。若再从剩余的m-k条边中选n-1-k条添加到生成森林中，使其成为G的生成树，并且选出的边的权值之和最小，则该生成树一定包含这m-k条边中连接生成森林的两个不连通节点的权值最小的边。
// 证明：采用替换法可以证明

//新的开始
//建立虚拟源节点 之后最小生成树
/*
const int N = 310;
int n;
int g[N][N];
int d[N];
bool st[N];

int prim(){
    memset(st,0,sizeof st);
    memset(d,0x3f,sizeof d);
    d[0] = 0;
    int res = 0;
    for(int i=0;i<n+1;i++){//几个点就需要几次
        int t = -1;
        for(int j=0;j<=n;j++)//0为虚拟源节点
            if(!st[j] && (t==-1 || d[t]>d[j]))
                t = j;
        st[t] = true;
        res+=d[t];
        //更新检查不能忘记0
        for(int j=0;j<=n;j++) d[j] = min(d[j],g[t][j]);
    }
    return res;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++){
        cin>>g[0][i];
        g[i][0] = g[0][i];
    }
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            cin>>g[i][j];
    cout<<prim()<<endl;
    return 0;
}
*/

//北极通讯网络
//直接看上去：使用二分 每次判断当前<d的边能否得到联通快数目<k的结果 选出最大的d即可
//由于d增大 联通快数目n减小 所以由于单调性 满足二分要求
//而必然选择d为边长 所以可以先排序 每次加入一条边 判断连通性 
//发现：如果使用dfs在新加入边之后需要重新计算 所以是n*logm+mlogm(排序后二分)复杂度 
//     如果使用并查集 只需要每次增量计算 不需要n判断 所以mlogm+m*1(不能二分了 必须依次加入 保证增量计算正确性)
//不依赖于增量可以二分但是判断慢---依赖于增量不能二分但是判断快
// note:依赖于增量的并查集算法本质就是kruskal过程
/*
#include<cmath>
#include<iomanip>
#define x first
#define y second
typedef pair<int,int> pii;
const int N = 510;
const int M = N*N/2;
pii q[M];
struct edges{
    int a,b;
    double w;
    bool operator <(const edges&o)const{
        return w<o.w;
    }
}e[M];
int n,k,m=0;

double getdis(pii a,pii b){
    int dx = a.x-b.x,dy = a.y-b.y;
    return sqrt(dx*dx+dy*dy);
}
int p[N];
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
int main(){
    // cin>>n>>k;
    int T;
    cin>>T;
    while(T--){
        cin>>k>>n;
        for(int i=1;i<n;i++) p[i] = i;
        for(int i=0;i<n;i++) cin>>q[i].x>>q[i].y;
        for(int i=0;i<n;i++)
            for(int j=0;j<i;j++)//只需要单向
                e[m++] = {i,j,getdis(q[i],q[j])};//稠密图
        sort(e,e+m);
        double res = 0;
        int cnt = n;
        for(int i=0;i<m;i++){
            if(cnt<=k) break;//放在最开始判断 便与处理特殊情况k>=n
            int pa = find(e[i].a),pb = find(e[i].b);
            if(pa!=pb){
                p[pa] = pb;
                cnt --;
                res = e[i].w;
            }
        }
        cout<<fixed<<setprecision(2)<<res<<endl;
    }
    return 0;
}
*/

//走廊泼水节 
//在保证最小生成树唯一情况下 添加边 使得变成完全图
//关键：对于两点间如果要添加必须保证d>w+1 (w表示路径上最大距离)
//朴素做法：On预处理得到任意两点间路径上最大距离 之后n*n点对枚举 复杂度n*n 有些太慢
//借助kruskal过程思考：对于两堆点(两个联通快)每次选中这条边必然是最大的 这时增加了sz[i]*sz[j]-1条边
//                  所以在变成一个完整的生成树过程中 必然统计到了所有的结果
//                  这样做的复杂度达到了nlogn(只有n-1条边 顺着插入就可以了)
/*
const int N = 6010;
struct edges{
    int a,b;
    int w;
    bool operator <(const edges&o)const{
        return w<o.w;
    }
}e[N];
int n;
int p[N],sz[N];//维护了大小的并查集
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
int main(){
    int T;
    int a,b,c;
    cin>>T;
    while(T--){
        cin>>n;
        for(int i=1;i<=n;i++) p[i]=i,sz[i]=1;
        for(int i=0;i<n-1;i++){
            cin>>a>>b>>c;
            e[i] = {a,b,c};
        }
        sort(e,e+n-1);
        int res = 0;
        for(int i=0;i<n-1;i++){
            int pa = find(e[i].a),pb = find(e[i].b);
            if(pa!=pb){
                //先更新后合并
                res += (sz[pb]*sz[pa]-1)*(e[i].w+1);
                sz[pb] += sz[pa];
                p[pa] = pb;
            }
        }
        cout<<res<<endl;
    }

    return 0;
}
*/
//秘密的牛奶运输
//严格的次小生成树问题
//次小生成树有以下定理：（存在只有一条边不同的此小生成树）
// 定理：对于一张无向图，如果存在最小生成树和（严格）次小生成树，
//      那么对于任何一棵最小生成树，都存在一棵（严格）次小生成树，使得这两棵树只有一条边不同。
//由此得到方案：
//1 枚举树边 删掉每条树边尝试 mlogm+mn
//2 枚举非树边 目标找到sum+w[i]-goalw最小=>goalw表示最大的从i-j路径上的边
// 概念：
// 设T为图G的一棵生成树，对于非树边a和树边b，插入边a，并删除边b的操作记为(+a,-b)。
// 如果T+a-b之后，仍然是一棵生成树，称(+a,-b)是T的一个可行交换。
// 称由T进行一次可行变换所得到的新的生成树集合为T的邻集。
// 定理：次小生成树一定在最小生成树邻集中
//note次小生成树一定在邻集中 == 任意最小生成树存在一个次小生成树只有一条边不一样
//方法：
// 对于非严格次小生成树：只需要n*n采用dfs预处理得到没对点之间的最大w
//                   或者用lca nlogn预处理之后每次logn查询最大w
// 对于严格次小生成树： 必须处理出最大w 以及严次大w
//复杂度分析：n*n+m+mlogm(dfs预处理) n*logn+mlogn+mlogm(lca预处理)
/*
const int N = 510, M = 10010;
// const int N = 100010;
// const int M = 300010;大数据下使用d存储都过不去 时间复杂度上也过不去
int n, m;
struct Edge
{
    int a,b,w;
    bool f;
    bool operator< (const Edge &t) const{
        return w < t.w;
    }
}edge[M];

int p[N];
int d1[N][N], d2[N][N];//存储最小
int h[N], e[N*2], w[N*2],ne[N*2], idx;

void add(int a, int b, int c)
{
    e[idx] = b, w[idx] = c, ne[idx] = h[a], h[a] = idx ++ ;
}

int find(int x)
{
    if (p[x] != x) p[x] = find(p[x]);
    return p[x];
}
//dfs方法 维护最大数值 严格最大数值
//只需要在dfs过程传递下就可以了
void dfs(int u,int fa,int mv1,int mv2,int d1[],int d2[]){
    d1[u] = mv1,d2[u] = mv2;
    for(int i=h[u];i!=-1;i=ne[i]){
        //坑 千万小心 因为要搜索多个分支 所以v1 v2数值需要保存住 不能改变掉
        int j = e[i];
        int v1 = mv1,v2 = mv2;
        if(j==fa) continue;
        if(w[i]>v1) v2 = v1,v1 = w[i];
        else if(w[i]<v1 && w[i]>v2) v2 = w[i];//严格次小 小心
        dfs(j,u,v1,v2,d1,d2);
    }
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h);
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        edge[i] = {a,b,c,false};
    }
    sort(edge,edge+m);
    for(int i=1;i<=n;i++) p[i] = i;
    long long sum = 0;
    for(int i=0;i<m;i++){
        int a = edge[i].a,b = edge[i].b;
        int pa = find(a),pb = find(b);
        if(pa!=pb){
            p[pa] = pb;
            sum += edge[i].w;
            add(a,b,edge[i].w),add(b,a,edge[i].w);
            edge[i].f = true;
        }
    }
    //预处理
    for(int i=1;i<=n;i++) dfs(i,-1,-1e9,-1e9,d1[i],d2[i]);
    //枚举得到结果
    long long res = 1e18;
    for(int i=0;i<m;i++){
        if(edge[i].f) continue;
        int a = edge[i].a,b = edge[i].b,w = edge[i].w;
        long long tmp;
        if(w>d1[a][b]) tmp = sum + w - d1[a][b];
        else if(w>d2[a][b]) tmp = sum + w - d2[a][b];
        res = min(res,tmp);
    }
    cout<<res<<endl;
    return 0;
}
*/
