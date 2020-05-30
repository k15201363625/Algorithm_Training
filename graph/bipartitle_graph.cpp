#include<algorithm>
#include<cstdio>
#include<iostream>
#include<cstring>
using namespace std;
//二分图
/*
1 染色定理/二分图判定/二分图充分必要等价条件
一个图不存在奇数个点构成的环(奇数环) == 一个图可以二染色 == 一个图是二分图
证明：只需要证明1==2 而2->3 3->1 的证 证明过程中需要用到大量反证法

2 二分图最大匹配求解算法
采用建立虚拟源节点 求解最大流 (复杂度太高)
匈牙利算法 O(n*(m+n)) 关键：不存在增广路时候充分必要已经最大匹配(可用于证明贪心覆盖问题正确性)

3 二分图其他匹配问题
最优匹配(最大边权匹配)
多重匹配(一个点可以匹配另一个集合中多个点)
note:以上需要用网络流解决

4 二分图最大匹配与一些问题的等价转换以及数学关系
[1]max match == 最小点覆盖(使用最少的点覆盖掉所有的边 无向图)
证明：采用构造法实现双向证明(很难)
[2]n-max match == 最大独立集 == 补图中的最大团
证明：最大独立集即最大的没有边的点集合==使用最少的点消去所有的边 补图即边变为无无变为有
[3]对于有向无环图(DAG)有 最小路径点覆盖(路径无重复) == pointnum-maxmatch
证明：将有向图中每个点拆成i i'其中i表示i作为出点 i'表示i作为入点 每条路径对应一个匹配
    而每一个路径终点就是一个未匹配点 所以未匹配的点数目为结果
有向图转换为了无向图上的匹配问题
[4]最小路径(可重复)点覆盖 == 传递闭包后得到的DAG下的最小路径(不可重复)点覆盖
证明：只需要证明而这对应关系 每一个1的方案可以转换成2 每一个2可以转换成1 关键在于重复点跳过 新增边还原
[5]拓展：有向图最大独立点集(任意两点之间没有边相连)
点集点数 == 最小路径可重复点覆盖数目
证明：首先路径可以重叠 之后得到最小路径覆盖k 由于最多只能有k个点符合条件否则在一条路径上 ans<=k
之后对于路径的终点E集合以及E可以到达的集合step(E) 如果二者不相交 则为结果ans==k 
        二者相交 则将E中被到达的点ei沿着路径回退 直到step(E)中没有ei 而不可能出现回退到头还没找到的情况(此时该路径可以被评到另一条路径上 k--)矛盾
综上使用反证法证明了k是可行方案 ans>=k 综上ans==k

5 二分图重点细节：
[1]只是针对无向图
[2]实现中只需要用到一个集合指向拎另一个集合的有向边
[3]需要用到match数组
[4]二分图在解决上面的路径覆盖问题中不需要真的拆点
[5]二分图最大匹配每次dfs之前需要充值st记录 因为每次增光后结果可能改变 在一次增光过程中探索过的点不需要再次探索
[6]使用邻接矩阵存储的二分图对于解决需要传递闭包的上面的问题4以及小规模的点数目比较好用
[7]判断需要用双向边 最大匹配只需要存储单向边

6 二分图难点：
[1]问题转换为二分图以及二分图相关问题(4个 判断+4)
[2]证明所需要求解的就是二分图上的某个性质(需要用到反证法/构造法)
[3]棋盘问题：
    数据规模小10用状态压缩dp
    数据规模大100 1000用二分图解决可能可以
[4]二分图解决棋盘问题套路：
    一个合法的方案是一个匹配
    棋盘上的点通常可以通过(i+j)%2实现分成两类点 有的题用i%2区分
    每个合法的关系是一对点之间的一条匹配边
    综上：最优方案变成了最大匹配 此时用邻接矩阵二分图最大匹配解决

坑：
做题经验 (有关最大二分匹配问题)
对于时间复杂度稍高的 
[1]可以用优化遍历顺序解决
在棋盘问题中由于匈牙利算法如果找到可以增广的会优先退出 为了实现这个剪枝 从下往上搜好(dx>0) 因为下方暂时没有放置过
[2]可以用建立源汇节点跑一次maxflow dinic
dinic复杂度会比匈牙利好一些
*/

//1 关押罪犯
//可以用二分+判断能否形成二分图(去掉<=m的边之后)
/*
const int N = 20010,M = 2e5+10;//判断需要用双向边 最大匹配只需要存储单向边
int n,m;
int h[N],e[M],ne[M],w[M],idx;
int color[N];//0 1 2
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
bool dfs(int u,int c,int up){//当前点 当前颜色 当前权值上限
    color[u] = c;
    for(int i=h[u];i!=-1;i=ne[i]){
        if(w[i]<=up) continue;
        int j = e[i];
        if(color[j]==c) return false;
        else if(!color[j])
            if(!dfs(j,3-c,up)) 
                return false;
    }
    return true;
}
bool check(int mid){
    //每次check必须重置color**
    memset(color,0,sizeof color);
    for(int i=1;i<=n;i++){
        if(!color[i]){
            if(!dfs(i,1,mid)) return false;
        }
    }
    return true;
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h),idx = 0;
    while(m--){
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c),add(b,a,c);
    }
    int l = 0,r = 1e9;//二分 最差1e9 最好情况0 二分注意边界
    while(l<r){
        int mid = (l+r)>>1;
        if(check(mid)) r = mid;
        else l = mid + 1;
    }
    cout<<l<<endl;
    return 0;
}
*/

//棋盘覆盖 由于点数目较多 使用二分图解决
//点二分之后变成求最大匹配
/*
const int N = 110;
bool g[N][N],st[N][N];
pair<int,int> match[N][N];
int n,k;
int dx[4] = {-1,0,1,0},dy[4] = {0,1,0,-1};
bool find(int x,int y){//dfs过程
    for(int i=0;i<4;i++){
        int nx = x+dx[i],ny = y+dy[i];
        if(nx<1 || nx>n || ny<1 || ny>n) continue;
        if(g[nx][ny] || st[nx][ny]) continue;
        st[nx][ny] = true;//注意何时设置
        pair<int,int>& t = match[nx][ny];
        if(t.first==0 || find(t.first,t.second)){
            t = {x,y};//回溯过程改变连接关系
            return true;
        }
    }
    return false;
}
int main(){
    cin>>n>>k;
    while(k--){
        int x,y;
        cin>>x>>y;
        g[x][y] = true;
    }
    int cnt = 0;
    memset(match,0,sizeof match);//pair也可以使用memset设置
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
        //只需要从一侧点考虑即可
            if(!g[i][j] && (i+j)%2){
                memset(st,0,sizeof st);//必须有
                if(find(i,j)) 
                    cnt++;
            }
    cout<<cnt<<endl;
    return 0;
}
*/

// 长脖子鹿放置 骑士放置(n==200会被卡掉 需要用最大流dinic求解)
//棋盘问题 这里变成了可以攻击到的点连边 合法的放置就是最大独立集
//发现当采用奇偶分类后连的边符合二分图性质 k;
//复杂度 200*200*8*200
/*
typedef pair<int,int> pii;
const int N = 210;
int g[N][N];
int st[N][N];
pii match[N][N];
int n,m,k;
int dx[8] = {-2,-1,1,2,2,1,-1,-2},dy[8] = {1,2,2,1,-1,-2,-2,-1};
bool find(int x,int y){
    for(int i=0;i<8;i++){
        int a = x+dx[i],b = y+dy[i];
        if(a<1 || a>n || b<1 || b>m) continue;
        if(st[a][b] || g[a][b]) continue;
        st[a][b] = true;
        pii &t = match[a][b];
        if(t.first==0 || find(t.first,t.second)){
            t = {x,y};
            return true;
        }
    }
    return false;
}
int main(){
    // cin>>n>>k;
    // m = n;
    cin>>n;
    m = n,k=0;
    string str;
    for(int i=1;i<=n;i++){
        cin>>str;
        for(int j=1;j<=n;j++){
            g[i][j] = str[j-1]-'0';
            if(g[i][j]) k++;
        }
    }
    // for(int i=0;i<k;i++){
    //     int a,b;
    //     cin>>a>>b;
    //     g[a][b] = true;
    // }
    int res = 0;//最大独立集等于n*m-k-res
    memset(match,0,sizeof match);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if((i+j)%2 && !g[i][j]){
                memset(st,0,sizeof st);
                if(find(i,j)) res++;
            }
    cout<<n*m-k-res<<endl;
}
*/
//长颈鹿问题采用建图方式改变 需要按照行/列奇偶性质建图 因为所能调到的只有同奇偶性的
/*
typedef pair<int,int> pii;
const int N = 210;
bool g[N][N];
int st[N][N];
pii match[N][N];
int n,m,k;
//搜索顺序优化问题
//**** 因为dfs过程如果找到直接可以返回 但是上面的可能已经放好了 所以优先从下面的找
// 考虑匈牙利算法的实现过程，若当前点找到的匹配边是暂时没有匹配冲突，那么就可以直接匹配结束dfs，否则将进行复杂的增广。因此，
// 从(x+3,x-1)开始(即下偏左)从下往上遍历可以减少冲突的概率，(上方的可匹配点被之前的点匹配的可能性较高。)，可以将复杂度降为O(能过)。
// int dx[8] = {-3,-1,1,3,3,1,-1,-3},dy[8] = {1,3,3,1,-1,-3,-3,-1};
int dx[8] = {1,3,3,1,-1,-3,-3,-1},dy[8] = {-3,-1,1,3,3,1,-1,-3};
//如果采用直接建图 可能会快一点
bool find(int x,int y){
    for(int i=0;i<8;i++){
        int a = x+dx[i],b = y+dy[i];
        if(a<1 || a>n || b<1 || b>m) continue;
        if(st[a][b] || g[a][b]) continue;
        st[a][b] = true;
        pii &t = match[a][b];
        if(t.first==0 || find(t.first,t.second)){
            t = {x,y};
            return true;
        }
    }
    return false;
}
int main(){
    cin>>n>>m>>k;
    int kk = 0;
    for(int i=0;i<k;i++){
        int a,b;
        cin>>a>>b;
        if(!g[a][b]) kk++;//可能会有重复点
        g[a][b] = true;
    }
    int res = 0;//最大独立集等于n*m-k-res
    memset(match,0,sizeof match);
    for(int i=1;i<=n;i+=2)//奇偶
        for(int j=1;j<=m;j++)
            if(!g[i][j]){
                memset(st,0,sizeof st);
                if(find(i,j)) res++;
            }
    cout<<n*m-kk-res<<endl;
}
*/

//机器任务(调度)问题
//二分图最小点覆盖问题
/*
#include<unordered_set>
const int N = 210,M = 1010;//只需要单向边
int n,m,k;
int h[N],e[M],ne[M],idx;//TLE很多时候不是因为慢 是因为空间访问越界 数值覆盖
int match[N];
bool st[N];
unordered_set<int> edges[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
bool find(int x){
    for(int i=h[x];i!=-1;i=ne[i]){
        int j = e[i];
        if(!st[j]){
            st[j] = true;
            if(match[j]==0 || find(match[j])){
                match[j] = x;
                return true;
            }
        }
    }
    return false;
}
int main(){
    while(cin>>n){
        if(n==0) break;
        cin>>m>>k;
        memset(h,-1,sizeof h),idx = 0;
        for(int i=1;i<=n-1;i++) edges[i].clear();
        while(k--){
            int a,b,c;
            cin>>c>>a>>b;
            if(!a || !b) continue;//对于已经是0不需要 在最开始就可以解决
            if(edges[a].count(b)>0) continue; 
            add(a,b);//可能有重边
            edges[a].insert(b);
        }
        int res = 0;
        memset(match,0,sizeof match);//小心 可以是0 0出发的边忽略了
        for(int i=1;i<=n-1;i++){
            if(h[i]==-1) continue;
            memset(st,0,sizeof st);
            if(find(i))
                res++;
        }
        cout<<res<<endl;
    }
    return 0;
}
*/

//在有向图中选出最大独立点集
//由上面得到只需要求解有向图最小路径可重复点覆盖结果
//不需要真的拆点 只需要有向边即可 图只需要用原来的有向图信息即可
//需要进行一次闭包传递 才能得到可重复最小路径点覆盖的结果
const int N = 210;//使用临界觉着呢方便进行闭包传递 使用临劫镖还需要记录每个点可以到的点集合
int match[N];
int n,m;
bool st[N];
bool g[N][N];//闭包传递之后结果也在这里
void transfer(){
    for(int k=1;k<=n;k++)
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                g[i][j] |= g[i][k]&g[k][j];
}
bool find(int x){
    for(int i=1;i<=n;i++){
        if(g[x][i] && !st[i]){//在传递之后的新图上进行
            st[i] = true;
            int y = match[i];
            if(y==0 || find(y)){
                match[i] = x;
                return true;
            }
        }
    }
    return false;
}
int main(){
    cin>>n>>m;
    while(m--){
        int a,b;
        cin>>a>>b;
        g[a][b] = true;
    }
    int res = 0;
    memset(match,0,sizeof match);
    transfer();
    for(int i=1;i<=n;i++){
        memset(st,0,sizeof st);
        if(find(i)) res++;
    }
    cout<<n-res<<endl;
    return 0;
}
//相同问题 单数需要构造出上述求得的方案 ** 难点
//？