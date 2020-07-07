#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
//广搜
//基本广搜
//floodfill求连通块数目
//最短路模型(对于权值全部相同/全部为1)
//多个等效起点 使用多路bfs 即将起点全部压入队列开始bfs
//广搜状态表示技巧 本质也是状态转移 构建合法状态树
//双端队列广搜 解决路径权值为0 1情况下的最短路不需要dj / spfa 

//note:广搜关键性质 任何时刻队列中元素具有单调性 两端性
//     即任何时刻队列中元素只会有两个d 并且满足单调性
//     借助这个性质保证了最短性质 以及双端广搜操作正确性


//电路维修
//双端队列广搜解决01最短路问题
//同dij  入队可能多次 但是出队更新只有一次（出队多次 有效更新只有一次 所以需要额外st）第一次出队为结果
//对于0路径插到头 1路径插到尾 保证了单调性 两端性0 1
//节点可能多次入队 但只有第一次出队是最短并且扩展
//复杂度：一个节点最多扩展一次 一次最多扩展n个节点 所以最多复杂度O(N^2)---O(N+E)
//本题：抽象成对顶角点会有边0/1 非对顶角点没有边 直接检查是否可以连通 并且求最短路
//     (n+m)&1 == 1表示不连通 对顶角如果有当前线路连接cost=0反之为1
const int N = 510;
char g[N][N];
bool st[N][N];
int dis[N][N];
int n,m;
//格点索引
int nx[4]={-1,-1,1,1},ny[4]={-1,1,1,-1};
//电线索引
int linex[4]={-1,-1,0,0},liney[4] = {-1,0,0,-1}; 
string str = "\\/\\/";

void bfs(){
    deque<pair<int,int>> q;
    q.push_back({0,0});
    dis[0][0] = 0;
    while(!q.empty()){
        pair<int,int> f = q.front();
        int x = f.first,y = f.second;
        q.pop_front();
        if(x==n && y==m) return;//提前返回
        if(st[x][y]) continue;//每个节点只会出队一次 并且拓展一次
        st[x][y] = true;
        for(int i=0;i<4;i++){
            int nex = x+nx[i],ney = y+ny[i];
            if(nex<0 || nex>n || ney<0 || ney>m) continue;
            int lx = x+linex[i],ly = y+liney[i];
            int w = (g[lx][ly]!=str[i]);
            if(dis[nex][ney]>dis[x][y]+w){
                dis[nex][ney] = dis[x][y]+w;
                if(w==0) q.push_front({nex,ney});
                else q.push_back({nex,ney});
            }
        }
    }
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++)
        cin>>g[i];
    if((n+m)&1) cout<<"NO SOLUTION"<<endl;
    else{
        //必须初始化
        memset(dis,0x3f,sizeof dis);
        bfs();
        cout<<dis[n][m]<<endl;
    }
    return 0;
}