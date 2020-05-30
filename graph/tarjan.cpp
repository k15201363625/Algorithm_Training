#include<iostream>
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;
//涉及有向图强连通分量
//无向图 割点 桥 点双连通分量 边双联通分量 
//缩点技巧
/*
[0]SCC定义：对于一个有向图，连通分量：对于分量重任意两点u，v，必然可以从u走到v，且从v走到u。
[1]关键技巧：
有向图通过缩点（将所有连通分量缩成一个点）变成有向无环图（DAG），即拓扑图，便于求最短（或最长）路、递推。时间复杂度为O(n+m)。
（利用拓扑图良好性质）
[2]处理过程：
只能用dfs(树枝边 前向边 后向边(只想祖宗) 横叉边)
2情况更新low：
1：通过子孙节点/本身走到祖先
2：通过横叉边走向祖先
通过dfn low数组得到最终强连通分量等信息
使用stack存储记录节点
[3]Tarjan求强连通分量算法步骤：(SCC)
dfn[u]表示遍历到u的时间戳
low[u]从u开始走，所能遍历到的最小时间戳是什么
u是其所在强连通分量的最高点<==>dfn[u]==low[u]
note:栈中存放的永远是强连通分量中没有搜索完成的点
[4]缩点技巧
有时不需要显示缩点 只需要统计ind
有时缩点需要显示重新建图：这时候要小心边如何处理 可能需要保存重复边
[5]使用tarjan之后进行缩点优势：
因为在得到过程中顺序问题，所以按照强连通分量编号递减顺序可以得到强连通分量的拓扑序
(强连通分量编号顺序与拓扑序逆序)
*/
//难点1：强连通分量图变成完全联通块 点边双联通分量图变成完全图
/*
难点2 : 对于不等式关系问题：

1 差分约束(慢 但是通用)
2 tarjan算法(对边有要求)--边情况特殊时候可以用tarjan+拓扑图最短路代替spfa判断正环最短路 这样稳定On
3 传递闭包/并查集(关系少的时候)
*/
//受欢迎的牛
//tarjan scc+dout统计 不需要显示建图
/*
const int N = 10010,M = 50010;
int n,m;
int h[N],e[M],ne[M],idx;
int dfn[N],low[N],timestamp;
int stk[N],top;
bool instk[N];
int id[N],scc_cnt,sz[N],dout[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void tarjan(int u){
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u,instk[u] = true;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(!dfn[j]){
            tarjan(j);
            low[u] = min(low[u],low[j]);
        }else if(instk[j]) low[u] = min(low[u],low[j]);//??min(low[u],dfn[j])二者都可以
    }
    //强连通分量的起始点
    if(low[u]==dfn[u]){
        ++scc_cnt;
        int y;
        do{
            y = stk[top--];
            instk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt] ++;
        }while(y!=u);
    }
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h),idx = 0;
    while(m--){
        int a,b;
        cin>>a>>b;
        add(a,b);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i);
    //缩点
    for(int i=1;i<=n;i++)
        for(int j=h[i];j!=-1;j=ne[j]){
            int v = e[j];
            int a = id[i],b = id[v];
            if(a!=b) dout[a]++;
        }
    int zeros = 0,res = 0;
    for(int i=1;i<=scc_cnt;i++){
        if(!dout[i]){
            zeros++;
            res += sz[i];
            if(zeros>1){
                res = 0;
                break;
            }
        }
    }
    cout<<res<<endl;
    return 0;
}
*/
//学校网络 将一个图变成一个强连通分量需要最少的边数目==max(|P|,|Q|)
//证明：
/*
按照对称性 假设|p|<|Q| |p|==1 需要|Q|条边
|p|>1 必然可以找到p1,p2对应不同终点q1 q2(否则|Q|==1矛盾)
所以可以链接q1 p2实现|p|-- |q|-- 从而有经过|p|-1条边变成|p|==1 从而一共需要|Q|-(|p|-1)+(|P|-1)
结果为|Q|
综上可以得到结论 edgenums = max(|P|,|Q|)
note:注意特殊判断 如果只有一个起点终点可能出现本身就上强连通分量 此时只需要0 特殊判断(sp)
*/
/*
const int N = 10010,M = 5000010;
int h[N],e[M],ne[M],idx;
int dfn[N],low[N],timestamp;
int stk[N],top;
bool instk[N];
int scc_cnt,id[N];
int din[N],dout[N];
int n,m;
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void tarjan(int u){
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u,instk[u] = true;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(!dfn[j]){
            tarjan(j);
            low[u] = min(low[u],low[j]);
        }else if(instk[j]) low[u] = min(low[u],dfn[j]);
    }
    if(dfn[u]==low[u]){
        int y;
        scc_cnt++;
        do{
            y = stk[top--];
            instk[y] = false;
            id[y] = scc_cnt;
        }while(y!=u);
    }
}
int main(){
    cin>>n;
    memset(h,-1,sizeof h),idx = 0;
    for(int i=1;i<=n;i++){
        int b;
        while(cin>>b,b){
            add(i,b);
        }
    }
    for(int i=1;i<=n;i++) 
        if(!dfn[i])
            tarjan(i);
    int pnum=0,qnum=0;
    for(int i=1;i<=n;i++){
        for(int j=h[i];j!=-1;j=ne[j]){
            int v = e[j];
            int a = id[i],b = id[v]; 
            if(a!=b) din[b]++,dout[a]++; 
        }
    }
    for(int i=1;i<=scc_cnt;i++){
        if(din[i]==0) pnum++;
        if(dout[i]==0) qnum++;
    }
    cout<<pnum<<endl;
    if(scc_cnt==1) cout<<0<<endl;
    else cout<<max(pnum,qnum)<<endl;
    return 0;
}
*/

//最大半连通子图
//定义：一个有向图G=(V,E)称为半连通的(Semi-Connected)，如果满足：任意u,v∈V，满足u→v或v→u，即对于图中任意两点u，v,存在一条u到v的有向路径或者从v到u的有向路径。
//定义2：若G'=(V',E')满足V'?V，E'是E中所有跟V'有关的边，则称G'是G的一个导出子图。
//定义3：若G'是G的导出子图，且G'半连通，则称G'为G的半连通子图。若G'是G所有半连通子图中包含节点数最多的，则称G'是G的最大半连通子图。
//note在这里用到了缩点后拓扑图可以直接dp 并且统计方案数的特性
//由于自动满足拓扑逆序 所以不需要建图(X)
//过程：
/*
1 tarjan 2 缩点 3 拓扑徐逆递推(dp)
设f(i)为表示到i这个点的最长链的长度，g(i)表示到到i这个点的最长链的方案数 
s(i)表示i这个强连通分量中的点数
如果可以从j->i：
1．若f(j)+s(i)>f(i)，则f(I)=f(j)+s(i)，且g(i)=g(j)
2．若f(j)+s(i)==f(i)，则g(i)+=g(j)
note:从拓扑徐角度分析不需要重新拓扑排序 但是需要重新建图 因为重边会导致dp计算方案数目错误 删除重边
*/
/*
#include<unordered_set>
const int N = 1e5+10,M = 2e6+10;//两个图 所以需要2倍边
int h[N],hs[N],e[M],ne[M],idx;
int dfn[N],low[N],timestamp;
int stk[N],top;
bool instk[N];
int scc_cnt,id[N],sz[N];
int din[N],dout[N];
int n,m,mod;
void add(int h[],int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void tarjan(int u){
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u,instk[u] = true;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(!dfn[j]){
            tarjan(j);
            low[u] = min(low[u],low[j]);
        }else if(instk[j]) low[u] = min(low[u],dfn[j]);
    }
    if(dfn[u]==low[u]){
        int y;
        scc_cnt++;
        do{
            y = stk[top--];
            instk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        }while(y!=u);
    }
}
int f[N],g[N];
int main(){
    cin>>n>>m>>mod;
    int a,b;
    memset(h,-1,sizeof h),idx = 0;
    memset(hs,-1,sizeof hs);
    while(m--){
        cin>>a>>b;
        add(h,a,b);
    }
    for(int i=1;i<=n;i++)
        if(!dfn[i]) tarjan(i);
    //缩点
    //为了避免重复使用unordered_set hash记录 pair本身有hash 但是可以实现自己的简单hash函数避免重复
    //u*1e6+v
    unordered_set<long long> record;
    for(int i=1;i<=n;i++)
        for(int j=h[i];j!=-1;j=ne[j]){
            int v = e[j];
            int a = id[i],b = id[v];
            long long hashnum = 1ll*a*1000000 + b;
            if(a!=b && record.count(hashnum)==0){
                add(hs,a,b);
                record.insert(hashnum);
            } 
        }
    //dp过程 已经是拓扑图 按照逆序实现拓扑序
    for(int i=scc_cnt;i>=1;i--){
        if(!f[i])
            f[i] = sz[i],g[i] = 1;
        for(int j=hs[i];j!=-1;j=ne[j]){
            int v = e[j];
            if(f[v]<f[i]+sz[v]){
                f[v] = f[i] + sz[v];
                g[v] = g[i];
            }else if(f[v]==f[i]+sz[v]){
                g[v] = (g[v]+g[i])%mod;
            }
        }
    }
    int maxf=0,sum=0;
    for(int i=1;i<=scc_cnt;i++){
        if(f[i]>maxf){
            maxf = f[i];
            sum = g[i];
        }else if(f[i]==maxf){
            sum = (sum+g[i])%mod;
        }
    }
    cout<<maxf<<endl;
    cout<<sum<<endl;
    return 0;
}
*/
//银河
//和糖果问题类似 
//糖果问题使用差分约束解决 但是复杂度可能爆掉 这时候考虑tarjan解决
/*
对于不等式关系问题：

1 差分约束(慢 但是通用)
2 tarjan算法(对边有要求) 建图过程同差分约束 只是求解最短路过程优化
3 传递闭包/并查集(关系少的时候)
*/
//糖果/银河 
//思路：由于边只有>=0 所以正环代表强连通分量中有边>0 
//      而当有解 没有正环 强连通分量中的点数值都相同 所以原来的全点最短路问题转换成了拓扑图上的最短路 O(n)复杂度
/*
const int N = 100010,M = 300010*2;
int h[N],hs[N],e[M],ne[M],w[M],idx;//需要删除重复边
int dfn[N],low[N],timestamp;
int stk[N],top;
bool instk[N];
int scc_cnt,id[N],sz[N];
int dis[N];
int n,m,mod;
void add(int h[],int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
void tarjan(int u){
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u,instk[u] = true;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(!dfn[j]){
            tarjan(j);
            low[u] = min(low[u],low[j]);
        }else if(instk[j]) low[u] = min(low[u],dfn[j]);
    }
    if(dfn[u]==low[u]){
        int y;
        scc_cnt++;
        do{
            y = stk[top--];
            instk[y] = false;
            id[y] = scc_cnt;
            sz[scc_cnt]++;
        }while(y!=u);
    }
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h);
    memset(hs,-1,sizeof hs);
    //0 为虚拟节点
    for(int i=1;i<=n;i++) add(h,0,i,1);
    while(m--){
        int t,a,b;
        cin>>t>>a>>b;
        if(t==1) add(h,a,b,0),add(h,b,a,0);
        else if(t==2) add(h,a,b,1);
        else if(t==3) add(h,b,a,0);
        else if(t==4) add(h,b,a,1);
        else add(h,a,b,0);
    }
    tarjan(0);
    //缩点 需要判断有没有正边
    bool success = true;
    for(int i=0;i<=n;i++){
        for(int j=h[i];j!=-1;j=ne[j]){
            int v = e[j];
            int a = id[i],b = id[v];
            if(a==b){
                if(w[j]>0){
                    success = false;
                    break;
                }
            }else{
                add(hs,a,b,w[j]);
            }
        }
        if(!success) break;
    }
    if(!success) cout<<-1<<endl;
    else{
        //自动已经有了拓扑顺序 求拓扑图最短路
        //只需要使用dp递推即可
        for(int i=scc_cnt;i>=1;i--){
            for(int j=hs[i];j!=-1;j=ne[j]){
                int v = e[j];
                dis[v] = max(dis[v],dis[i]+w[j]);
            }
        }
        long long res = 0;
        for(int i=1;i<=scc_cnt;i++) 
            res += 1ll*dis[i]*sz[i];
        cout<<res<<endl;
    }
    return 0;
}
*/

