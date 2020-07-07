#include<iostream>
#include<cstring>
#include<algorithm>
#include<vector>
#include<set>
using namespace std;
/*
// typedef long long ll;
typedef int ll;
const int N = 1e6+10,M = 18;
// ll f[N][4][4];
ll f[2][4][4][M];
ll tmp[M];
int n;
void print(ll x[]){
    if(n<=36){
        int i = 15;
        while(x[i]==0) i--;
        for(;i>=0;i--) cout<<x[i];
        cout<<endl;
    }else{
        cout<<"......";
        for(int i=9;i>=0;i--) cout<<x[i];
        cout<<endl;
    }

}
inline void add(ll a[],ll b[],ll c[]){
    ll t = 0;
    memset(c,0,sizeof(ll)*M);
    for(int i=0;i<M;i++){
        t += a[i] + b[i];
        c[i] = t%10;
        t/=10;
    }
}
inline void add2(ll a[],ll b[]){
    ll t = 0;
    memset(tmp,0,sizeof tmp);
    for(int i=0;i<M;i++){
        t += a[i] + b[i];
        tmp[i] = t%10;
        t/=10;
    }
    memcpy(a,tmp,sizeof tmp);
}
void dp(){
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            // f[2%2][i][j] = 1;
            f[2%2][i][j][0] = 1;

    for(int i=3;i<=n;i++){
        // f[i%2][0][0] = f[(i-1)%2][1][0] + f[(i-1)%2][2][0];
        // f[i%2][1][1] = f[(i-1)%2][0][1] + f[(i-1)%2][2][1];
        // f[i%2][2][2] = f[(i-1)%2][0][2] + f[(i-1)%2][1][2];
        add(f[(i-1)%2][1][0],f[(i-1)%2][2][0],f[i%2][0][0]);
        add(f[(i-1)%2][0][1],f[(i-1)%2][2][1],f[i%2][1][1]);
        add(f[(i-1)%2][0][2],f[(i-1)%2][1][2],f[i%2][2][2]);

        for(int j=0;j<3;j++)
            for(int k=0;k<3;k++){
                if(j==k) continue;
                // f[i%2][j][k] = 0;
                memset(f[i%2][j][k],0,sizeof(ll)*M);
                for(int x=0;x<3;x++) 
                    // f[i%2][j][k] += f[(i-1)%2][x][j];
                    add2(f[i%2][j][k],f[(i-1)%2][x][j]);
            }
    }
}

int main(){
    cin>>n;
    dp();
    // ll res = 0;
    ll res[M];
    memset(res,0,sizeof res);
    for(int i=0;i<3;i++)
        for(int j=0;j<3;j++)
            // res += f[n%2][i][j];
            add2(res,f[n%2][i][j]);
    // cout<<res<<endl;
    print(res);
    return 0;
}
*/

/*
#include<unordered_map>
const int N = 1e6+10,M = N<<1;
int cnt = 0;
int a[N],nums[N];
int h[N],e[M],ne[M],idx = 0;
int n;
unordered_map<int,int> mp; 
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
void init(){
    memset(h,-1,sizeof h);
    idx = 0;
}
void dfs(int u,int fa){
    mp[a[u]]++;
    if(mp[a[u]]==1) nums[u] = nums[fa]+1;
    else nums[u] = nums[fa];
    for(int i=h[u];i!=-1;i=ne[i]){
        int v = e[i];
        if(v==fa) continue;
        dfs(v,u);
    }
    mp[a[u]]--;
}
int main(){
    cin>>n;
    int b,c;
    init();
    for(int i=0;i<n-1;i++){
        cin>>b>>c;
        add(b,c);
        add(c,b);
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    dfs(n,0);
    for(int i=1;i<=n;i++) cout<<nums[i]<<" ";
    cout<<endl;
    return 0;
}
*/
/*
问题描述
有n个数字，a[1],a[2],…,a[n]。有一个集合，刚开始集合为空。然后有一种操作每次向集合中加入一个数字或者删除一个数字。每次操作给出一个下标x(1 ≤ x ≤ n)，如果a[x]已经在集合中，那么就删除a[x],否则就加入a[x]。 问每次操作之后集合中互质的数字有多少对。 注意，集合中可以有重复的数字，两个数字不同当且仅当他们的下标不同。 比如a[1]=a[2]=1。那么经过两次操作1，2之后，集合之后存在两个1，有一对互质。

输入格式
第一行包含两个整数n 和 q。表示数字的种类和查询数目。

第二行有n个以空格分开的整数a[1],a[2],…,a[n],分别表示n个数字。

接下来q行，每行一个整数x，表示每次操作的下标。

输出格式
对于每一个查询，输出当前集合中互质的数字有多少对。
对于30%数据：1≤n≤100，1≤q≤1000
对于所有数据：1≤n≤100000， 1≤m≤100000，1≤a[i]≤500000
*/
//暴力
const int N = 1e5+10;
int n,q;
inline int gcd(int a,int b){
    if(b==0) return a;
    return gcd(b,a%b);
}
int nums[N];
bool st[N];
int calc(){
    int res = 0;
    for(int i=1;i<=n;i++){
        if(!st[i]) continue;
        for(int j=i+1;j<=n;j++){
            if(!st[j]) continue;
            if(gcd(nums[i],nums[j])==1)
                res++;
        }

    }
    return res;
}
int main(){
    cin>>n>>q;
    int num;
    for(int i=1;i<=n;i++){
        cin>>nums[i];
    }
    for(int i=0;i<q;i++){
        cin>>num;
        if(!st[num]) st[num]=true;
        else st[num] = false;
        cout<<calc()<<endl;
    }
    return 0;
}