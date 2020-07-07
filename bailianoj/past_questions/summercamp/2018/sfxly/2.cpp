#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/*
//dp 表示 dp[i][j] 表示用了前i个火车 考虑前j堆客人 最大结果 具有最优子结构
//dp[i][j] = max(dp[i][j-1],dp[i-1][j-k]+sum[j]) sum[j]表示从j-k+1->j 
//为方便初始化 这里用的是至少前i个火车头 否则需要-0x3f初始化
//即背包问题 把k个一组人看作一个物品 
const int N = 5e4+10;
int nums[N];
int s[N];
int dp[4][N];
int n,k;
int main(){
    int T;
    cin>>T;
    while(T--){
        memset(dp,0,sizeof dp);
        cin>>n;
        for(int i=1;i<=n;i++) cin>>nums[i];
        cin>>k;
        int sum = 0;
        for(int i=1;i<=n;i++){
            sum+=nums[i];
            if(i==k) s[i] = sum;
            else if(i>k){
                sum -= nums[i-k];
                s[i] = sum;
            }
        }
        //初始 dp[0][i] = 0 dp[i][0]不存在 -0x3f
        for(int i=1;i<=3;i++)
            for(int j=k;j<=n;j++){
                dp[i][j] = max(dp[i][j-1],dp[i-1][j-k]+s[j]);
            }
        cout<<dp[3][n]<<endl;

    }
    return 0;
}
*/
/*
//贪心

const int N = 1010;
bool st[N];
int m,n;

int main(){
    int T = 0;
    while(cin>>m>>n,m||n){
        int num;
        memset(st,0,sizeof st);
        for(int i=0;i<n;i++){
            cin>>num;
            st[num] = true;
        }
        int pre = 0,ans = 0;
        for(int i=n*m;i>=1;i--){
            if(st[i]){
                if(pre==0) ans++;
                else    pre--;
            }else{
                pre++;
            }
        }
        cout<<"Case "<<++T<<": "<<ans<<endl;
    }
    return 0;
}
*/

//贪心 哈夫曼树
#include<queue>
int ans = 0;
int main(){
    int n,m,num;
    cin>>n;
    while(n--){
        priority_queue<int,vector<int>,greater<int>> q;
        ans = 0;
        cin>>m;
        for(int i=0;i<m;i++){
            cin>>num;
            q.push(num);
        }
        if(m==1){
            cout<<num<<endl;
            continue;
        }
        int v1,v2;
        while(q.size()>1){
            v1 = q.top(),q.pop();
            v2 = q.top(),q.pop();
            ans += (v1+v2);
            q.push(v1+v2);
        }
        cout<<ans<<endl;
    }
    return 0;
}