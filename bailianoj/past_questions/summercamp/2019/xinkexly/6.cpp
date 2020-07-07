#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//枚举 + bfs/dfs中的flood fill
int ney[6] = {-1,0,-1,1,0,1},nex[6] = {-1,-1,0,0,1,1};
int cnt,flag;
int n,c;
int g[12][12];
bool st[12][12];
void dfs(int x,int y){
    st[x][y] = true;
    cnt++;
    for(int i=0;i<6;i++){
        int nx = nex[i] + x,ny = ney[i] + y;
        if(nx<1 || nx>n || ny<1 || ny>nx || st[nx][ny]) continue;

        if(g[nx][ny]==0){
            flag = 0;
        }else if(g[nx][ny]==g[x][y]){
            dfs(nx,ny);
        }
    }
}
int getans(){
    memset(st,0,sizeof st);
    int res = 0;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=i;j++){
            if(g[i][j]==0) continue;
            if(!st[i][j]){
                cnt = 0,flag = 1;
                dfs(i,j);
                if(g[i][j]==c){
                    res -= flag * cnt;
                }else{
                    res += flag * cnt;
                }
            }
        }
    return res;
}
int main(){
    while(cin>>n>>c,n||c){
        for(int i=1;i<=n;i++)
            for(int j=1;j<=i;j++)
                cin>>g[i][j];
        int ans = -0x3f3f3f3f;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=i;j++){
                if(g[i][j]==0){
                    g[i][j] = c;
                    ans = max(ans,getans());
                    g[i][j] = 0;
                }
            }
        cout<<ans<<endl;
    }
    return 0;
}