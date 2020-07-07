#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
/*
int nums[3010];
int main(){
    int n;
    int last = 0;
    int tmp;
    cin>>n;
    cin>>last;
    for(int i=0;i<n-1;i++){
        cin>>tmp;
        nums[i] = abs(tmp-last);
        last = tmp;
    } 
    sort(nums,nums+n-1);
    bool flag = true;
    for(int i=0;i<n-1;i++) 
        if(nums[i]!=(i+1)){
            flag = false;
            break;
        } 
    if(flag) cout<<"Jolly"<<endl;
    else cout<<"Not jolly"<<endl;
    return 0;
}
*/
//bfs
/*
char g[45][45];
int d[45][45];
bool st[45][45];
int r,c;
int nex[4] = {-1,0,1,0},ney[4] = {0,1,0,-1};
int bfs(){
    queue<pair<int,int>> q;
    q.push({1,1});
    d[1][1] = 0,st[1][1] = true;
    while(q.size()){
        pair<int,int> top = q.front();
        q.pop();
        int x = top.first,y = top.second;
        if(x==r && y==c) break;
        for(int i=0;i<4;i++){
            int nx = x+nex[i],ny = y+ney[i];
            if(nx<1 || nx>r || ny<1 || ny>c || g[nx][ny]=='#' || st[nx][ny]) continue;
            st[nx][ny] = true,d[nx][ny] = d[x][y] + 1;
            q.push({nx,ny});
        }
    }
    return d[r][c]+1;
}
int main(){
    cin>>r>>c;
    for(int i=1;i<=r;i++) cin>>g[i];
    cout<<bfs()<<endl;
    return 0;
}
*/

//最大上升子序列
const int N = 1010;
int f[N],nums[N];
int n;
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>nums[i];
    memset(f,0,sizeof f);
    f[1] = nums[1];
    int ans = f[1];
    for(int i=2;i<=n;i++){
        for(int j=1;j<=i;j++){
            if(nums[j]<nums[i]){
                f[i] = max(f[i],f[j]+nums[i]);
            }
        }
        //可以采用树状数组优化 如果是lis还可以用贪心+二分 nlogn
        //但是由于具有性质要求 不能单纯使用单调栈
        ans = max(ans,f[i]);
    }
    cout<<ans<<endl;
    return 0;
}