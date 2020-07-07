#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 510;
int nums[N];
int f[N];
int n,k;
/*
f[i][j] 前i个位置已经插入了j个挡板最小的结果
f[i][j] = min(f[i-1][j-k]+change) 当k不可以为0
初始化 f[0][i] = (max-min)^2 f[i][j](i>j)不存在
*/
int dp(){
    // for(int i=0;i<=n-1;i++) f[i] = (nums[n]-nums[1])*(nums[n]-nums[1]);
    // int ans = f[0];
    int ans = (nums[n]-nums[1])*(nums[n]-nums[1]);
    if(k==1) return ans;
    for(int i=1;i<=n-1;i++){
        f[i] = (nums[i]-nums[1])*(nums[i]-nums[1]) + (nums[n]-nums[i+1])*(nums[n]-nums[i+1]);
        ans = min(ans,f[i]);
    }
    for(int i=2;i<=k-1;i++){
        for(int j=n-1;j>=i;j--){
            //保证f[j-1]一定不是f[0][j-1]
            f[j] = f[j-1] + (nums[n] - nums[j+1])*(nums[n]-nums[j+1]) - (nums[n]-nums[j])*(nums[n]-nums[j]);
            for(int x = 2;j-x>=i-1;x++){
                f[j] = min(f[j],f[j-x] + (nums[j]-nums[j-x+1])*(nums[j]-nums[j-x+1]) + (nums[n] - nums[j+1])*(nums[n]-nums[j+1]) - (nums[n]-nums[j-x+1])*(nums[n]-nums[j-x+1]));
            }
            cout<<i<<" "<<j<<" "<<f[j]<<endl;
            ans = min(ans,f[j]);
        }
    }
    return ans;
}
int main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++) cin>>nums[i];
    sort(nums+1,nums+n+1);
    cout<<dp()<<endl;
    return 0;
}