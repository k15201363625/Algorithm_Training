#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
//tarjan2 无向图双联通分量(重联通分量)
/*
e-DCC 边双联通分量 极大地不包含桥的的连通块
v-DCC 点双连通分量 极大地不包含割点的连通块
桥：删去桥原图不连通
e-DCC性质：无论删掉哪条边 仍然联通，任意两点间存在两条不相交路径
割点：删去割点原图不连通 
v-DCC性质：每一个割点至少属于两个v-DCC
note：二者无之间关系 两个割点之间未必是桥 桥的两个端点未必是割点
     一个点双连通分量未必是一个边双联通分量 反之也是

如何找到桥：
dfn(x) < low(y) x->y为桥
割点：
dfn(x) <= low(y) 如果x不是根节点 则x是割点 否则x需要至少有两个子节点满足以上条件
如何求解e-DCC
m1：删掉所有桥 
m2：（错误：弹栈 直到x停止 不弹出x）(正确：当满足low[u]==dfn[u]的时候开始弹栈 需要弹出u)
如何求解v-DCC
m1:枚举割点
m2:弹栈 注意保留x割点 但是在保存结果中单独加上x(不同于其他 他需要在遍历完一个子节点之后就弹栈操作)

note:无向图中不存在横叉边 所以不需要instk判断
*/

//冗余路径
//对应与有向图中问题 目标 将无向连通图至少添加几条边变成边双联通分量
//方法：缩点 之后变成一棵树 结果是ceil(cnt/2) = floor((cnt+1)/2) cnt表示叶子节点数目
/*
const int N = 5010,M = 20010;
int n,m;
int h[N],e[M],ne[M],idx;
int dfn[N],low[N],timestamp;
int stk[N],top;
int dcc_cnt,id[N];
bool is_bridge[M];
int deg[N];
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void tarjan(int u,int from){
    //这里不能统计指向fa的边
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;//不需要instk判断
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(!dfn[j]){
            tarjan(j,i);
            low[u] = min(low[u],low[j]);
            if(low[j]>dfn[u]){
                is_bridge[i] = is_bridge[i^1] = true;
            }
        }else if(i!=(from^1)){
            low[u] = min(low[u],dfn[j]);
        }
    }
    if(dfn[u]==low[u]){
        ++dcc_cnt;
        int y;
        do{
            y = stk[top--];
            id[y] = dcc_cnt;
        }while(y!=u);
    }
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h);
    while(m--){
        int a,b;
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    tarjan(1,-1);//从-1作为入边
    //统计度
    for(int i=0;i<idx;i++){
        if(is_bridge[i])
            deg[id[e[i]]]++;
    }
    int cnt = 0;
    for(int i=1;i<=dcc_cnt;i++)
        if(deg[i]==1)
            cnt++;
    cout<<(cnt+1)/2<<endl;//只有一个边双联通分量的时候也计算在内
    return 0;
}
*/

//电力 删除一个点之后最多的连通块数目 
//方案：割点问题 求点双联通分量
//多组数据记得dfn low更新
/*
const int N = 10010,M = 30010;
int n,m;
int h[N],e[M],ne[M],idx;
int dfn[N],low[N],timestamp;
int stk[N],top;
int root;//不能少 
int res = 0;
//本题不需要真的求解存储点双联通分量 只需要统计数目即可 而且也不是严格的统计vdcc数目 而是需要讨论根节点的数目统计
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void tarjan(int u){
    dfn[u] = low[u] = ++timestamp;
    int cnt = 0;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(!dfn[j]){
            tarjan(j);
            low[u] = min(low[u],low[j]);
            //先更新在检查 
            if(low[j]>=dfn[u]) cnt++;//统计数目
        }else{
            //没有if判断 统计上回边也不影响
            low[u] = min(low[u],dfn[j]);
        }
    }
    if(u!=root) cnt++;//额外的加成
    res = max(res,cnt);
}
int main(){
    while(cin>>n>>m,n||m){
        memset(dfn,0,sizeof dfn);//low 不会作为判断标准 不需要
        memset(h,-1,sizeof h);
        idx = timestamp = 0;
        while(m--){
            int a,b;
            cin>>a>>b;
            add(a,b),add(b,a);
        }
        res = 0;
        int cnt = 0;
        //可能有多个联通快
        for(int i=0;i<n;i++){
            if(!dfn[i]){
                root = i;
                cnt++;
                tarjan(i);
            }
        }
        cout<<res+cnt-1<<endl;
    }
    return 0;
}
*/
//矿场搭建 难题--//给定一个无向图，问最少在几个点上设置出口，可以使得不管哪个点坍塌，其余所有点都可以与某个出口连通。
//关键：需要用到组合数学知识
//发现设置出口与有无割点有关系 在有割点情况下 一个点双联通分量有几个割点也很重要
//综上：当没有割点C(cnt,2) 当有割点，求得vdcc，之后建立边关系有每个割点与对应vdcc连边
//                       此时度数目表示割点数目 对于deg==1的vdcc 需要1 >1的vdcc不需要
//最后用乘法原理得到结果 
#include<vector>
const int N = 1010,M = 1010;
typedef unsigned long long ull;
int n,m;
int h[N],e[M],ne[M],idx;
int dfn[N],low[N],timestamp;
int stk[N],top;
int dcc_cnt;
vector<int> dcc[N];//需要真实存储 只用id不方便
bool iscut[N];
int root;
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void tarjan(int u){
    //求解vdcc切记特殊情况只有一个点处理
    if(u==root && h[u]==-1){
        dcc_cnt++;
        dcc[dcc_cnt].push_back(u);
        return;
    } 
    dfn[u] = low[u] = ++timestamp;
    stk[++top] = u;
    int cnt = 0;
    for(int i=h[u];i!=-1;i=ne[i]){
        int j = e[i];
        if(!dfn[j]){
            tarjan(j);
            low[u] = min(low[u],low[j]);
            if(dfn[u]<=low[j]){
                cnt++;
                if(cnt>1 || u!=root) iscut[u] = true;
                //即便只有一支 也需要统计vdcc
                int y;
                dcc_cnt++;
                do{
                    y = stk[top--];
                    dcc[dcc_cnt].push_back(y);
                }while(y!=j);
                dcc[dcc_cnt].push_back(u);
            }            
        }else{
            low[u] = min(low[u],dfn[j]);
        }
    }
}
int main(){
    int T = 1;
    while(cin>>m,m){
        // 初始化小心
        for(int i=1;i<=dcc_cnt;i++) dcc[i].clear();
        idx = timestamp = top = dcc_cnt = n = 0;
        memset(h,-1,sizeof h);
        memset(dfn,0,sizeof dfn);
        memset(iscut,0,sizeof iscut);
        while(m--){
            int a,b;
            cin>>a>>b;
            n = max(n,max(a,b));
            add(a,b),add(b,a);
        }
        for(int i=1;i<=n;i++){
            root = i;
            if(!dfn[i])
                tarjan(i);
        }
        int res = 0;
        ull num = 1;//乘法原理
        for(int i=1;i<=dcc_cnt;i++){
            int cnt = 0;
            for(int j=0;j<dcc[i].size();j++)
                if(iscut[dcc[i][j]])
                    cnt++;
            if(cnt==0){
                if(dcc[i].size()>1) res+=2,num*=dcc[i].size()*(dcc[i].size()-1)/2;
                else res++;
            }else if(cnt==1){
                res ++,num*=dcc[i].size()-1; 
            }
        }
        cout<<"Case "<<T++<<": "<<res<<" "<<num<<endl;
    }
    return 0;
}