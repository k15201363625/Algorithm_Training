#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
/*
拓扑排序问题
DAG==拓扑图 五环有向图 任意一个点的前驱节点有限 所以可以借助队列实现topsort
应用广泛：便于线性求解最短路 可以在上面dp 使用tarjan求得的强连通分量缩点后逆序满足拓扑徐
        在最短路问题中 如果想要使用dp统计方案 需要满足最短路树是拓扑结构 即不能出现循环后效性更新(拓扑图才能dp)
拓展：
字典序输出结果问题：
要求字典序输出 所以采用领结军阵更方便 如果采用邻接表比较麻烦（x）
需要先排序 之后再加边（x）
其次需要对于度为0的节点按照顺序插入队列才行 这太难实现 所以需要每次采用优先队列实现
字典序；两个注意：优先队列（v）

差分约束求最长路问题：
1)边权没有限制 spfa(Onm)
2)边权非负 （可能有0环 缩点之后topsort）tarjan(O(n+m)) 
3)边权>0 (必然没有环 有解情况下必然可以topsort) O(n+m)

最简单判断环方法 使用topsort结果
return tt == n-1;
*/

/*
const int N = 110,M = N*N/2;
int n;
int h[N],e[M],ne[M],idx;
int q[N];
int din[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
//要求字典序输出 所以采用领结军阵更方便 如果采用邻接表比较麻烦（x）
//需要先排序 之后再加边（x）
//其次需要对于度为0的节点按照顺序插入队列才行 这太难实现 所以需要每次采用优先队列实现
//字典序；两个注意：优先队列（v）
void topsort(){//普通版本
    int hh = 0,tt = -1;
    for(int i=1;i<=n;i++)
        if(!din[i]) q[++tt] = i;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(--din[j]==0)
                q[++tt] = j;
        }
    }
}
int res[N],id = 0;
void sorted_topsort(){//变成nlog复杂度
    id = 0;
    priority_queue<int,vector<int>,greater<int>> pq;
    for(int i=1;i<=n;i++ )
        if(!din[i]) pq.push(i);
    while(pq.size()){
        int t = pq.top();
        //需要存储结果
        res[id++] = t;
        pq.pop();
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(--din[j]==0) 
                pq.push(j);
        }
    }

}
int tmp[N];
int main(){
    while(cin>>n && n){
        memset(h,-1,sizeof h),idx=0;
        memset(din,0,sizeof din);
        for(int i=1;i<=n;i++){
            int son;
            int idx = 0;
            while(cin>>son,son){
                add(i,son);
                // tmp[id++] = son;
                din[son]++;
            }
            // sort(tmp,tmp+id);
            //逆序插入边 在邻接表中变成顺序
            // for(int j=id-1;j>=0;j--) add(i,tmp[j]);
        }
        // topsort();
        //输出不需要单独存储 只需要按照队列中元素顺序输出即可(优于使用stlqueue)
        // for(int i=0;i<n;i++) cout<<q[i]<<" ";

        sorted_topsort();
        //顺序输出需要借助额外存储
        for(int i=0;i<id;i++) cout<<res[i]<<" ";
        cout<<endl;
    }
    return 0;
}
*/
//奖金
//类似差分约束问题 给出一系列不等关系 求解最小值
//但是nm范围太大 考虑别的作法
//方法：topsort优化
//note：topsort有事可以解决差分约束问题
//note:**有解情况下直接topsort求得差分约束中的最长路**
//转换为差分约束问题中：边权为1>0
/*
const int N = 10010,M = 20010;
int n,m;
int h[N],e[M],ne[M],idx;
int q[N];
int din[N];
int dist[N];//最长距离 topsort求最长路 先行复杂度
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
bool topsort(){
    int hh=0,tt=-1;
    for(int i=1;i<=n;i++)
        if(!din[i]) 
            q[++tt]=i;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(--din[j]==0)
                q[++tt] = j;
        }
    }
    //最简单判断环方法 使用topsort结果
    return tt == n-1;
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h);
    while(m--){
        int a,b;
        cin>>a>>b;
        add(b,a);
        din[a] ++;
    }
    if(!topsort()) cout<<"Poor Xed"<<endl;
    else{
        for(int i=1;i<=n;i++) dist[i] = 100;
        //拓扑图上dp即可
        for(int i=0;i<n;i++){
            int j = q[i];
            for(int k=h[j];k!=-1;k=ne[k]){
                //最长路对应最小数值
                dist[e[k]] = max(dist[e[k]],dist[j]+1);//边权为1
            }
        }
        int res = 0;
        for(int i=1;i<=n;i++) res += dist[i];
        cout<<res<<endl;
    }
}
*/
//可达性统计
//快速得到每个点所可以到达的点的数量(DAG)上面
//很容易想到dp 但是会有重复 需要合并集合 这时候变成了n*n 
//为了优化 如果使用bool数组需要遍历 任然是n*n
//所以想到用类似int的压缩 但是这里状态数目太多了 采用bitset实现优化(bitset内部可以讲合并操作/32)
/*
#include<bitset>//小数目状态压缩使用int/long long大数目状态压缩统计合并使用bitset<N>
const int N = 30010,M = 30010;
int n,m;
int h[N],e[M],ne[M],idx;
int q[N];
int din[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
bitset<N> f[N];
void topsort(){
    int hh=0,tt=-1;
    for(int i=1;i<=n;i++)
        if(din[i]==0) q[++tt] = i;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(--din[j]==0)
                q[++tt] = j;
        }
    }
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h);
    while(m--){
        int a,b;
        cin>>a>>b;
        add(a,b);
        din[b]++;
    }
    topsort();
    for(int i=n-1;i>=0;i--){
        //拓扑逆序
        int j = q[i];
        //使用位表示快速合并 而不是使用归并合并/使用bool暴力合并
        f[j][j] = 1;
        for(int k=h[j];k!=-1;k=ne[k]){
            f[j] |= f[e[k]];//合并操作
        }
    }
    //统计操作
    for(int i=1;i<=n;i++) cout<<f[i].count()<<endl;
    return 0;
}
*/

//车站分级
//差分约束问题很明显 并且是边长度是1
//但是由于题目中每个给出的信息会有n*n跳边 总边数目n*n*n太大 所以需要优化
//集合与集合之间两两暴力连边 n*n 但是通过虚拟中间节点实现2*n连边 但是引入了0 1边
//  对于0边看似不满足直接使用topsort  但是题目保证有解=>无环 可以使用topsort
//原来的1边拆成了0->ver->1边 
//小心：点数目变数目计算开空间
//具体细节使用topsort上的dp得到最长路即为最小数值（即为最少的级别 级别从1开始）
//2*1000点数 1000*1000=1e6
const int N = 2010,M = 1e6+10;
int n,m;
int h[N],e[M],ne[M],w[M],idx;
int q[N];
int din[N];
int dist[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
    din[b] ++;
}
void topsort(){
    int hh=0,tt=-1;
    for(int i=1;i<=n+m;i++)
        if(din[i]==0) q[++tt] = i;
    while(hh<=tt){
        int t = q[hh++];
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(--din[j]==0)
                q[++tt] = j;
        }
    }
}
bool st[N];//车站标记
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h);
    for(int i=1;i<=m;i++){
        memset(st,0,sizeof st);
        int cnt;
        int stop,start=n,end=1;
        cin>>cnt;
        while(cnt--){
            cin>>stop;
            start = min(start,stop),end = max(end,stop);
            st[stop] = true;
        }
        int ver = n+i;//实现错位虚拟节点****
        for(int j=start;j<=end;j++){
            if(!st[j]) add(j,ver,0);
            else add(ver,j,1);
        }
    }
    topsort();
    for(int i=1;i<=n;i++) dist[i] = 1;
    //dp
    for(int i=0;i<n+m;i++){//一共n+m点
        int j = q[i];
        for(int k=h[j];k!=-1;k=ne[k]){
            dist[e[k]] = max(dist[e[k]],dist[j]+w[k]);
        }
    }
    int res = 0;
    //由于从1开始分配 所以最少的级别数目就是最长路(最小数值)中的最大数值
    for(int i=1;i<=n;i++) res = max(res,dist[i]);
    cout<<res<<endl;
    return 0;
}
