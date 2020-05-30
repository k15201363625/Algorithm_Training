#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
//线段树 基本操作 单点修改单点区间查询  进阶操作：区间修改 区间信息维护(lazy标记)
//空间4×n(静态) 动态2*n
/*
query难点
难点 注意返回 必须返回node才能包含所需要的全部信息 不同于平时只需要返回一个max/sum就可以计算
由于这里维护的信息比较复杂 需要返回node才能便于统计
而且这个node未必是tr中的节点 可能需要重新着生成的节点 所以可能返回重新构造的节点
由于可能有负数 需要小心初始化为全0可能错误
*/

/*
const int N = 2e5+10;
int m,p;
struct Node{
    int l,r;
    long long v;
}tr[N*4];

inline void push_up(int u){
    tr[u].v = max(tr[u<<1].v,tr[u<<1|1].v);
}
void build(int u,int l,int r){//没有数据 只是建立lr关联结构
    tr[u] = {l,r,0};
    if(l==r) return;
    int mid = (l+r)>>1;
    build(u<<1,l,mid),build(u<<1|1,mid+1,r);
}
int query(int u,int l,int r){
    if(tr[u].l>=l && tr[u].r<=r) return tr[u].v;
    int mid = (tr[u].l+tr[u].r) >> 1;
    int v = 0;
    if(l<=mid) v = query(u<<1,l,r);
    if(r>mid) v = max(v,query(u<<1|1,l,r));
    return v;
}
void modify(int u,int x,int y){
    if(tr[u].l==tr[u].r && tr[u].l==x) tr[u].v = y;
    else{
        int mid = (tr[u].l+tr[u].r)>>1;
        if(x<=mid) modify(u<<1,x,y);
        else modify(u<<1|1,x,y);
        push_up(u);
    }
}
//最大数 
//查找最大数值 设计区间改动 可以用树状数组
int main(){
    int n = 0,last = 0;
    cin>>m>>p;
    build(1,1,m);
    int x;
    char op;
    while(m--){
        cin>>op>>x;
        if(op=='Q'){
            last = query(1,n-x+1,n);
            cout<<last<<endl;
        }else{
            modify(1,n+1,(0ll+last+x)%p);
            n++;
        }
    }
    return 0;
}
*/

//区间最大连续字段和动态维护问题
//你能回答这些问题吗？ 
//关键：维护 sum rmax lmax tmax 就可以实现 注意sum不要忘记
//难点在于pushup操作
/*
const int N = 5e5+10;
#define ls u<<1
#define rs u<<1|1
int w[N];
struct Node{
    int l,r;
    int sum,tmax,lmax,rmax;
}tr[N<<2];
void pushup(int u){
    tr[u].sum = tr[ls].sum + tr[rs].sum;
    tr[u].tmax = max(max(tr[ls].tmax,tr[rs].tmax),tr[ls].rmax+tr[rs].lmax);
    tr[u].lmax = max(tr[ls].lmax,tr[ls].sum+tr[rs].lmax);
    tr[u].rmax = max(tr[rs].rmax,tr[rs].sum+tr[ls].rmax);
}
//本题需要将初始数据赋值
void build(int u,int l,int r){
    if(l==r) tr[u] = {l,r,w[l],w[l],w[l],w[l]};
    else{
        tr[u] = {l,r};//不要忘记
        int mid = (l+r)>>1;
        build(ls,l,mid),build(rs,mid+1,r);
        pushup(u);
    }
}
void modify(int u,int x,int v){
    if(tr[u].l == x && tr[u].r == x){
        tr[u] = {x,x,v,v,v,v};
        return;
    }
    int mid = (tr[u].l + tr[u].r)>>1;
    if(x<=mid) modify(ls,x,v);
    else modify(rs,x,v);
    pushup(u);
}
//难点 注意返回 必须返回node才能包含所需要的全部信息 不同于平时只需要返回一个max/sum就可以计算
//由于这里维护的信息比较复杂 需要返回node才能便于统计
//而且这个node未必是tr中的节点 可能需要重新着生成的节点 所以可能返回重新构造的节点
//由于可能有负数 需要小心初始化为全0可能错误
Node query(int u,int l,int r){
    //单单是返回一个点不可以 需要这个点上的的其他信息 从而合并 所以需返回node（可能创造新的node）
    if(tr[u].l>=l && tr[u].r<=r) return tr[u];
    int mid = (tr[u].l+tr[u].r)>>1;
    if(r<=mid) return query(u<<1,l,r);
    if(l>=mid+1) return query(u<<1|1,l,r);
    Node ll,rr;//本来为空0 但是如果有负数 可能导致结果不正确
    //****所以为空的时候不能汇合处理****
    ll = query(ls,l,r);
    rr = query(rs,l,r);
    Node res;
    res.tmax = max(max(ll.tmax,rr.tmax),ll.rmax+rr.lmax);
    res.lmax = max(ll.sum+rr.lmax,ll.lmax);
    res.rmax = max(rr.rmax,rr.sum+ll.rmax);
    res.sum = ll.sum + rr.sum;
    return res;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i];
    build(1,1,n);
    while(m--){
        int k,x,y;
        cin>>k>>x>>y;
        if(k==1){
            if(x>y) swap(x,y);
            cout<<query(1,x,y).tmax<<endl;
        }else{
            modify(1,x,y);
        }
    }
    return 0;
}
*/

//gcd重要性质
//gcd(a,b,c)==gcd(a,b-a,c-b) 转换为差分的gcd
//因为区间+d之后求gcd不太直观 目标转换成单点 所以想到用差分
//区间+变成单点修改 区间gcd变成单点修改下的gcd 而单点修改下的区间gcd很容易
// 综上 区间gcd问题需要转换成单点修改下的区间gcd 否则难以快速维护
//而这样借助差分转换为了维护sum gcd信息的单点修改线段树 query需要返回两个数值(都需要)
/*
const int N = 500010;
typedef long long ll;
#define ls u<<1
#define rs u<<1|1
long long w[N];
int n,m;
struct Node{
    int l,r;
    ll sum,d;
}tr[N<<2];

//note 对于负数 gcd(a,-b) == gcd(a,b)所以运算中需要处理一下 便于计算
ll gcd(ll a,ll b){
    return b==0?a:gcd(b,a%b);//gcd(a,b)==gcd(a,a-b)=gcd(a-b,b) a-nb b-na都可以
}
void pushup(int u){
    tr[u].sum = tr[ls].sum+tr[rs].sum;
    tr[u].d = gcd(tr[ls].d,tr[rs].d);
}
void build(int u,int l,int r){
    if(l==r) tr[u] = {l,r,w[r]-w[r-1],w[r]-w[r-1]};
    else{
        tr[u] = {l,r};
        int mid = (l+r)>>1;
        build(ls,l,mid),build(rs,mid+1,r);
        pushup(u);
    }
}

void modify(int u,int x,ll v){
    if(tr[u].l==x && tr[u].r==x) tr[u].sum += v,tr[u].d += v;
    else{
        int mid = tr[u].l + tr[u].r >>1;
        if(x<=mid) modify(ls,x,v);
        else modify(rs,x,v);
        pushup(u);
    }
}
Node query(int u,int l,int r){
    if(tr[u].l>=l && tr[u].r<=r) return tr[u];
    int mid = (tr[u].l+tr[u].r)>>1;
    if(r<=mid) return query(ls,l,r);
    if(l>=mid+1) return query(rs,l,r);
    Node left = query(ls,l,r),right = query(rs,l,r);
    Node res;
    res.sum = left.sum + right.sum;
    res.d = gcd(left.d,right.d);
    return res;
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i];
    build(1,1,n);
    int l,r;
    ll x;
    char op;
    while(m--){
        cin>>op>>l>>r;
        if(op=='Q'){
            Node left = query(1,1,l),right = query(1,l+1,r);
            //千万小心 虽然对于负数采用%仍然能得到正确计算结果 但是由于gcd定义为正数 需要取abs作为结果
            //note:gcd都定义为正数 需对结abs
            cout<<abs(gcd(left.sum,right.d))<<endl;
        }else{
            cin>>x;
            modify(1,l,x);
            //只有在r+1在范围内才需要进行操作
            if(r+1<=n) modify(1,r+1,-x);
        }
    }
    return 0;
}
*/
//模板 使用线段树维护区间修改 区间查询操作(树状数组也可以)
//学要使用懒标记
/*
#define ls u<<1
#define rs u<<1|1
typedef long long ll;
const int N = 100010;
int n,m;
int w[N];
struct Node{
    int l,r;
    ll sum,add;
}tr[N*4];
void pushup(int u){
    tr[u].sum = tr[ls].sum + tr[rs].sum;
}
void pushdown(int u){
    //设置懒惰标记
    Node & root = tr[u],&left = tr[ls],&right = tr[rs];
    if(root.add){
        left.add += root.add,right.add += root.add;
        left.sum += (left.r-left.l+1)*root.add;
        right.sum += (right.r-right.l+1)*root.add;
        root.add = 0;
    }
}
void build(int u,int l,int r){
    if(l==r) tr[u] = {l,r,w[l],0};
    else{
        tr[u] = {l,r};
        int mid = (l+r)>>1;
        build(ls,l,mid),build(rs,mid+1,r);
        pushup(u);
    }
}
void modify(int u,int l,int r,int v){
    if(tr[u].l>=l && tr[u].r<=r) {
        tr[u].sum += 1ll*(tr[u].r-tr[u].l+1)*v;
        tr[u].add += v;
    }else{
        pushdown(u);
        int mid = (tr[u].l+tr[u].r)>>1;
        if(l<=mid) modify(ls,l,r,v);
        if(r>=mid+1) modify(rs,l,r,v);
        pushup(u);
    }
}
ll query(int u,int l,int r){
    if(tr[u].l>=l&&tr[u].r<=r)
        return tr[u].sum;
    pushdown(u);
    ll res = 0;
    int mid = (tr[u].l+tr[u].r)>>1;
    if(l<=mid) res += query(ls,l,r);
    if(r>=mid+1) res += query(rs,l,r);
    return res; 
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>w[i];
    build(1,1,n);
    // char op;
    int op;
    int l,r,x;
    while(m--){
        cin>>op>>l>>r;
        if(op==1){
            cin>>x;
            modify(1,l,r,x);
        }else{
            cout<<query(1,l,r)<<endl;
        }
    }
    return 0;
}
*/

//亚特兰蒂斯 扫描线维护面积
/*
#include<iomanip>
#include<vector>
#define ls u<<1
#define rs u<<1|1
const int N = 1e5+10;
//小心空间
struct edge{
    double x,y1,y2;
    int k;
    bool operator<(const edge& o)const{
        return x<o.x;
    }
}edges[N*2];
struct Node{
    int l,r;
    int cnt;
    double len;
}tr[N*8];
int n;
vector<double> ys;
//离散化辅助函数
inline int find(double y){
    return lower_bound(ys.begin(),ys.end(),y)-ys.begin();
}
//线段树操作中注意用的是一个线段的起点代表这一条线段
//不同与维护sum的普通pushup 这里的pushup不仅仅用于更新父节点 对于单一的子节点更新功能也融合在这里
//所以可能会有l==r情况 为单一结点 此时不需要也不能使用ls rs
inline void pushup(int u){
    //小心 需要特<殊判断 
    //难点
    if(tr[u].cnt>=1) tr[u].len = ys[tr[u].r+1]-ys[tr[u].l];
    else if(tr[u].l!=tr[u].r){
        tr[u].len = tr[ls].len + tr[rs].len;
    }else{
        tr[u].len = 0;
    }
}
void build(int u,int l,int r){
    if(l==r) tr[u] = {l,r,0,0};
    else{
        tr[u] = {l,r};
        int mid = (l+r)>>1;
        build(ls,l,mid),build(rs,mid+1,r);
    }
}
//区间修改
//但是由于查询永远在总区间 所以不需要下推标记等操作 只需每次更新饿时候及时上推更新即可
void modify(int u,int l,int r,int v){
    //小心 即使可以变成对于单点的修改 也需要重新维护这一点的len 这里统一使用pushup
    if(tr[u].l>=l && tr[u].r<=r){
        tr[u].cnt += v;
        pushup(u);
    }else{
        int mid = (tr[u].l+tr[u].r)>>1; 
        if(l<=mid) modify(ls,l,r,v);
        if(r>=mid+1) modify(rs,l,r,v);
        pushup(u);    
    }
}
int main(){
    int T = 1;
    while(cin>>n,n){
        ys.clear();
        for(int i=0,j=0;i<n;i++){
            double x1,x2,y1,y2;
            cin>>x1>>y1>>x2>>y2;
            edges[j++] = {x1,y1,y2,1};
            edges[j++] = {x2,y1,y2,-1};
            ys.push_back(y1),ys.push_back(y2);
        }
        //离散化+对edges排序并且进行操作
        sort(ys.begin(),ys.end());
        ys.erase(unique(ys.begin(),ys.end()),ys.end());
        sort(edges,edges+n*2);
        
        build(1,0,ys.size()-2);//小心范围是最后一条线段的起点
        double res = 0;
        for(int i=0;i<n*2;i++){
            //每次先统计之后插入更新(小心顺序) 最开始一次不需要统计
            if(i>0) res += tr[1].len * (edges[i].x - edges[i-1].x);
            modify(1,find(edges[i].y1),find(edges[i].y2)-1,edges[i].k);
        }
        cout<<"Test case #"<<T++<<endl;
        cout<<fixed<<setprecision(2)<<"Total explored area: "<<res<<endl;
        cout<<endl;
    }
    return 0;
}
*/
/*
//luogu类似题目
#include<vector>
#define ls u<<1
#define rs u<<1|1
typedef long long ll;
const int N = 1e3+10;
//小心空间
struct edge{
    ll x,y1,y2;
    int k;
    bool operator<(const edge& o)const{
        return x<o.x;
    }
}edges[N*2];
struct Node{
    int l,r;
    int cnt;
    ll len;
}tr[N*8];
int n;
vector<int> ys;
//离散化辅助函数
inline int find(ll y){
    return lower_bound(ys.begin(),ys.end(),y)-ys.begin();
}
//线段树操作中注意用的是一个线段的起点代表这一条线段
//不同与维护sum的普通pushup 这里的pushup不仅仅用于更新父节点 对于单一的子节点更新功能也融合在这里
//所以可能会有l==r情况 为单一结点 此时不需要也不能使用ls rs
inline void pushup(int u){
    //小心 需要特<殊判断 
    //难点
    if(tr[u].cnt>=1) tr[u].len = ys[tr[u].r+1]-ys[tr[u].l];
    else if(tr[u].l!=tr[u].r){
        tr[u].len = tr[ls].len + tr[rs].len;
    }else{
        tr[u].len = 0;
    }
}
void build(int u,int l,int r){
    if(l==r) tr[u] = {l,r,0,0};
    else{
        tr[u] = {l,r};
        int mid = (l+r)>>1;
        build(ls,l,mid),build(rs,mid+1,r);
    }
}
//区间修改
//但是由于查询永远在总区间 所以不需要下推标记等操作 只需每次更新饿时候及时上推更新即可
void modify(int u,int l,int r,int v){
    //小心 即使可以变成对于单点的修改 也需要重新维护这一点的len 这里统一使用pushup
    if(tr[u].l>=l && tr[u].r<=r){
        tr[u].cnt += v;
        pushup(u);
    }else{
        int mid = (tr[u].l+tr[u].r)>>1; 
        if(l<=mid) modify(ls,l,r,v);
        if(r>=mid+1) modify(rs,l,r,v);
        pushup(u);    
    }
}
int main(){
    cin>>n;
    ys.clear();
    for(int i=0,j=0;i<n;i++){
        ll x1,x2,y1,y2;
        cin>>x1>>y1>>x2>>y2;
        //不同题目坐标给出方式 小心设置方式 
        edges[j++] = {x1,y2,y1,1};
        edges[j++] = {x2,y2,y1,-1};
        ys.push_back(y1),ys.push_back(y2);
    }
    //离散化+对edges排序并且进行操作
    sort(ys.begin(),ys.end());
    ys.erase(unique(ys.begin(),ys.end()),ys.end());
    sort(edges,edges+n*2);
    
    build(1,0,ys.size()-2);//小心范围是最后一条线段的起点
    ll res = 0;
    for(int i=0;i<n*2;i++){
        //每次先统计之后插入更新(小心顺序) 最开始一次不需要统计
        if(i>0) res += tr[1].len * (edges[i].x - edges[i-1].x);
        modify(1,find(edges[i].y1),find(edges[i].y2)-1,edges[i].k);
    }
    cout<<res<<endl;
    return 0;
}
*/
//维护周长问题
//模板2 mul add双标记问题
//双标记考虑结合性质 sum*mul+add 对于接下来的*标记 +标记均易于处理 但是(sum+add)*mul 对于接下来的+标记不宜与处理
//所以采用*mul +add方式维护 所以有了标记作用先后顺序
/*
#define ls u<<1
#define rs u<<1|1
const int N = 1e5+10;
int n,m,p;
int w[N];
struct Node{
    int l,r;
    int sum,add,mul;
}tr[N*4];
void pushup(int u){
    tr[u].sum = tr[ls].sum + tr[rs].sum;
}
void eval(Node &rt,int add,int mul){
    rt.sum = (1ll*rt.sum*mul + 1ll*(rt.r-rt.l+1)*add)%p;
    rt.mul = 1ll*rt.mul*mul%p;
    rt.add = (1ll*rt.add*mul + add)%p;
}
void pushdown(int u){
    eval(tr[ls],tr[u].add,tr[u].mul),eval(tr[rs],tr[u].add,tr[u].mul);
    tr[u].add = 0,tr[u].mul = 1;
}
void build(int u,int l,int r){
    if(l==r){
        tr[u] = {l,r,w[r]%p,0,1};
    }else{
        tr[u] = {l,r,0,0,1};//小心不能设置为{l,r}因为mul需要为1
        int mid = (l+r)>>1;
        build(ls,l,mid),build(rs,mid+1,r);
        pushup(u);
    }
}
void modify(int u,int l,int r,int add,int mul){
    if(tr[u].l>=l && tr[u].r<=r){
        eval(tr[u],add,mul);
    }else{
        pushdown(u);
        int mid = (tr[u].l + tr[u].r) >> 1;
        if(l<=mid) modify(ls,l,r,add,mul);
        if(r>=mid+1) modify(rs,l,r,add,mul);
        pushup(u);
    }
}
int query(int u,int l,int r){
    if(tr[u].l>=l && tr[u].r<=r) return tr[u].sum;
    pushdown(u);
    int mid = (tr[u].l + tr[u].r)>>1;
    int sum = 0;
    if(l<=mid) sum += query(ls,l,r);
    if(r>=mid+1) sum = (sum+query(rs,l,r))%p;
    return sum;
}
int main(){
    cin>>n>>m>>p;
    for(int i=1;i<=n;i++) cin>>w[i];
    build(1,1,n);
    while(m--){
        int op,l,r,d;
        cin>>op>>l>>r;
        if(op==1){
            cin>>d;
            modify(1,l,r,0,d);
        }else if(op==2){
            cin>>d;
            modify(1,l,r,d,1);
        }else{
            cout<<query(1,l,r)<<endl;
        }
    }
    return 0;
}
*/

