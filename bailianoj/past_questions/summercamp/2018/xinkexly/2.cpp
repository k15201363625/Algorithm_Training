#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 55;
char g[N][N];
//双重dfs 注意状态标记 以及外层dfs设置
//需要内层dfs正常编写但是恢复状态 外层dfs不仅调用内层dfs 同时之后执行自身dfs才行 注意顺序
//这里为了方便 不用vis 二十直接修改g *->.  X->*->.
int w,h;
int nums[N],cnt = 0;
int nex[4] = {-1,0,1,0},ney[4] = {0,1,0,-1};
void ddfs(int x,int y){
    g[x][y] = '*';
    for(int i=0;i<4;i++){
        int nx = nex[i]+x,ny = ney[i] + y;
        if(nx<1 || nx>h || ny<1 || ny>w || g[nx][ny]!='X') 
            continue;
        ddfs(nx,ny);
    }

}
void dfs(int x,int y){
    g[x][y] = '.';
    for(int i=0;i<4;i++){
        int nx = nex[i]+x,ny = ney[i]+y;
        if(nx<1 || nx>h || ny<1 || ny>w || g[nx][ny]=='.')
            continue;
        if(g[nx][ny]=='X'){
            ddfs(nx,ny);
            nums[cnt]++;
        }
        //注意顺序不能少
        dfs(nx,ny);
    }
}
int main(){
    int T = 0;
    while(cin>>w>>h,w||h){
        cnt = 0;
        memset(nums,0,sizeof nums);
        for(int i=1;i<=h;i++) cin>>(g[i]+1);
        for(int i=1;i<=h;i++)
            for(int j=1;j<=w;j++)
                if(g[i][j]=='*'){
                    dfs(i,j);
                    cnt++;
                }
        cout<<"Throw"<<" "<<++T<<endl;
        sort(nums,nums+cnt);
        for(int i=0;i<cnt;i++) cout<<nums[i]<<" ";
        cout<<endl<<endl;
    }
    return 0;
}