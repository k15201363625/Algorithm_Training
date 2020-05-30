#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
//并查集
/*
查询某个元素在哪个集合中
合并两个集合
时间复杂度：均摊O(1) ，是一个非常优秀的数据结构
本质：
并查集解决的是连通性（无向图联通分量）+传递性（家谱关系）问题，并且可以动态的维护。
(连通性判断 传递性问题)

带权并查集：
概念：在并查集的边上加上一些信息进行维护就是带权并查集
原理：并查集的边上存储与父亲结点有关的信息，一般需要满足可以向上合并，这样在路径
压缩时就可以合并信息到新的边上，至于合并操作，一般会给出要合并的两个结点之间的相
对关系，合并集合时根据以下关系实现
如图所示，给出关系c后，可以画出这样一个四边形，图中有2条路径可以从a到fa[b]而他们路径上的权值和（此处以求和为例）应该是相等的，这样就可以列出方程
value[a]+x=value[b]+c
移项后得到的就是合并时边权的取值x

带秩(size)并查集

拓展域并查集：
*/

//格子游戏(二维到一维)
/*
const int N = 40010;
int p[N];
int n,m;
int find(int x){
    if(x!=p[x]) p[x] = find(p[x]);
    return p[x];
}
int get(int x,int y){
    return x*n+y;
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n*n;i++) p[i] = i;
    int res = 0;
    for(int i=1;i<=m;i++){
        int x,y;
        char d;
        cin>>x>>y>>d;
        x--,y--;
        int a = get(x,y);
        int b;
        if(d=='D') b = get(x+1,y);
        else b = get(x,y+1);
        int pa = find(a),pb = find(b);
        if(pa==pb){
            res = i;
            break;
        }
        p[pa] = pb;
    }
    if(!res) cout<<"draw"<<endl;
    else cout<<res<<endl;
    return 0;
}
*/
//搭配购买 不是树形依赖dp 而是并查集
//并查集+背包
/*
const int N = 10010;
int n,m,vol;
int v[N],w[N];
int p[N],f[N];
int find(int x){
    if(x!=p[x]) p[x] = find(p[x]);
    return p[x];
}
//合并中 vw也需要合并
int main(){
    cin>>n>>m>>vol;
    for(int i=1;i<=n;i++) p[i] = i;
    for(int i=1;i<=n;i++) cin>>v[i]>>w[i];
    while(m--){
        int a,b;
        cin>>a>>b;
        int pa = find(a),pb = find(b);
        if(pa!=pb){
            v[pb] += v[pa];
            w[pb] += w[pa];
            p[pa] = pb;
        }
    }
    //01背包 只针对祖先节点
    for(int i=1;i<=n;i++)
        if(p[i]==i){
            for(int j=vol;j>=v[i];j--){
                f[j] = max(f[j],f[j-v[i]]+w[i]);
            }
        }
    cout<<f[vol]<<endl;
    return 0;
}
*/

// 程序自动化分析
/*
先排序，把所有e==1的操作放在前面，然后再进行e==0的操作，在进行e==1的操作的时候，我们只要把它约束的两个变量放在同一个集合里面即可。在e==0，即存在一条不相等的约束条件，对于它约束的两个变量，如果在一个集合里面，那就不可能满足！如不相等的约束条件都满足，那就YES。
要关注一下数据范围，是有10的9次方那么大，如果开一个10的9次方大的fa数组的话，空间肯定超限，所以，，我们需要用到离散化。

离散化是什么：一些数字，他们的范围很大（0-1e9），但是个数不算多（1-1e5），
并且这些数本身的数字大小不重要，重要的是这些数字之间的相对大小（比如说某个数字是这些数字中的第几小，而与这个数字本身大小没有关系，要的是相对大小）
（6 8 9 4 离散化后即为 2 3 4 1）（要理解相对大小的意思）（6在这4个数字中排第二小，那么就把6离散化成2，与数字6本身没有关系， 8,9,4亦是如此）

note:(保序离散化 无序离散化 分别是nlogn n复杂度)
离散化分为保序的离散化（排序判重二分）和不要求保序的离散化(hash)。
*/
//本题目保序离散化不必要而且时间不足nlogn
/*
#include<unordered_map>
const int N = 2e6+10;
unordered_map<int,int> S;
int n = 0;
int p[N];
struct query{
    int x,y;
    bool type;
}q[N];
int get(int x){
    if(S.count(x)==0) S[x] = ++n;
    return S[x];
}
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
int main(){
    int T;
    cin>>T;
    while(T--){
        n = 0;
        S.clear();
        int m;
        cin>>m;
        for(int i=0;i<m;i++){
            int a,b;
            cin>>a>>b>>q[i].type;
            q[i].x = get(a);
            q[i].y = get(b);
        }
        for(int i=1;i<=n;i++) p[i] = i;
        for(int i=0;i<m;i++)
            if(q[i].type==1){
                int pa = find(q[i].x),pb = find(q[i].y);
                p[pa] = pb;
            }
        //之后检查不等条件
        bool success = true;
        for(int i=0;i<m;i++)
            if(q[i].type==0){
                int pa = find(q[i].x),pb = find(q[i].y);
                if(pa==pb){
                    success = false;
                    break;
                }
            }
        if(success) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
*/
//银河英雄传说
//对于集合的操作只需要O1 而不是对于内部元素一个一个暴力操作** 
//通过集合维护信息的更新 在查找过程中利用这些信息保证正确性即可 在集合合并过程中也要维护这些信息
//关键 维护size 以及d的点信息 是带权并查集 维护了更多点信息的并查集
//d表示到根节点距离 size表示子树大小
/*
const int N = 30010;
int p[N];
int sz[N],d[N];
int m;
int find(int x){
    if(p[x]!=x){
        int rt = find(p[x]);
        d[x] += d[p[x]];
        p[x] = rt;//路径压缩在结果更新之后
    }
    return p[x];
}
int main(){
    cin>>m;
    for(int i=1;i<=N;i++) p[i] = i,sz[i] = 1;//d[i]=0
    while(m--){
        char op;
        int a,b;
        cin>>op>>a>>b;
        if(op=='M'){
            int pa = find(a),pb = find(b);
            d[pa] = sz[pb];
            sz[pb] += sz[pa];
            p[pa] = pb;
        }else{
            int pa = find(a),pb = find(b);
            if(pa!=pb) cout<<"-1"<<endl;
            else cout<<max(0,abs(d[a]-d[b])-1)<<endl;//小心为0有两种情况
        }
    }
    return 0;
}
*/
//cube stacking 类似于上一题

/*
[1]带权并查集本质是维护了到根节点的信息(相对信息)
[2]拓展域并查集基于枚举的思想 将个体拓展 
拓展域并查集用于解决一种有多个相互关系的并查集 比如一般的并查集只有相等关系 这个并查集支持更丰富关系
对与最简单的并查集来说，如果两个是同一类，那么就 p[pa]=pb
拓展域并查集 一个个体拆成多个(枚举个体情况) 对于互斥信息变成 a+n--b a--b+n 信息
            对于相同则有 a+n--b+n a--b  (最终会有k个并查集 k表示信息关系类别数目)
同理可以扩展到更多相互关系类别的信息(相等 排斥是二类信息)

对于相互关系矛盾性判断问题：
[1]用带权并查集 只需要一个1n大小并查集可以通过维护相对根节点的信息d 从而得到矛盾与否
[2]用拓展域并查集 需要用到kn大小并查集 基于对于个体枚举扩展为n个个体的思想 空间时间消耗变大 
                通过维护不同的枚举可能(拓展个体)的并查集实现 但是随k着数目增多 集合大小以及操作更复杂
*/
//例题1：奇偶游戏（k==2）
//利用前缀和思想 变换为判断奇偶性相同与否问题 (d1+d2)%2表示奇偶性 但是可以用^简单处理
//离散化
//方法1 带权并查集
/*
#include<unordered_map>
const int N = 20010;
int n,m;
int p[N],d[N];
unordered_map<int,int> S;
int get(int x){
    if(S.count(x)==0) S[x]=++n;
    return S[x];
}
int find(int x){
    if(p[x]!=x){
        int rt = find(p[x]);
        d[x] ^= d[p[x]];
        p[x] = rt;
    }
    return p[x];
}
int main(){
    cin>>n>>m;
    n = 0;
    for(int i=0;i<N;i++) p[i] = i;
    int res = m;
    for(int i=1;i<=m;i++){
        int a,b;
        string type;
        cin>>a>>b>>type;
        a = get(a-1),b = get(b);
        int t = 0;
        if(type=="odd") t = 1;
        int pa = find(a),pb = find(b);
        if(pa==pb){
            if(d[a]^d[b]!=t){
                res = i-1;
                break;
            }
        }else{
            p[pa] = pb;
            //可以用连立方程/用不同路径相同结果两种方式理解
            d[pa] = d[a]^d[b]^t;
        }
    }
    cout<<res<<endl;
    return 0;
}
*/

//拓展域
/*
#include<unordered_map>
const int N = 40010,Base = N/2;//开成2×N
int n,m;
int p[N];
unordered_map<int,int> S;
int get(int x){
    if(S.count(x)==0) S[x] = ++n;
    return S[x];
}
int find(int x){
    if(x!=p[x]) p[x] = find(p[x]);
    return p[x];
}
int main(){
    cin>>n>>m;
    n = 0;
    for(int i=0;i<N;i++) p[i] = i;
    int res = m;
    for(int i=1;i<=m;i++){
        int a,b;
        string type;
        cin>>a>>b>>type;
        a = get(a-1),b = get(b);
        if(type=="even"){
            if(find(a+Base)==find(b)){
                res = i-1;
                break;
            }
            p[find(a)] = find(b);
            p[find(a+Base)] = find(b+Base);
        }else{
            if(find(a)==find(b)){
                res = i-1;
                break;
            }
            p[find(a+Base)] = find(b);
            p[find(a)] = find(b+Base);
        }
    }
    cout<<res<<endl;
    return 0;
}
*/

//例题2：食物链（k==3）
//循环吃问题：
//采用带权并查集 用到了%3加法判断
/*
判断：
(d[x]-d[y]+3)%3(相对关系)
[1]==0 同类 [2]==1 x吃y
合并操作：
(d[x]+d[px]-d[y]+3) %3 =0/1从而推导得到d[px]设定什么数值 
note:d可以为负数 所以用+3%3技巧
*/
/*
const int N = 50010;
int n,m;
int p[N],d[N];
int res;
int find(int x){
    if(x!=p[x]){
        int rt = find(p[x]);
        d[x] = (d[x]+d[p[x]]+3)%3;
        p[x] = rt;
    }
    return p[x];
}
int main(){
    int res = 0;
    cin>>n>>m;
    for(int i=1;i<=n;i++) p[i] = i,d[i] = 0;
    while(m--){
        int a,b,c;
        cin>>c>>a>>b;
        if(a>n||b>n||(c==2&&a==b)) res++;
        else{
            int pa = find(a),pb = find(b);
            if(c==1){
                if(pa==pb){
                    //判断
                    if((d[a]-d[b]+3)%3) res++;
                }else{
                    //合并
                    p[pa] = pb;
                    d[pa] = (d[b]-d[a]+3)%3;
                }
            }else{
                if(pa==pb){
                    if((d[a]-d[b]+3)%3!=1) res++;
                }else{
                    p[pa] = pb;
                    d[pa] = (d[b]-d[a]+1+3)%3;
                }
            }
        }
    }
    cout<<res<<endl;
    return 0;
}
*/
//拓展域做法
//由于有3个关系--三点形成的环（每个点可以拓展成三种可能）所以需要三个并查集
/*
拆成3个 x x+n x+2n 分别表示本身 猎物 以及捕食者 三者形成环形关系
同类很简单 分别相等即可
捕食关系则需要分类讨论:
    x    x+n   x+2n 
    y+2n  y    y+n
对于x可能处于三种不同的状态 可以得到对应的y的不同可能的状态与x可能状态的对应关系
本质上是基于枚举x可能的状态 得到当前关系x吃y条件下确定的三种可能的关系对 从而在相应的并查集中进行合并操作
这样合并所有关系 保证了在检查的时候只需要检查其中一对关系成立与否即可
*/
/*
const int N = 150010,Base = N/3;
int p[N];
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
void merge(int x,int y){
    p[find(x)] = find(y);
}
int main(){
    int n,m;
    cin>>n>>m;
    int ans = 0;
    for(int i=1;i<=3*n;i++) p[i] = i;
    int c,x,y;
    while(m--){
        cin>>c>>x>>y;
        if(x>n || y>n || (c==2&&x==y)){
            ans ++;
            continue;
        }
        if(c==1){
            //两种情况小心
            if(find(x+n)==find(y) || find(y+n)==find(x)) ans++;
            else{
               merge(x,y),merge(x+n,y+n),merge(x+2*n,y+2*n); 
            } 
        }else{
            //也有两种情况小心
            if(find(x)==find(y) || find(y+n)==find(x)) ans++;
            else{
                merge(x+n,y),merge(x+2*n,y+n),merge(x,y+2*n);
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}
*/

