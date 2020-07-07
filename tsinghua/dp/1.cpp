#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//区间/环形dp
/*
const int N = 210;
int f[N][N],g[N][N];
int num[N*2],sum[N*2];
int n;
//也可以用f[i][j]表示左右边界
void dp(){
    //区间长度递增
    memset(f,-0x3f,sizeof f);
    memset(g,0x3f,sizeof g);
    //小心求解范围
    for(int i=1;i<=n*2;i++) f[1][i] = g[1][i] = 0;
    for(int len=2;len<=n;len++)
        for(int i=1;i+len-1<=2*n;i++){
            int ss = sum[i+len-1] - sum[i-1];
            for(int l=1;l<len;l++){
                f[len][i] = max(f[len][i],f[l][i]+f[len-l][i+l]+ss);
                g[len][i] = min(g[len][i],g[l][i]+g[len-l][i+l]+ss);
            }
        }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>num[i],num[n+i]=num[i];
    for(int i=1;i<=2*n;i++) sum[i] = sum[i-1]+num[i];
    dp();
    int res = -0x3f3f3f3f,res2 = 0x3f3f3f3f;
    for(int i=1;i<=n;i++) res = max(res,f[n][i]),res2 = min(res2,g[n][i]);
    cout<<res2<<endl<<res<<endl;
    return 0;
}
*/
/*
const int N = 210;
int f[N][N];
int num[N];
int n;
void dp(){
    for(int i=1;i<=n*2;i++) f[i][i] = 0;
    for(int len=2;len<=n;len++)
        for(int i=1;i+len-1<=n*2;i++){
            int j = i + len - 1;
            for(int k=i;k<j;k++){
                f[i][j] = max(f[i][j],f[i][k]+f[k+1][j]+num[i]*num[k+1]*num[j+1]);
            }
        }
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>num[i],num[n+i] = num[i];
    num[2*n+1] = num[1];
    dp();
    int res = 0;
    for(int i=1;i<=n;i++) res = max(res,f[i][i+n-1]);
    cout<<res<<endl;
    return 0;
}
*/
//需要用到高精度存储 为了运算不溢出 使用longlong 
//区间dp
/*
typedef long long ll;
const int N = 55,M = 35;
ll f[N][N][M],w[N],tmp[M],c[M],res[M];
void print(ll a[]){
    int st = M - 1;
    while(st && a[st]==0) st--;
    for(int i=st;i>=0;i--)
        cout<<a[i];
    cout<<endl;
}
void add(ll a[],ll b[]){
    memset(tmp,0,sizeof tmp);
    ll t = 0;
    for(int i=0;i<M;i++){
        t += a[i] + b[i];
        tmp[i] = t%10;
        t/=10;
    }
    memcpy(a,tmp,sizeof tmp);
}
void mul(ll a[],ll b){
    memset(tmp,0,sizeof tmp);
    ll t = 0;
    for(int i=0;i<M;i++){
        t += a[i]*b;
        tmp[i] = t%10;
        t/=10;
    }
    memcpy(a,tmp,sizeof tmp);
}
bool cmp(ll a[],ll b[]){
    for(int i=M-1;i>=0;i--){
        if(a[i]!=b[i]) return a[i]<b[i];
    }
    return false;
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=n;i++) cin>>w[i];
    for(int len=3;len<=n;len++)
        for(int i=1;i+len-1<=n;i++){
            int j = i+len-1;
            f[i][j][M-1] = 1;//无穷大
            for(int k=i+1;k<j;k++){
                memset(c,0,sizeof c);
                c[0] = w[i];
                mul(c,w[j]);
                mul(c,w[k]);
                add(c,f[i][k]);
                add(c,f[k][j]);
                if(cmp(c,f[i][j])) memcpy(f[i][j],c,sizeof c); 
            }
        }
    print(f[1][n]);
    return 0;
}
*/
/*
const int N = 110;
int f[N][N];
char str[N];
int n;
void dp(){
    memset(f,0x3f,sizeof f);
    for(int i=1;i<=n;i++) f[i][i] = 1;
    for(int len=2;len<=n;len++)
        for(int i=1;i+len-1<=n;i++){
            int j = i+len-1;
            if((str[i]=='[' && str[j]==']') || (str[i]=='(')&&(str[j]==')')){
                if(i+1<=j-1)  f[i][j] = min(f[i][j],f[i+1][j-1]);
                else f[i][j] = 0;
            }
            for(int k=i;k<j;k++){
                f[i][j] = min(f[i][j],f[i][k]+f[k+1][j]);
            }
        }
}
int main(){
    cin>>(str+1);
    n = strlen(str+1);
    dp();
    cout<<f[1][n]<<endl;
    return 0;
}
*/
/*
#include<queue>
const int N = 310;
typedef long long ll;
ll f[N][N];
int p[N][N];
ll a[N];
bool st[N];
int n;
//要求按照bfs遍历

// void getpath(int l,int r){
//     if(l>=r) return;
//     cout<<p[l][r]<<" ";
//     getpath(l,p[l][r]);
//     getpath(p[l][r]+1,r); 
// }
void getpath(int l,int r){
    queue<pair<int,int>> q;
    q.push({l,r});
    while(q.size()){
        pair<int,int> t = q.front();
        q.pop();
        int point = p[t.first][t.second];
        cout<<point<<" ";
        if(t.first<point) q.push({t.first,point});
        if(point+1<t.second) q.push({point+1,t.second});
    }
    cout<<endl;
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    memset(f,0,sizeof f);
    for(int i=1;i<=n;i++) f[i][i] = 0;
    for(int len=2;len<=n;len++)
        for(int i=1;i+len-1<=n;i++){
            int j = i+len-1;
            for(int k=i;k<j;k++){
                ll tmp = f[i][k]+f[k+1][j]+a[k]*(a[i]+a[j]);
                if(tmp>f[i][j]){
                    f[i][j] = tmp;
                    p[i][j] = k;
                }
            }
        }
    cout<<f[1][n]<<endl;
    getpath(1,n);
    return 0;
}
*/

/*
//需要借助高精度
typedef long long ll;
const int N = 100;
const int M = 30;
// ll f[N][N];
// ll nums[N][N];
// int n,m;
// ll pow2[N];
ll f[N][N][M];
ll nums[N][N];
int n,m;
ll pow2[N][M];
ll tmp[M],c[M],res[M];
void print(ll a[]){
    int st = M - 1;
    while(st && a[st]==0) st--;
    for(int i=st;i>=0;i--)
        cout<<a[i];
    cout<<endl;
}
void add(ll a[],ll b[]){
    memset(tmp,0,sizeof tmp);
    ll t = 0;
    for(int i=0;i<M;i++){
        t += a[i] + b[i];
        tmp[i] = t%10;
        t/=10;
    }
    memcpy(a,tmp,sizeof tmp);
}
void mul(ll a[],ll b){
    memset(tmp,0,sizeof tmp);
    ll t = 0;
    for(int i=0;i<M;i++){
        t += a[i]*b;
        tmp[i] = t%10;
        t/=10;
    }
    memcpy(a,tmp,sizeof tmp);
}
bool cmp(ll a[],ll b[]){
    for(int i=M-1;i>=0;i--){
        if(a[i]!=b[i]) return a[i]<b[i];
    }
    return false;
}
void dp(int n){
    // for(int i=1;i<=m;i++) f[i][i] = nums[n][i]*pow2[m];
    // for(int len=2;len<=m;len++)
    //     for(int i=1;i+len-1<=m;i++){
    //         int j = i+len-1;
    //         f[i][j] = max(f[i][j-1]+nums[n][j]*pow2[m-len+1],f[i+1][j]+nums[n][i]*pow2[m-len+1]);
    //     }
    // return f[1][m];
    static ll t1[M],t2[M];
    memset(f,0,sizeof f);
    for(int i=1;i<=m;i++){
        for(int j=0;j<m;j++) f[i][i][j] = pow2[m][j];
        mul(f[i][i],nums[n][i]);
    }
    for(int len=2;len<=m;len++)
        for(int i=1;i+len-1<=m;i++){
            int j = i+len-1;
            memset(t1,0,sizeof t1);
            memset(t2,0,sizeof t2);
            for(int x=0;x<M;x++) t1[x] = pow2[m-len+1][x],t2[x] = pow2[m-len+1][x];
            mul(t1,nums[n][j]);
            add(t1,f[i][j-1]);
            mul(t2,nums[n][i]);
            add(t2,f[i+1][j]);
            if(cmp(t1,t2)) for(int x=0;x<M;x++) f[i][j][x] = t2[x];
            else for(int x=0;x<M;x++) f[i][j][x] = t1[x];
        }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            cin>>nums[i][j];
    
    memset(c,0,sizeof c);
    c[0] = 1;
    for(int i=1;i<=m;i++){
        mul(c,2);
        for(int j=0;j<M;j++) pow2[i][j] = c[j];
    }
    memset(res,0,sizeof res);
    for(int i=1;i<=n;i++){
        dp(i);
        add(res,f[1][m]);
    }
    print(res);
    return 0;
}
*/
typedef long long ll;
const int N = 40;
ll a[N];
ll f[N][N],path[N][N];
int n = 0;
int dp(){
    for(int i=1;i<=n;i++) f[i][i] = a[i],path[i][i] = i;
    for(int len=2;len<=n;len++)
        for(int i=1;i+len-1<=n;i++){
            int j = i+len-1;
            for(int k=i;k<=j;k++){
                ll val = a[k],lv,rv;
                if(i==k) lv = 1;
                else lv = f[i][k-1];
                if(k==j) rv = 1;
                else rv = f[k+1][j];
                val += (lv*rv);
                if(val>f[i][j]){
                    f[i][j] = val;
                    path[i][j] = k;
                } 
            }
        }
    return f[1][n];
}
void preorder(int l,int r){
    if(l>r) return;  
    int mid = path[l][r];
    cout<<mid<<" ";
    preorder(l,mid-1),preorder(mid+1,r);
}
int main(){
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    cout<<dp()<<endl;
    preorder(1,n);
    return 0;
}
