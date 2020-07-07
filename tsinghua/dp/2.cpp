#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/*
//二叉苹果树 类似于 树形依赖背包问题
//f[u][i][j] 表示u(子树)考虑前i个物品组(子节点)装满j个的结果 -> f[u][j] 只需要逆序得到f[u][j]即可 枚举决策(子树中选取数目)即可 详单与在每个树节点上分组背包
//注意转移方程角度可以理解为f[u][i][j] = max(f[u][i-1][j],f[u][i-1][k]+f[e[i]][all][j-k-1]+w[i])
int n,m;
const int N = 100;
int h[N],e[N<<1],ne[N<<1],w[N<<1],idx = 0;
int f[N][N];
void init(){
    memset(h,-1,sizeof h);
    idx = 0;
}
void add(int a,int b,int v){
    e[idx] = b,ne[idx] = h[a],w[idx] = v,h[a] = idx++;
}
void dfs(int u,int fa){
    for(int i=h[u];i!=-1;i=ne[i]){
        if(e[i]==fa) continue;
        dfs(e[i],u);
        for(int j=m;j>=1;j--)//j==0自动为0
            for(int k=0;k+1<=j;k++)
                f[u][j] = max(f[u][j],f[u][k]+f[e[i]][j-k-1]+w[i]);
    }
}

int main(){
    cin>>n>>m;
    init();
    int a,b,v;
    for(int i=0;i<n-1;i++){
        cin>>a>>b>>v;
        add(a,b,v),add(b,a,v);
    }
    dfs(1,0);
    cout<<f[1][m]<<endl;
    return 0;
}
*/
/*
int n,m;
const int N = 110;
int h[N],e[N<<1],ne[N<<1],idx = 0;
int f[N][N];
int w[N];
void init(){
    memset(h,-1,sizeof h);
    idx = 0;
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void dfs(int u,int fa){
    for(int i=h[u];i!=-1;i=ne[i]){
        if(e[i]==fa) continue;
        dfs(e[i],u);
        for(int j=m-1;j>=0;j--)//j=m-v[u]
            for(int k=1;k<=j;k++)  
                f[u][j] = max(f[u][j],f[u][j-k]+f[e[i]][k]);
    }
    //修正结果
    for(int j=m-1;j>=0;j--) f[u][j+1] = f[u][j] + w[u];
    // for(int j=0;j<1;j++) f[u][j] = 0; //j<v[u]
    f[u][0] = 0;
}
int main(){
    cin>>n>>m;
    init();
    int a,b;
    for(int i=1;i<=n;i++){
        cin>>a>>b;
        add(a,i),add(i,a);
        w[i] = b;
    }
    w[0] = 0,m++;
    dfs(0,-1);
    cout<<f[0][m]<<endl;
    return 0;
}
*/
/*
//本质：求解树上最长链
const int N = 5e4+10;
int h[N],e[N<<1],ne[N<<1],idx = 0;
int sum[N];
int f[N][2];
int n;
bool vis[N];
int ans = 0;
void init(){
    idx = 0;
    memset(h,-1,sizeof h);
    memset(vis,0,sizeof vis);
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void getsum(){
    //正向思维
    for(int i=1;i<=n-1;i++)
        for(int j=2;j<=n/i;j++)
            sum[i*j] += i;
}
void dfs(int u,int fa){
    vis[u] = true;
    for(int i=h[u];i!=-1;i=ne[i]){
        if(e[i]==fa) continue;
        dfs(e[i],u);
        if(f[u][0]<=f[e[i]][0]+1) f[u][1]=f[u][0],f[u][0] = f[e[i]][0]+1;
        else if(f[u][1]<f[e[i]][0]+1) f[u][1] = f[e[i]][0]+1;
    }
    ans = max(ans,f[u][0]+f[u][1]);
}

int main(){
    cin>>n;
    init();
    getsum();
    for(int i=2;i<=n;i++)
        if(sum[i]<i)
            add(sum[i],i),add(i,sum[i]);
    for(int i=1;i<=n;i++){
        if(!vis[i])
            dfs(i,0);
    }
    cout<<ans<<endl;
    return 0;
}
*/

//不同于守皇宫 没有那麽多选择 只有放或者不放
/*
const int N = 1600;
int f[N][2];
int h[N],e[N],ne[N],idx = 0;
bool tag[N];
int n;
int ans = 0;
void init(){
    idx = 0;
    memset(h,-1,sizeof h);
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void dfs(int u){
    f[u][1] = 1,f[u][0] = 0;//叶结点
    for(int i=h[u];i!=-1;i=ne[i]){
        dfs(e[i]);
        f[u][1] += min(f[e[i]][0],f[e[i]][1]);
        f[u][0] += f[e[i]][1];
    }
}
int main(){
    cin>>n;
    int tmp,k,to;
    init();
    for(int i=0;i<n;i++){
        cin>>tmp>>k;
        for(int j=0;j<k;j++){
            cin>>to;
            add(i,to);
            tag[to] = true;
        }
    }
    for(int i=0;i<n;i++)
        if(!tag[i]){
            dfs(i);
            ans += min(f[i][0],f[i][1]);
        }
    cout<<ans<<endl;
    return 0;
}
*/

/*
const int N = 1600;
int f[N][3];
int h[N],e[N],ne[N],idx = 0;
bool st[N];
int w[N];
void dfs(int u){
    //不同于上一题 此题针对节点所以更复杂 需要考虑父节点 上一题针对边 不需要考虑父节点
    //f[u][0] 父节点在 本节点不在
    //f[u][1] 子节点在 本节点不在
    //f[u][2] 本节点在
    //从自给自足以及反向运算角度可以得到ff[u][1]计算方法
    f[u][0] = 0,f[u][2] = w[u],f[u][1] = 0x3f3f3f3f;
    for(int i=h[u];i!=-1;i=ne[i]){
        int v = e[i];
        dfs(v);
        f[u][0] += min(f[v][1],f[v][2]);
        f[u][2] += min(min(f[v][0],f[v][1]),f[v][2]);
    }
    //f[u][1]需要在f[u][0]求解完成后计算
    //从众多子节点中选出一个由普通自给自足min(f[v][1],f[v][2])->必须子结点上有f[v][2] 而其他节点不被影响
    //因此想到反向计算 所有节点自给自足为f[u][0] 所以f[u][1] = f[u][0] + mincost
    //mincost = min(f[v][2] - min(f[v][1],f[v][2]))
    for(int i=h[u];i!=-1;i=ne[i]){
        int v = e[i];
        f[u][1] = min(f[u][1],f[u][0]+f[v][2]-min(f[v][1],f[v][2]));
    }
}
void init(){
    idx = 0;
    memset(h,-1,sizeof h);
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
int main(){
    int n;
    cin>>n;
    int tmp,k,from,to;
    init();
    for(int i=1;i<=n;i++){
        cin>>from>>w[from]>>k;
        for(int j=0;j<k;j++){
            cin>>to;
            add(from,to);
            st[to] = true;
        }
    }
    int root = 1;
    while(st[root]) root++;
    dfs(root);
    cout<<min(f[root][1],f[root][2])<<endl;
    return 0;
}
*/
/*
const int N = 2e5+10;
int h[N],e[N<<1],ne[N<<1],idx = 0;
int f[N][2];
int ff[N];//保证有向
bool st[N];
int maxv = 0;
int n;
void init(){
    idx = 0;
    memset(h,-1,sizeof h);
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void dfs1(int u,int fa){
    //获得最长及次长路径
    ff[u] = fa;
    f[u][0] = 0,f[u][1] = -1;
    for(int i=h[u];i!=-1;i=ne[i]){
        int v = e[i];
        if(v==fa) continue;
        dfs1(v,u);
        if(f[u][0]<=1+f[v][0]) f[u][1] = f[u][0],f[u][0] = f[v][0] + 1;
        else if(f[u][1]<1+f[v][0]) f[u][1] = f[v][0] + 1;
    }
}
void dfs2(int u){
    //得到所有可能最长链上的点
    if(st[u]) return;
    st[u] = true;
    for(int i=h[u];i!=-1;i=ne[i]){
        int v = e[i];
        if(v==ff[u]) continue;
        // if(f[v][0]+1==f[u][0] || f[v][0]+1==f[u][1]) 
        if(f[v][0]+1==f[u][0]) 
            dfs2(v);
    }
}
int main(){
    cin>>n;
    int a,b;
    init();
    for(int i=0;i<n-1;i++){
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    dfs1(0,-1);
    for(int i=0;i<n;i++){
        maxv = max(maxv,f[i][0]+f[i][1]+1);
    }
    for(int i=0;i<n;i++){
        if(f[i][0]+f[i][1]+1==maxv){
            st[i] = true;
            for(int j=h[i];j!=-1;j=ne[j]){
                int v = e[j];
                //只有最开始可以选择双方
                if(f[v][0]+1==f[i][0] || f[v][0]+1==f[i][1]) 
                    dfs2(v);
            }
        }
    }
    for(int i=0;i<n;i++) if(st[i]) cout<<i<<endl;
    cout<<endl;
    return 0;
}
*/
/*
const int N = 6010;
int h[N],e[N],ne[N],idx = 0;
int w[N];
bool st[N];
int n;
int f[N][2];
void init(){
    idx = 0;
    memset(h,-1,sizeof h);
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void dfs(int u){
    f[u][0] = 0,f[u][1] = w[u];
    for(int i=h[u];i!=-1;i=ne[i]){
        int v = e[i];
        dfs(v);
        f[u][0] += max(f[v][0],f[v][1]);
        f[u][1] += f[v][0];
    }
}
int main(){
    cin>>n;
    init();
    for(int i=1;i<=n;i++) cin>>w[i];
    int a,b;
    while(cin>>a>>b,a||b){
        add(b,a);
        st[a] = true;
    }
    int ans = 0;
    for(int i=1;i<=n;i++){
        if(!st[i]){
            dfs(i);
            ans += max(f[i][0],f[i][1]);
        }
    }
    cout<<ans<<endl;
    return 0;
}
*/
//树染色问题 可以通过替换法证明任意选取根节点不改变结果
//其次由于将染色节点提升到跟不会影响结果 所以可以假设每个节点的子树中根节点必须染色 此时容易转移
//所以只需要从叶子节点转移到根节点即可
//dp[u][i]表示u代表的子树在满足条件下u染色为i所需要的最少染色数目
//只需呀合理初始化即可
/*
const int N = 1e4+10,inf = 0x3f3f3f3f;
int h[N],e[N<<1],ne[N<<1],idx = 0;
int n,m;
int f[N][2];
bool c[N];
void init(){
    idx = 0;
    memset(h,-1,sizeof h);
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void dfs(int u,int fa){
    if(u<=n){
        f[u][c[u]] = 1;
        f[u][c[u]^1] = inf;
    }else{
        f[u][0] = f[u][1] = 1;
    }
    for(int i=h[u];i!=-1;i=ne[i]){
        int v = e[i];
        if(v==fa) continue;
        dfs(v,u);
        f[u][0] += min(f[v][1],f[v][0]-1);
        f[u][1] += min(f[v][0],f[v][1]-1);
    }
}
int main(){
    cin>>m>>n;
    for(int i=1;i<=n;i++) cin>>c[i];
    init();
    int a,b;
    for(int i=0;i<m-1;i++){
        cin>>a>>b;
        add(a,b),add(b,a);
    }
    dfs(m,-1);
    cout<<min(f[m][0],f[m][1])<<endl;
    return 0;
}
*/

//化环为树 图->树 在简单圈（基环树）中可以
//借助并查集变成树 之后在树形dp结果基础上加以处理
const int N = 1e6+10;
typedef long long ll;
int h[N],e[N<<1],ne[N<<1],idx = 0;
ll f[N][2];
int p[N];
ll w[N];
int n;
pair<int,int> ps[N];
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
void init(){
    idx = 0;
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++) p[i] = i;
}
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
ll dfs(int u,int fa){
    //需要自带初始化
    f[u][1] = w[u],f[u][0] = 0;
    for(int i=h[u];i!=-1;i=ne[i]){
        int v = e[i];
        if(v==fa) continue;
        dfs(v,u);
        f[u][1] += f[v][0];
        f[u][0] += max(f[v][1],f[v][0]);
    }
    return f[u][0];
}
int main(){
    cin>>n;
    init();
    int to;
    int cnt = 0;
    for(int i=1;i<=n;i++){
        cin>>w[i]>>to;
        if(find(i)!=find(to)){
            add(i,to),add(to,i);
            p[p[i]] = p[to];
        }else{
            ps[cnt++] = {i,to};
        }
    }
    ll ans = 0;
    //处理每个连通块基环树
    for(int i=0;i<=cnt;i++){
        ans += max(dfs(ps[i].first,-1),dfs(ps[i].second,-1));//由于是去最值 所以可以重复 作为跟更方便处理
    }
    cout<<ans<<endl;
    return 0;
}