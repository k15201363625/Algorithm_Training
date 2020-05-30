#include<iostream>
#include<cstring>
#include<cstdio>
#include<vector>
#include<algorithm>
using namespace std;
//欧拉回路欧拉路径问题
/*
哥尼斯堡七桥问题（一笔画）
欧拉回路/路径定理：
对于无向图，所有边都是连通的
(1) 存在欧拉路径的充分必要条件：度数为奇数的点只能有0或2个
(2) 存在欧拉回路的充分必要条件：度数为奇数的点只能有0个
对于有向图，所有边都是连通的
(1) 存在欧拉路径的充分必要条件：要么所有点的出度均等于入度；要么除了两个点以外，其余所有点的出度等于入度，剩余的两个点：一个满足出度比入度多1（起点），另一个满足入度比出度多1（终点）
(2) 存在欧拉回路的充分必要条件：所有点的出度均等于入度

实现方式：dfs，在dfs的最后将当前遍历的节点加入队列中(判断过程中用边判重)
note：用边判重，时间复杂度可能会很高。可以在走过一条边之后就将这条边删去。在无向图中，由于建了双向边，两条边都要删掉。
在删边中有些技巧需要注意：具体看题目(涉及到通过&提升效率)
*/
//铲雪车
//无向图 满足连通性+所有点读书为偶数 所以有欧拉回路
//很多问题乍看是图论 实际上是直接可以计算得到
/*
#include<cmath>
int main(){
    double x1,y1,x2,y2;
    cin>>x1>>y1;
    double sum = 0;
    while(cin>>x1>>y1>>x2>>y2){
        double dx = (x2-x1);
        double dy = (y2-y1);
        sum += sqrt(dx*dx + dy*dy)*2;
    }
    int minutes = round(sum/1000/20*60);
    //注意转换为小时分钟输出技巧 
    //使用%02d控制整数前导0显示问题
    printf("%d:%02d\n",minutes/60,minutes%60);
    return 0;
}
*/
//欧拉回路问题
//由于可以重复经过一个点(dfs过程中) 
/*
所以删除一条边需要在上层的dfs以及下层dfs中都有效 否则会多次重复判断 
本题n 1e5 在多次重复判断情况下不可(即便已经有了used标记 也需要多次判断)
解决方案：
思路：使所有访问使用共同的变量(全局变量) 记录当前删边情况 
m1：采用dinic当前弧优化技巧 使用引用使全部都被修改
m2：采用全局head[i]修改head[i]实现真正删边 并且遍历更新中用i=head[u]作为每次forloop更新
使用邻接表存储关键优化代码：
    for(int &i=h[u];i!=-1;){
        int t;
        if(type==1) t = i/2+1;
        else t = i+1;
        
        int j = e[i];
        //先修改再遍历 否则死循环(没有used情况下)
        i = ne[i];
        dfs(j);
        //欧拉路径统计需要在觳觫的时候进行
        ans[++cnt] = t;
    }
*/

/*
const int N = 1e5+10,M = 4e5+10;
int h[N],e[M],ne[M],idx;
int din[N],dout[N];
bool used[N];//即便使用引用 可以省去？？ 
int type;
int ans[M],cnt=0;
int n,m;
//[1]如果数据范围小 只需要used删边更简单
//[2]稍大数据只需要保证子节点背后正确删边 只需要修改h
//[3]对于大数据量1e5需要用当前弧优化保证上层下层节点都被正确删边
void dfs(int u){
    //首先使用普通h[u]重新设置对于上层的i会继续检查 只对下层的i=h[u]有效删边
    //采用&i 保证下层删边之后上层有效被删边（下层改变了h[u]）
    //其次为了保证下层被删边 需要在dfs之前将i=ne[i]执行 所以改写forloop
    //如果采用m2 需要每次for最后i=head[u]相同效果
    for(int &i=h[u];i!=-1;){

        // if(used[i]){
        //     i = ne[i];
        //     continue;
        // }
        // used[i] = true;
        // if(type==1) used[i^1] = true;
        
        int t;
        if(type==1) t = i/2+1;
        else t = i+1;
        
        int j = e[i];
        //先修改再遍历 否则死循环(没有used情况下)
        i = ne[i];
        dfs(j);
        //欧拉路径统计需要在觳觫的时候进行
        ans[++cnt] = t;
    }
}
bool judge(){//无向图只需要单边加din dout
    for(int i=1;i<=n;i++)
        if(type==1){
            if(din[i]+dout[i]&1) return false;
        }else{
            if(din[i]!=dout[i]) return false;
        }
    return true;
}
*/

//骑马修栅栏 需要字典序输出欧拉路径
//note：虽然路径是到这村出的 但是不会改变一个性质：只要按照节点编号从小到大顺序搜索 最终ans逆序结果就是字典序最小欧拉路径
//数据规模小 可以直接用普通删边
//为了按照顺序搜索相邻节点 邻接矩阵存储更简单
//note:使用邻接矩阵存储删边不需要考虑那么多 不需要used标志直接设置即可 检查中也是依次检查(当然可以使用全局变量)
/*
const int N = 1100;
int g[N][N];
int ans[1100],cnt;
int d[N];
int n=500,m;
void dfs(int u){
    for(int i=1;i<=n;i++){
        if(g[u][i]){
            g[u][i] --;
            g[i][u] --;
            dfs(i);
        }
    }
    ans[cnt++] = u;
}
int main(){
    cin>>m;
    while(m--){
        int a,b;
        cin>>a>>b;
        g[a][b]++,g[b][a]++;
        d[a]++,d[b]++;
    }
    //保证字典序 从最开头探索
    int st = 1;
    //任意一个点结束 可能是欧拉回路/路径 所以可以没有节点度为奇数
    while(!d[st]) st++;//先找到一个有边的点
    for(int i=1;i<=n;i++){
        if(d[i]%2){
            st = i;
            break;
        }
    }
    dfs(st);
    for(int i=cnt-1;i>=0;i--) cout<<ans[i]<<endl;
    return 0;
}
*/
//单词游戏
//按照之前的思路 将单词看成边 而前缀/后缀字母看做点
//有向图
int g[27][27];
int din[27],dout[27];
bool st[27];
int n;
void dfs(int u){
    st[u] = true;
    for(int i=0;i<=25;i++)
        if(!st[i] && g[u][i])
            dfs(i);
}
int p[27];
int find(int x){
    if(x!=p[x]) p[x] = find(p[x]);
    return p[x];
}
int main(){
    int T;
    cin>>T;
    while(T--){
        int m;
        cin>>m;
        string str;
        //每次需要重置
        memset(st,0,sizeof st);
        memset(din,0,sizeof din),memset(dout,0,sizeof dout);
        memset(g,0,sizeof g);
        for(int i=0;i<=25;i++) p[i] = i;
        for(int i=0;i<m;i++){
            cin>>str;
            int len = str.size();
            int a = str[0]-'a',b = str[len-1]-'a';
            g[a][b]++;
            dout[a]++,din[b]++;
            //并查集方法
            p[find(a)] = find(b);
        }
        int x=0,y=0,start=-1;
        bool flag = true;
        //容许欧拉回路/欧拉路径
        for(int i=0;i<=25;i++){
            if(din[i]==dout[i]) continue;
            else if(din[i]-dout[i]==1) y++;
            else if(dout[i]-din[i]==1) x++,start=i;
            else{
                flag = false;
                break;
            }
        }
        if(x==1&&y==1) ;
        else if(x==0&&y==0) ;
        else flag = false;

        if(flag){//需要检验连通性
            // dfs(start);
            // for(int i=0;i<=25;i++){
            //     if(!st[i] && din[i]>=1){
            //         flag = false;
            //         break;
            //     }
            // }
            // 另一种方法
            int rep = -1;
            for(int i=0;i<=25;i++){
                if(din[i]||dout[i]){
                    if(rep==-1) rep = find(i);
                    else if(rep!=find(i)){
                        flag = false;
                        break;
                    }
                }
            }
        }


        //也可以用并查集检查连通性
        if(!flag)
            cout<<"The door cannot be opened."<<endl;
        else
            cout<<"Ordering is possible."<<endl;
    }
    return 0;
}