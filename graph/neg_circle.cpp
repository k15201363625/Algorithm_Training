#include<iostream>
#include<cstring>
#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
//负环判断方法：
/*
使用bellman-ford/spfa(本质：基于抽屉原理)
两种判断方法：
1 统计每个点入队次数 如果入队n次必然被更新了超过>=n次 必然存在负环
2 通过每个点最短路中所包含的边数 如果>=n 则表示存在负环
    note：更加高效，因为可能一个点被更新了但是因为在队列中没有再次入队 所以更正确判断了边数
note：由于存在负环 所以初始化成什么最终结果都会是-inf 所以无需初始化
note2：对于非全部连通情况下 不需要依次使用spfa  只需要将所有点都初始加入队列
       可以理解成由虚拟节点建立了一条边连向所有节点 保证了整体的连通性
note3：复杂度分析 由于基于bellmanford 最差mn 但是为了加快负环判断效率 两个策略
    【1】使用stack 而不是queue 这样一个点被更新后可以快速更新他相关的点
    【2】使用经验数值 k*m 当所有节点入队次数超过k*m认为很大可能存在负环
note4：分析2方法为什么更好--特例如果有一个全负环 则需要nm才能用1解决 而二方法只需要n可以解决
*/
/*
const int N = 510, M = 5210;
int n,m1,m2;
int h[N],e[M],w[M],ne[M],idx;
int d[N];
int q[N],cnt[N];
bool st[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
bool spfa(){
    memset(d,0,sizeof 0);
    memset(cnt,0,sizeof cnt);
    memset(st,0,sizeof st);
    int hh = 0,tt = 0;
    for(int i=1;i<=n;i++)
        q[tt++] = i,st[i] = true;
    while(hh!=tt){
        int t = q[hh++];
        if(hh==N) hh = 0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+w[i]){
                d[j] = d[t]+w[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j]>=n) return true;
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt = 0;
                    st[j] = true;
                }
            }

        }
    }
    return false;
}
int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n>>m1>>m2;
        memset(h,-1,sizeof h);
        idx = 0;
        int a,b,c;
        for(int i=0;i<m1;i++){
            cin>>a>>b>>c;
            add(a,b,c),add(b,a,c);
        }
        for(int i=0;i<m2;i++){
            cin>>a>>b>>c;
            add(a,b,-c);
        }
        if(spfa()) cout<<"YES"<<endl;
        else cout<<"NO"<<endl;
    }
    return 0;
}
*/

//观光奶牛
//思路：发现是一个0 1分数规划问题(i取值为0/1是否选择 去优化目标数值)
//     发现值域在(0,1000]范围内 所以使用二分可能可以
//     发现整理后得到sum(f[i]-mid*w[i])为边权的图中是否有正环等价问题 所以可以用spfa求正环
//note:spfa可以方便求解正环  分数规划问题归结为选择优化问题，想办法变换形式找到等价问题
// d[t] + [val[t]-mid*w[i]](新权值)
/*
#include<iomanip>
const int N = 1010,M = 5010;
//浮点数比较精度在二分中通常设置为precision*1e-2
const double eps = 1e-4;
int n,m;
int h[N],e[M],w[M],ne[M],idx;
double d[N];
int q[N],cnt[N];
int val[N];
bool st[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}

bool check(double mid){
//spfa判断正环
    memset(d,0,sizeof d);
    memset(cnt,0,sizeof cnt);
    memset(st,0,sizeof st);
    int hh = 0,tt = 0;
    for(int i=1;i<=n;i++) q[tt++] = i,st[i] = true;
    while(hh!=tt){
        int t = q[hh++];
        if(hh==N) hh = 0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j] < d[t] + val[t]-mid*w[i]){
                d[j] = d[t] + val[t]-mid*w[i];//新边权
                cnt[j] = cnt[t] + 1;
                if(cnt[j]>=n) return true;
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}
int main(){
    cin>>n>>m;
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++)
        cin>>val[i];
    for(int i=0;i<m;i++){
        int a,b,c;
        cin>>a>>b>>c;
        add(a,b,c);
    }
    double l = 0,r = 1000;//左开右闭 数据保证有解 否则需要虚拟迭代次数 或者用double比较边界数值
    while(r-l>eps){//不能用fabs 需要严格大于小于判断
        double mid = (l+r)/2;
        if(check(mid)) l = mid;
        else r = mid;
    }
    cout<<fixed<<setprecision(2)<<l<<endl;
    return 0;
}
*/
//单词环 
//首先发现点太多 所以转化思维 将单词作为边 而两个字母组合作为点
//共有26*26点 1e5边
//问题转换为分数规划问题 只需要采用二分+正环判断即可
//不同于上题目的是：边权变成了w[i]-mid*val[t] 
//二分范围 (0,1000]
//复杂度：10*26*26*n 可能超过限制
//优化使用stack/k*m约束
/*
#include<iomanip>
#include<string>
const int N = 26*26+10,M = 1e5+10;
//浮点数比较精度在二分中通常设置为precision*1e-2
const double eps = 1e-4;
int n,m;
int h[N],e[M],w[M],ne[M],idx;
double d[N];
int q[N],cnt[N];
// int val[N];点权为1
bool st[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}

bool check(double mid){
//spfa判断正环
    memset(d,0,sizeof d);
    memset(cnt,0,sizeof cnt);
    memset(st,0,sizeof st);
    int hh = 0,tt = 0;
    for(int i=0;i<26*26;i++) q[tt++] = i,st[i] = true;
    int count = 0;//计数器优化
    while(hh!=tt){//tt==0
        // 使用stack循环栈
        // int t = q[hh++];
        int t = q[--tt];
        // if(hh==N) hh = 0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j] < d[t] + w[i]-mid){
                d[j] = d[t] + w[i]-mid;//新边权
                cnt[j] = cnt[t] + 1;
                //碰运气方法
                // if(++count>10000) return true;//通过经验值跳出 按照遍历过km
                if(cnt[j]>=N) return true;//小心判断点
                if(!st[j]){
                    q[tt++] = j;
                    // if(tt==N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return false;
}
int getnode(string s){
    return (s[0]-'a')*26 + (s[1]-'a');
}
int main(){
    while(cin>>n,n){
        memset(h,-1,sizeof h);
        idx = 0;
        string ss="";
        for(int i=0;i<n;i++){
            cin>>ss;
            if(ss.size()<2) continue; 
            int a = getnode(ss.substr(0,2)),b = getnode(ss.substr(ss.size()-2,2));
            add(a,b,ss.size());
        }
        double l = -1,r = 1000;//左开右闭 数据保证有解 否则需要虚拟迭代次数 或者用double比较边界数值
        while(r-l>eps){//不能用fabs 需要严格大于小于判断
            double mid = (l+r)/2;
            if(check(mid)) l = mid;
            else r = mid;
        }
        // cout<<check(0)<<endl;//没有环
        if(-l>eps) cout<<"No solution"<<endl; 
        else cout<<l<<endl;
    }
    return 0;
}
*/
