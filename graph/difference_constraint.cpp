#include<iostream>
#include<cstring>
#include<queue>
#include<cstdio>
#include<algorithm>
using namespace std;
//差分约束
/*
(1)求不等式组可行解：
步骤：
先将每个不等式xi<=xj+c转化成一条从xj走到xi，长度为ck的一条边
找一个超级源点，使得该源点一定可以遍历到所有边(**) 否则未必是可行解
从源点求一遍单源最短路
note:>= 则转换为求解最长路 (本质是三角不等式约束下如果是>=用最长路)
结果：
如果存在负环，则原不等式组一定无解
如果没有负环，则dist[i]就是原不等式组的一个可行解
note:>= 则转变为正环判断
意义：
最短路--从1到i最小值 对应不等式链化简后最小的c
最长路--从1到i的最大值 对应不等式链化简后最大的c
(2)求解不等式组在给定一组初始范围条件后的最大值/最小值(针对每个变量本身的)
结论/步骤：
如果求的是最小值，则应该求最长路；如果求的是最大值，则应该求最短路。
note：看似与直觉相违背
证明：
以求xi的最大值为例：所有从xi出发，构成的不等式链xi<=xj+c1<=xk+c2+c1<=...<=c1+c2+...+ck
                所计算出的上界，最终xi的最大值等于所有上界的最小值，即表示所有c的最小值，需要最短路
同理，若是求最大值，则是求所有下界的最大值，即表示所有c的最大值，即表示最长路
问题/关键点2：
如何转化xi<=c，其中c是一个常数，这类的不等式
方法：
建立一个超级源点，0，然后建立0->xi，长度是c的边即可
这时候无论对于求解最大值还是求解最小值都有了一个超级源点 求解某一个变量最值只需要以这个超级源点作为起点跑一次最短/长路即可
*/
//note差分约束有时候可以用并查集/传递闭包解决(因为而这也有解决简单不等式的能力) 但是看到不等式组尤其复杂的或者多个关系情况下优先用差分约束
//糖果
//由于差分约束只能解决不等式问题 对于等式问题 采用等式变成不等式
//发现隐含的绝对条件：
//x>=1 (x>=x0+1)
//边数组大小计算：3n
//由于边点数目较大 可能在spfa tle  所以用栈优化(队列不行就用栈 尤其在差分约束这种存在负环判断的问题中)
//目标：求解最小数值 即求解最长路 应该全用>=关系
/*
const int N = 1e5+10,M = 3*N;
int h[N],e[M],ne[M],w[M],idx;
long long d[N];
int q[N],cnt[N];
bool st[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
int n,m;
bool spfa(){
//同时判断正环 采用栈更快 0必然可以作为超级原点
    memset(st,0,sizeof st);
    memset(cnt,0,sizeof cnt);
    memset(d,-0x3f,sizeof d);//需要最长路
    int hh = 0,tt = 0;
    q[tt++] = 0,st[0] = true,d[0] = 0;
    while(tt!=0){
        int t = q[--tt];
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]<d[t]+w[i]){
                d[j] = d[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j]>=n+1) return false;
                if(!st[j]) st[j] = true,q[tt++] = j;
            }
        }
    }
    return true;
}
int main(){
    cin>>n>>m;
    int x,a,b;
    memset(h,-1,sizeof h);
    for(int i=1;i<=n;i++) add(0,i,1);
    while(m--){
        cin>>x>>a>>b;
        if(x==1) add(a,b,0),add(b,a,0);
        else if(x==2) add(a,b,1);
        else if(x==3) add(b,a,0);
        else if(x==4) add(b,a,1);
        else add(a,b,0);
    }
    if(!spfa()) cout<<-1<<endl;
    else{
        long long res = 0;
        for(int i=1;i<=n;i++) res+=d[i];
        cout<<res<<endl;
    }
    return 0;
}
*/

//差分约束
//难点1：难在将问题转换成不等式组 之后通过不等式组见图过程不难
//难点2：找全隐含的不等式关系
//区间intervals
//此问题每个选择方案对应着一个01序列 而为了快速表示区间点数目 可以用前缀和
//综上：采用si表示每个点的数字安排情况 每个区间信息表示为一个不等式关系 而彼此之间的不等式关系要小心 最后是隐含的s0=0不等式关系
//发现存在超级节点s0【前缀和处理方便将0-50000->1-50001】 而这样保证了0可以作为茶集结点
//为了得到最小值min s50001 可以采用边界条件--s0==0
/*
const int N = 5e4+10,M = 3*N;
int h[N],e[M],ne[M],w[M],idx;
int d[N];//必然有解
int q[N];
bool st[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
int n,m;
void spfa(){
//同时判断正环 采用栈更快 0必然可以作为超级原点
    memset(st,0,sizeof st);
    memset(d,-0x3f,sizeof d);//需要最长路
    int hh = 0,tt = 0;
    q[tt++] = 0,st[0] = true,d[0] = 0;
    // while(tt!=0){
    //     int t = q[--tt];
    //     st[t] = false;
    //     for(int i=h[t];i!=-1;i=ne[i]){
    //         int j = e[i];
    //         if(d[j]<d[t]+w[i]){
    //             d[j] = d[t] + w[i];
    //             if(!st[j]) st[j] = true,q[tt++] = j;
    //         }
    //     }
    // }
    //普通情况下使用队列明显更快
    while(tt!=hh){
        int t = q[hh++];
        if(hh==N) hh = 0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]<d[t]+w[i]){
                d[j] = d[t] + w[i];
                if(!st[j]){
                    st[j] = true,q[tt++] = j;
                    if(tt==N) tt=0;
                }
            }
        }
    }
}
int main(){
    int T;
    cin>>T;
    while(T--){
        cin>>n;
        int a,b,c;
        idx = 0;
        memset(h,-1,sizeof h);
        while(n--){
            cin>>a>>b>>c;
            //将之移位 方便处理 原本范围从0开始
            a++,b++;
            add(a-1,b,c);
        }
        // a++ b++ 50000++
        for(int i=1;i<=50001;i++)
            add(i-1,i,0),add(i,i-1,-1);
        //0可以作为超级节点 由于s0==0 只需要将0作为虚拟节点 开始求最长路
        spfa();
        cout<<d[50001]<<endl;
    }
    return 0;
}
*/

//奶牛排队 排队布局 Layout
//明显差分约束  但是需要小心xi<xi+1条件 
//            小心需要两次spfa  第一次由于未必联通 需要使用虚拟节点 但是不用真的建立 只需要全部加入队列
//              第二次只需要从1开始 设置x1=0尝试spfa 如果有二者不联通(d==inf) 则表没有约束 距离可以无限大
/*
const int N = 1e3+10;
const int M = 2e4+1e3+20;
int h[N],e[M],ne[M],w[M],idx;
int d[N],cnt[N];
int q[N];
bool st[N];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
int n,m1,m2;
bool spfa(int rt=0){
    memset(st,0,sizeof st);
    memset(d,0x3f,sizeof d);//最短路的时候需要用到
    memset(cnt,0,sizeof cnt);
    int hh = 0,tt = 0;
    if(rt==0){
        for(int i=1;i<=n;i++){
            q[tt++] = i;
            st[i] = true;
        }
    }else if(rt==1){
        q[tt++] = 1;
        d[1] = 0;
        st[1] = true;
    }
    while(hh!=tt){
        int t = q[hh++];
        if(hh==N) hh=0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]>d[t]+w[i]){
                d[j] = d[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j]==n) return false;
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return true;
}
int main(){
    cin>>n>>m1>>m2;
    memset(h,-1,sizeof h),idx = 0;
    //如果有了这个约束条件 
    //for(int i=1;i<n;i++) add(i+1,i,0); 
    //并需要在下面if(a>b) swap(a,b); 保证全体有序性
    //否则相距l需要表示称两个条件并且是或关系 并非经典差分约束问题 通过强制有序性 保证每个条件变成唯一的不等式关系
    for(int i=1;i<n;i++) add(i+1,i,0); 
    int a,b,c;
    while(m1--){
        cin>>a>>b>>c;
        if(a>b) swap(a,b);
        add(a,b,c);
    }
    while(m2--){
        cin>>a>>b>>c;
        if(a>b) swap(a,b);
        add(b,a,-c);
    }
    if(!spfa()) cout<<-1<<endl;
    else{
        spfa(1);
        if(d[n]==0x3f3f3f3f) cout<<-2<<endl;
        else cout<<d[n]<<endl;
    }
    return 0;
}
*/

//雇佣收银员
//关键：建图难点
/*
1 统计num[i] 从而得到隐含约束
2 利用前缀和 这时将0-23-> 1-24更方便处理 同时有了前缀情况下0这个天然超级节点
3 对于i>=8 情况简单 但是对于i<7 情况需要特殊考虑 变成si+s24-si+16>=ri
4 难点 对于非二元差分约束关系可以使用前缀(最常见) 但是还可以采用枚举 即把一个数值看成常数 枚举数值 并且这时候3元变成二元不等关系
    note:表示相等关系只需要与超级节点两条边即可
    note:注意枚举顺序 由于枚举量可以是目标量 所以可以枚举到有解的时候就退出 并且此时就是最佳结果 
*/

const int N = 25;
const int M = 25*3+10;
int h[N],e[M],ne[M],w[M],idx;
int d[N],cnt[N];
int q[N];
bool st[N];
int R[25],num[25];
void add(int a,int b,int c){
    e[idx] = b,ne[idx] = h[a],w[idx] = c,h[a] = idx++;
}
int n;
bool spfa(){
    memset(st,0,sizeof st);
    memset(d,-0x3f,sizeof d);
    memset(cnt,0,sizeof cnt);  
    int hh = 0,tt = 0;//0是超级源节点
    q[tt++] = 0,st[0] = true,d[0] = 0;//25个点
    while(hh!=tt){
        int t = q[hh++];
        if(hh==N) hh=0;
        st[t] = false;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(d[j]<d[t]+w[i]){
                d[j] = d[t] + w[i];
                cnt[j] = cnt[t] + 1;
                if(cnt[j]>=25) return false;
                if(!st[j]){
                    q[tt++] = j;
                    if(tt==N) tt = 0;
                    st[j] = true;
                }
            }
        }
    }
    return true;
}
int main(){
    int T;
    cin>>T;
    while(T--){
        for(int i=1;i<=24;i++) cin>>R[i];
        cin>>n;
        int x;
        memset(num,0,sizeof num);//千万小心不要忘记
        while(n--){
            cin>>x;
            num[x+1]++;
        }
        //下次重新加边不对 只能重新加一次边 因为h e ne信息需要改变
        // memset(h,-1,sizeof h),idx = 0;
        // //建图
        // for(int i=1;i<=24;i++) add(i-1,i,0),add(i,i-1,-num[i]);
        // for(int i=8;i<=24;i++) add(i-8,i,R[i]);
        // //枚举s24 并且判断是否合法 也可以二分 满足二分性质
        // //24范围在
        // bool success = false;
        // for(int i=0;i<=1000;i++){
        //     //s24=i
        //     for(int i=1;i<8;i++) add(i+16,i,R[i]-i);//每次会重置
        //     //表示限定s24数值
        //     add(24,0,-i),add(0,24,i);
        //     if(spfa()) {
        //         success = true;
        //         break;
        //     }
        //     // idx -= 9;
        // }
                // memset(h,-1,sizeof h),idx = 0;
        //枚举s24 并且判断是否合法 也可以二分 满足二分性质
        bool success = false;;
        for(int c=0;c<=1000;c++){
            //建图
            memset(h,-1,sizeof h),idx = 0;
            for(int i=1;i<=24;i++) add(i-1,i,0),add(i,i-1,-num[i]);
            for(int i=8;i<=24;i++) add(i-8,i,R[i]);
            //s24=i
            for(int i=1;i<8;i++) add(i+16,i,R[i]-c);//每次会重置
            //表示限定s24数值
            add(24,0,-c),add(0,24,c);
            if(spfa()) {
                success = true;
                break;
            }
        }
        if(success) cout<<d[24]<<endl;//==i
        else cout<<"No Solution"<<endl;
    }
    return 0;
}