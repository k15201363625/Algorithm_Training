#include<iostream>
#include<cstring>
#include<algorithm>
#include<cstdio>
using namespace std;
//树状数组 BIT(binary indexed tree) 
/*
对于普通数组/前缀和都只能使用O1 On实现查询前缀与修改单点
而折中 使用变成均为logn方法实现修改与查询
思想：
首先需要知道一个定义：
C(i)表示以i为结尾长度为lowbit(i)的一段区间的和(后缀区间和)
求和：
任何一个和使用二进制拆分 拆成为一个对应的为1所对应的数字的前缀和 实现logn求和
但是在修改中为难点：
发现C之间的关系 C(x)->x，对x-1进行拆分 确定了在BIT中的直接父子关系
所以在更新的时候也只需要直接更新到父节点上即可其他节点不用管
而由于-1之后最多拆分成logn个所以会有logn层最大深度 保证了logn修改复杂度
（弄清楚C之间的父子关系就可以得到相应的变化计算方式）
所以有为了得到子节点可以影响到的父节点只需要+lowbit(x)
拓展：
1 通过求差分思想得到单点查询 区间修改
2 二维情况
3 通过差分+公式推导 维护两个/多个bit实现区间修改区间查询

note：两种方式实现On建树 不过意义不大
1 只更新对应的父亲节点-lognn是逐个添加 这里采用奇数项保留 偶数项+=奇数项 迭代logn层 得到2*n复杂度建树
2 先统计前缀和 通过相减得到正确结果(显然)
*/

//楼兰古城：
//使用分组+乘法原理实现统计 需要快速得到小于/大于某个数的个数 转换为在权值树状数组上的前缀后缀和查询即可
/*
const int N = 200010;
int tr[N];
int gre[N],low[N];
int a[N];
int n;
inline int lowbit(int x){
    return x&(-x);
}
void add(int x,int v){
    for(int i=x;i<=n;i+=lowbit(i)) 
        tr[i] += v;
}
int sum(int x){
    int res = 0;
    for(int i=x;i>0;i-=lowbit(i))
        res += tr[i];
    return res;
}

int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    //顺着扫描+逆着扫描 一边添加以便统计权值bit结果
    //统计前驱
    memset(tr,0,sizeof tr);
    for(int i=1;i<=n;i++){
        int y = a[i];
        gre[i] = sum(n)-sum(y);
        low[i] = sum(y-1);
        add(y,1);
    }
    memset(tr,0,sizeof tr);
    long long res1 = 0,res2 = 0;
    for(int i=n;i>0;i--){
        int y = a[i];
        res1 += gre[i]*1ll*(sum(n)-sum(y));
        res2 += low[i]*1ll*sum(y-1);
        add(y,1);
    }
    cout<<res1<<" "<<res2<<endl;
    return 0;
}
*/

//拓展后的模板题目
//区间+ 单点查
/*
const int N = 1e5+10;
int tr[N];
int n,m;
int arr[N];
inline int lowbit(int x){
    return x&(-x);
}
void add(int x,int c){
    for(int i=x;i<=n;i+=lowbit(i))
        tr[i] += c;
}
//最终结果不会溢出 但是过程中可能计算溢出
long long sum(int x){
    long long res = 0;
    for(int i=x;i>0;i-=lowbit(i))
        res += (long long)tr[i];
    return res;
}
int a,b,c;
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        cin>>arr[i];
        add(i,arr[i]-arr[i-1]);
    }
    char op;
    int a,b,c;
    while(m--){
        cin>>op;
        if(op=='C'){
            cin>>a>>b>>c;
            add(a,c),add(b+1,-c);
        }else{
            cin>>a;
            cout<<sum(a)<<endl;
        }
    }
    return 0;
}
*/

//快速实现区间+ 区间查询 这时候需要用公式推导
//采用展开求和式子 并且从横向累加->纵向累加 之后通过求补集 转化为只需要a[i] i*a[i]两个树状数组即可
/*
typedef long long LL;
const int N = 1e5+10;
int n,m;
LL tr1[N],tr2[N];//前面的前缀和不会溢出 这里可能溢出
int arr[N];
inline int lowbit(int x){
    return x&(-x);
}
void add(LL tr[],int x,LL c){
    for(int i=x;i<=n;i+=lowbit(i))
        tr[i] += c;
}
LL sum(LL tr[],int x){
    LL res = 0;
    for(int i=x;i;i-=lowbit(i))
        res += tr[i];
    return res;
}
LL getpresum(int x){
    return sum(tr1,x)*(x+1) - sum(tr2,x);
}

int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i];
    for(int i=1;i<=n;i++){
        int b = arr[i]-arr[i-1];
        add(tr1,i,b),add(tr2,i,1ll*b*i);
    }
    char op;
    int a,b,c;
    while(m--){
        cin>>op;
        if(op=='C'){
            cin>>a>>b>>c;
            add(tr1,a,c),add(tr1,b+1,-c);
            add(tr2,a,a*c),add(tr2,b+1,(b+1)*(-c));
        }else{
            cin>>a>>b;
            cout<<getpresum(b)-getpresum(a-1)<<endl;
        }
    }
    return 0;
}
*/

//好题：谜一样的牛
//如果从前开始无法确定 但是从后面开始可以发现ai表示当前是除了已经选好的之外ai+1排名的奶牛
//如果从前面 无法确定当前位置 但是从后往前 可以逐个确定当前位置奶牛
//设计操作 查找k大元素 删除某个元素 -> 平衡树可以  但是bit可以实现logn*logn也很快(常熟小)
//二分+bit查询操作lognlogn
const int N = 1e5+10;
int a[N],res[N];
int tr[N];
int n;
inline int lowbit(int x){
    return x&(-x);
}
int sum(int x){
    int res = 0;
    for(int i=x;i;i-=lowbit(i))
        res += tr[i];
    return res;
}
void add(int x,int c){
    for(int i=x;i<=n;i+=lowbit(i))
        tr[i]+=c;
}

int getkthnum(int k){
    int l=1,r=n;
    while(l<r){
        int mid = (l+r)>>1;
        if(sum(mid)>=k) r = mid;
        else l = mid+1;
    }
    return l;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) tr[i] = lowbit(i);
    for(int i=2;i<=n;i++) cin>>a[i];//a[1]=0
    for(int i=n;i>=1;i--){
        res[i] = getkthnum(a[i]+1);
        add(res[i],-1);
    }
    for(int i=1;i<=n;i++) cout<<res[i]<<endl;
    return 0;
}