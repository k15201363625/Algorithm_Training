#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/*
const int N = 610;
int nums[N];
int n;
int res = 0;
int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>nums[i];
    sort(nums,nums+n);
    for(int i=0;i<n-1;i++)
        for(int j=i+1;j<n;j++)
            if(gcd(nums[i],nums[j])==1) res++;
    cout<<res<<endl;
    return 0;
}
*/
/*
//可以用kmp
const int N = 510;
char s[N],p[10];
int ne[10];
int n;
bool st[N];
void getnext(){
    memset(ne,0,sizeof ne);
    for(int i=2,j=0;i<=n;i++){
        while(j && p[j+1]!=p[i]) j = ne[j];
        if(p[j+1]==p[i]) j++;
        ne[i] = j;
    }
}
int match(){
    int ans = 0;
    for(int i=1,j = 0;i<=strlen(s+1);i++){
        while(j && p[j+1]!=s[i]) j = ne[j];
        if(p[j+1]==s[i]) j++;
        if(j==n){
            ans++;
            st[i-n+1] = true;
            j = ne[j];
        }
    }
    return ans;
}
int res[N];
int cnt = 0,nowmax = 0;
int main(){
    cin>>n;
    cin>>(s+1);
    p[n+1] = '\0';
    for(int i=1;i+n-1<=strlen(s+1);i++){
        if(st[i]) continue;//避免重复
        for(int j=1;j<=n;j++){
            p[j] = s[i+j-1];
        }
        getnext();
        int times = match();
        if(times>nowmax){
            nowmax = times;
            cnt = 0;
            res[cnt++] = i;
        }else if(times==nowmax){
            res[cnt++] = i;
        }
    }
    if(nowmax<=1) cout<<"NO"<<endl;
    else{
        cout<<nowmax<<endl;
        for(int i=0;i<cnt;i++){
            int j = res[i];
            for(int k=0;k<n;k++)
                cout<<s[j+k];
            cout<<endl;
        }
    }
    return 0;
}
*/
/*
const int N = 90;
char str[N];
int cnt[27];
char res[330][55];
int main(){
    memset(cnt,0,sizeof cnt);
    for(int i=0;i<4;i++){
        cin.getline(str,N);
        for(int i=0;i<strlen(str);i++){
            if(str[i]>='A' && str[i]<='Z') cnt[str[i]-'A']++;
        } 
    } 
    int maxn = 0;
    for(int i=0;i<26;i++){
        maxn = max(maxn,cnt[i]);
    }
    for(int i=0;i<maxn;i++){
        for(int j=0;j<=50;j++) res[i][j] = ' ';
        res[i][51] = '\0';
    }
    for(int i=0;i<26;i++) res[maxn][i*2] = 'A'+i,res[maxn][i*2+1] = ' ';
    res[maxn][51] = '\0';
    for(int i=0;i<26;i++){
        int j = maxn-1;
        for(int k=0;k<cnt[i];k++)
            res[j-k][i*2] = '*'; 
    }
    for(int i=0;i<=maxn;i++) cout<<res[i]<<endl;
    return 0;
}
*/
/*
//最小生成树
const int N = 60,M = 10000;
int p[N];
int n,m;

int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
struct Edge{
    int a,b,v;
    bool operator<(const Edge & o)const{
        return v<o.v;
    }
}edges[M];

int kruskal(){
    int res = 0;
    sort(edges,edges+m);
    for(int i=0;i<m;i++){
        int a = edges[i].a,b = edges[i].b,v = edges[i].v;
        if(find(a)!=find(b)){
            p[p[a]] = p[b];
            res += v;
        }
    }
    return res;
}
int main(){
    while(cin>>n,n){
        for(int i=1;i<=n;i++) p[i] = i;
        cin>>m;
        int a,b,v;
        for(int i=0;i<m;i++){
            cin>>edges[i].a>>edges[i].b>>edges[i].v;
        }
        cout<<kruskal()<<endl;
    }
    return 0;
}
*/
const int N = 110;
char str[N][N];
char p[N];
int n,m;
int x_1,y_1,x_2,y_2;
int nex[8] = {0,0,1,-1,1,-1,1,-1},ney[8] = {1,-1,1,-1,0,0,-1,1};
bool match(int x,int y){
    int nx,ny,bx,by;
    for(int i=0;i<8;i++){
        bx = x + nex[i]*(m-1),by = y + ney[i]*(m-1);
        if(bx<0 || bx>=n || by<0 || by>=n) continue;
        bool judge = true;
        nx = x,ny = y;
        for(int j=1;j<m;j++){
            nx += nex[i],ny += ney[i];
            if(str[nx][ny]!=p[j]){
                judge = false;
                break;
            }
        }
        if(judge){
            x_1 = x,y_1 = y,x_2 = nx,y_2 = ny;
            return true;
        }
    }   
    return false;
}
bool getpos(){
    for(int i=0;i<n;i++)    
        for(int j=0;j<n;j++){
            if(str[i][j]==p[0]){
                if(match(i,j)) return true;
            }
        }
    return false;
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++)
        cin>>str[i];
    while(cin>>p){
        if(p[0]=='0') break;
        m = strlen(p);
        if(getpos()) cout<<x_1+1<<","<<y_1+1<<" "<<x_2+1<<","<<y_2+1<<endl;
        else cout<<"Not found"<<endl;
    }
    return 0;
}