#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//炮兵阵地 状压dp 需要预处理出合法的状态以及状态转移
//需要存储两个维度的这状态
// int f[110][]
int n,m;
int f[110][70][70];
bool judge(int x){
    if(x&(x<<1) || x&(x<<2)) return false;
    return true;
}
int calc(int x){
    int res = 0;
    while(x){
        res += (x&1);
        x>>=1;
    }
    return res;
}
// int cnt = 0; 经测试周游60个可用状态
int st[70],cnt=0,nums[70];
void init(){
    for(int i=0;i<(1<<m);i++){
        if(judge(i)){
            st[cnt] = i;
            nums[cnt++] = calc(i);
        }
    }
}
bool check(int a,int b,int c){
    if(st[a]&st[b] || st[b]&st[c] || st[a]&st[c]) return false;
    return true; 
}
char g[110][15];
int org[110];
bool check2(int x,int row){
    if(row<=0) return true;
    if(st[x]&org[row]) return false;
    return true;
}
int main(){
    cin>>n>>m;
    init();
    for(int i=1;i<=n;i++) cin>>g[i];
    for(int i=1;i<=n;i++)
        for(int j=0;j<m;j++){
            if(g[i][j]=='H') org[i]|=(1<<j); 
        }   
    //dp
    memset(f,0,sizeof f);
    for(int i=0;i<cnt;i++)
        if(check2(i,1)) f[1][i][0] = nums[i];
    for(int i=2;i<=n+2;i++)
        for(int j=0;j<cnt;j++){
            if(!check2(j,i)) continue;
            for(int x=0;x<cnt;x++){
                if(!check2(x,i-1)) continue;
                if(st[j]&st[x]) continue;
                for(int y=0;y<cnt;y++){
                    if(!check2(y,i-2)) continue;
                    if(!check(j,x,y)) continue;
                    f[i][j][x] = max(f[i][j][x],f[i-1][x][y]+nums[j]); 
                }
            }
        }
    cout<<f[n+2][0][0]<<endl;
    return 0;
}