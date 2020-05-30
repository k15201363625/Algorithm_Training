#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<vector>
using namespace std;
//最近公共祖先
//基本求解方法
// 1 向上标记法 on
// 2 倍增求解(note 哨兵) bfs/dfs nlogn先预处理 logn查询
// 3 tarjan 离线求解(向上标记法优化) 所有点分成三类--已经遍历过并且回溯过的 正在搜索得点 未搜索的点
//     需要用到并查集将点快速归类 On算法

//模板题目
/*
const int N = 1e3+10;
int h[N],e[N],ne[N],idx=0;
int q[N];//bfs方防止爆栈
int res[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}

//标记数组
int dep[N],fa[N][16];
void bfs(int rt){
    int hh = 0,tt = -1;
    memset(dep,0x3f,sizeof dep);//同时用标记数组
    dep[0] = 0,dep[rt] = 1;
    q[++tt] = rt;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(dep[j]>dep[t]+1){
                dep[j] = dep[t] + 1;
                q[++tt] = j;
                fa[j][0] = t;
                //由于bfs  可以直接在此时进行fa求解 因为上面的层次已经处理完了
                for(int k=1;k<=15;k++) fa[j][k] = fa[fa[j][k-1]][k-1];
            }
        }
    }
}
int lca(int a,int b){
    if(dep[a] < dep[b]) swap(a,b);
    for(int k=15;k>=0;k--) 
        if(dep[fa[a][k]]>=dep[b])
            a = fa[a][k];
    if(a==b) return a;
    for(int k=15;k>=0;k--)
        if(fa[a][k]!=fa[b][k])
            a = fa[a][k],b = fa[b][k];
    return fa[a][0];
} 
int n;
int main(){
    int T;
    cin>>T;
    for(int i=1;i<=T;i++){
        cin>>n;
        int m;
        int a,b;
        memset(h,-1,sizeof h),idx = 0;
        for(int j=1;j<=n;j++){
            cin>>m;
            while(m--){
                cin>>b;
                add(j,b);
            }
        }
        bfs(1);
        int Q;
        cin>>Q;
        int cnt = 0;
        while(Q--){
            cin>>a>>b;
            res[cnt++] = lca(a,b);
        }
        cout<<"Case "<<i<<":"<<endl;
        for(int j=0;j<cnt;j++)
            cout<<res[j]<<endl;
    }
    return 0;
}
*/

//tarjan算法关键 
/*
状态为2 表示已经遍历完成并且回溯的 对于这些点需要正确设置父节点
状态为1 便是正在进行遍历的点 对于这些点需要设置p[i]=i即还没有完成回溯过程
此时对于状态为1的点 在遍历完子树之后(询问另一段可能在子树上)检查另一端的询问节点
                 对于这些节点 只需要查找祖先直到找到p[i]=i节点即为lca
状态为0 表示节点没有遍历过
*/
/*
const int N = 100010,M = N*2;
typedef pair<int,int> pii;
int h[N],e[M],ne[M],w[M],idx=0;
int res[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
vector<pii> query[N];
int d[N];//统计到根节点距离
int p[N];
int st[N];
int n,m;
void dfs(int u,int fa){
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(j == fa) continue;
        d[j] = d[u] + w[i];
        dfs(j,u);
    }
}
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
void tarjan(int u){
    //dfs过程
    st[u] = 1;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(!st[j]){
            tarjan(j);
            //重点 设置p要在返回之后 
            p[j] = u;
        }
    }
    for(auto qq:query[u]){
        int y = qq.first,id = qq.second;
        if(st[y]==2){//总有一侧可以实现这种状态
            int ans = find(y);
            res[id] = d[u]+d[y]-d[ans]*2;
        }
    }
    st[u] = 2;
}
int main(){
    cin>>n;
    memset(h,-1,sizeof h);
    idx = 0;
    int a,b,c;
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        add(a,b,1),add(b,a,1);
    }
    cin>>m;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        if(a!=b){
            query[a].push_back({b,i});
            query[b].push_back({a,i});
        }else{
            res[i] = 0;
        }
    }
    for(int i=1;i<=n;i++) p[i] = i;//必须有
    dfs(1,-1);
    tarjan(1);
    for(int i=0;i<m;i++) cout<<res[i]<<endl;
    return 0;
}
*/
//联合权值 统计点对的max联合权值 联合权值之和
//关键 暴力会超时n*n 为了避免暴力 采用dp思想 通过前缀统计得到sum max
//      方法2 直接推公式sumres=(sum)^2 - (a^2+b^2+...) maxres = max*次max
//用到乘法结合律
/*
const int N = 200010;
int h[N],e[N*2],ne[N*2],idx;
long long w[N*2];
const int mod = 10007;
long long maxans,sumans;
int n;
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
//或者可以在dfs过程中对于每个店进行计算并且更新全局变量答案即可 线性时间复杂度
void solve(){
    for(int i=1;i<=n;i++){
        //枚举
        long long presum = 0,premax = 0;
        for(int j=h[i];j!=-1;j=ne[j]){
            int v = e[j];
            sumans = (sumans+presum*w[v])%mod;
            maxans = max(premax*w[v],maxans);
            premax = max(premax,w[v]),presum = (presum+w[v])%mod;
        }
    }
    sumans = (sumans*2)%mod;
}
int main(){
    cin>>n;
    memset(h,-1,sizeof h);
    idx = 0;
    for(int i=0;i<n-1;i++){
        int a,b;
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    for(int i=1;i<=n;i++) cin>>w[i];
    solve();
    cout<<maxans<<" "<<sumans<<endl;
    return 0;
}
*/

//重复前面的题目(秘密的奶牛运输) 当时使用dfs n*n复杂度无法通过 这里使用lca
//严格次小生成树问题
//如果使用dfs光是存储都不够 N×N
/*
const int N = 100010,M = 300010,inf = 0x3f3f3f3f;
int n,m;
struct edges{
    int a,b,w;
    bool used;
    bool operator<(const edges &o)const{
        return w<o.w;
    }
}ee[M];
int p[N];
int h[N],e[N*2],ne[N*2],w[N*2],idx;
int dep[N],fa[N][17],d1[N][17],d2[N][17];//分别存储最小次小
int q[N];
//节点太多防止爆栈
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
int find(int x){
    if(p[x] != x) p[x] = find(p[x]);
    return p[x];
}
long long kruskal(){
    long long res = 0;
    for(int i=1;i<=n;i++) p[i] = i;
    sort(ee,ee+m);
    for(int i=0;i<m;i++){
        int a = find(ee[i].a),b = find(ee[i].b);
        if(a!=b){
            p[a] = b;
            res += ee[i].w;
            ee[i].used = true;
        }
    }
    return res;
}
//建树
void build_tree(){
    memset(h,-1,sizeof h);
    idx = 0;
    for(int i=0;i<m;i++){
        if(ee[i].used){
            int a = ee[i].a,b = ee[i].b;
            add(a,b,ee[i].w),add(b,a,ee[i].w);
        }
    }
}
//bfs 只是这是不知要处理fa 还需要处理d1 d2 小心这里的d1 d2需要用4个可能的数值计算
//注意哨兵节点 
void bfs(int rt){
    memset(dep,0x3f,sizeof dep);
    dep[0] = 0,dep[rt] = 1;
    int hh = 0,tt = 0;
    q[0] = rt;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(dep[j]>dep[t]+1){
                dep[j] = dep[t]+1;
                q[++tt] = j;
                fa[j][0] = t;
                d1[j][0] = w[i],d2[j][0] = -inf;
            }
            //处理关键 需要统计的不只是dep 还需要有d1 d2
            //这些信息只需要依赖于dep就可以通过倍增统计得到
            for(int k=1;k<=16;k++){
                int nowfa = fa[j][k-1];
                fa[j][k] = fa[nowfa][k-1];
                int d[4] = {d1[j][k-1],d1[nowfa][k-1],d2[j][k-1],d2[nowfa][k-1]};
                d1[j][k] = d2[j][k] = -inf;
                for(int u=0;u<4;u++){
                    int dis = d[u];
                    if(dis>d1[j][k]) d2[j][k] = d1[j][k],d1[j][k] = dis;
                    else if(dis!=d1[j][k] && dis>d2[j][k]) d2[j][k] = dis;
                }   
            }
        }
    }
}
int lca(int a,int b,int w){//求解lca过程中统计d1 d2
//返回树上w-严格小于w的边 所以需要统计最大次大 避免最大数值与w相同
    //首先统计得到路径上的最大次大数值
    static int tmpd[N*2];//统计路径行的d1 d2信息
    int cnt = 0;
    if(dep[a]<dep[b]) swap(a,b);
    for(int k=16;k>=0;k--){
        if(dep[fa[a][k]]>=dep[b]){
            tmpd[cnt++] = d1[a][k];
            tmpd[cnt++] = d2[a][k];
            a = fa[a][k];
        } 
    }
    if(a!=b){
        for(int k=16;k>=0;k--){
            if(fa[a][k]!=fa[b][k]){
                tmpd[cnt++] = d1[a][k];
                tmpd[cnt++] = d2[a][k];
                tmpd[cnt++] = d1[b][k];
                tmpd[cnt++] = d2[b][k];
                a = fa[a][k];
                b = fa[b][k];
            }
        }
        //最后一轮的需要计算上
        tmpd[cnt++] = d1[a][0];//只有最大
        tmpd[cnt++] = d1[b][0];
    }
    int dis1,dis2;
    dis1 = dis2 = -inf;
    for(int i=0;i<cnt;i++){
        int d = tmpd[i];
        if(d>dis1) dis2 = dis1,dis1 = d;
        else if(d!=dis1 && d>dis2) dis2 = d;
    }
    if(w>dis1) return w-dis1;
    else return w-dis2;//小心可能存在没有次大数值 这时候出现-inf 不会被最终min的结果取到
}

int main(){
    cin>>n>>m;
    int a,b,c;
    for(int i=0;i<m;i++){
        cin>>a>>b>>c;
        ee[i] = {a,b,c,false};
    }
    long long sum = kruskal();
    build_tree();
    bfs(1);
    long long res = 1e18;
    //遍历所有非树边
    for(int i=0;i<m;i++){
        if(ee[i].used) continue;
        int a=ee[i].a,b = ee[i].b;
        res = min(res,sum + lca(a,b,ee[i].w));
    }
    cout<<res<<endl;
    return 0;
}
*/
//poj 3417 Network/暗的连锁
//难题：
//思路：
/*
首先对于每一条加入的边 有x-y路径上所有边覆盖数目++
当某条边被覆盖了0次 则只需要切断一次 共有m2种方案
当某条边被覆盖了1次 则需要切断两次 共有1种方案 
当某条边被覆盖了>1次 则没有方案
关键点：
如何统计每条边覆盖数目 相当于快速对于树上的一个区间进行+1操作 
方案1：树链剖分
方案2：树上差分快速操作
问题：(树上差分操作)
**1** 边修改化作点修改 用边的终点表示边
区间操作 -- 这段区间中的边则用w[x]++ w[y]++ w[lca(x,y)]-2
区间操作结果查询 -- 在线性结构中采用累加 在树形结构中采用遍历 之后累加子树上的结果(回溯完成)
*/
const int N = 100010,M = 2*N;
int n,m;
int h[N],e[M],ne[M],idx;
int dep[N],fa[N][17];
int cov[N];
int q[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void bfs(){
    memset(dep,0x3f,sizeof dep);
    dep[0] = 0,dep[1] = 1;
    int hh=0,tt=0;
    q[0] = 1;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(dep[j]>dep[t]+1){
                dep[j] = dep[t]+1;
                q[++tt] = j;
                fa[j][0] = t;
                for(int k=1;k<=16;k++) fa[j][k] = fa[fa[j][k-1]][k-1];
            }
        }
    }
}
int lca(int a,int b){
    if(dep[a]<dep[b]) swap(a,b);
    for(int k=16;k>=0;k--){
        if(dep[fa[a][k]]>=dep[b])
            a = fa[a][k];
    }
    if(a==b) return a;
    for(int k=16;k>=0;k--){
        if(fa[a][k]!=fa[b][k])
            a =fa[a][k],b = fa[b][k];
    }
    return fa[a][0];
}
int ans = 0;
//关键 统计树上差分的结果 在回溯过程统计
int dfs(int u,int f){
    int ucov = cov[u];
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(j!=f){
            int s = dfs(j,u);//没有重叠子问题 直接搜索就可以
            //更新结果
            if(s==0) ans += m;
            else if(s==1) ans += 1;
            ucov += s;
        }
    }
    return ucov;
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h),idx = 0;
    int a,b,c;
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    bfs();
    for(int i=0;i<m;i++){
        cin>>a>>b;
        int father = lca(a,b);
        //树上差分区间修改
        cov[a]++,cov[b]++,cov[father]-=2;
    }
    //树上差分通过求和一次性统计全部结果
    dfs(1,-1);
    cout<<ans<<endl;
    return 0;
}