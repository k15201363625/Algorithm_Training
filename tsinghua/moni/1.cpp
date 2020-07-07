#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<set>
#include<algorithm>
using namespace std;
/*
const int N = 70000;
char str[N];
int cnt = 0;
void getres(int num){
    int a = 0,b = 0;
    for(int i=0;i<cnt;i++){
        if(str[i] == 'E') break;
        if(str[i]=='W') a++;
        else b++;
        if(abs(a-b)>=2 && (a>=num || b>=num)){
            cout<<a<<":"<<b<<endl;
            a = 0,b = 0;
        }
    }
    cout<<a<<":"<<b<<endl;
}
int main(){
    char tmp[30];
    while(cin>>tmp){
        for(int i=0;i<strlen(tmp);i++) str[cnt++] = tmp[i];
    }
    str[cnt] = '\0';
    getres(11);
    cout<<endl;
    getres(21);
    return 0;
}
*/
/*
char str[110][110];
int nex[8] = {-1,-1,0,1,1,1,0,-1},ney[8] = {0,1,1,1,0,-1,-1,-1};
int n,m;
void solve(){
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(str[i][j]=='*'){
                cout<<'*';
            }else{
                int cnt = 0,nx = i,ny = j;
                for(int k=0;k<8;k++){   
                    nx = i + nex[k],ny = ney[k] + j;
                    if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                    if(str[nx][ny]=='*') cnt++;
                }
                cout<<cnt;
            }
        }
        cout<<endl;
    }
}
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>str[i];
    solve();
    return 0;
}
*/
/*
const int N = 1e5+10;
int n,m;
bool st[N];
string names[N];
void move(int &now,int op,int step){
    if(!st[now]){
        if(op==0) now = (now+step)%n;
        else now = (now-step+n)%n;
    }else{
        if(op==0) now = (now-step+n)%n;
        else now = (now+step)%n;
    }
}
int main(){
    cin>>n>>m;
    for(int i=n-1;i>=0;i--){
        cin>>st[i]>>names[i];
    }
    int op,step;
    int now = n-1;
    for(int i=0;i<m;i++){
        cin>>op>>step;
        move(now,op,step);
    }
    cout<<names[now]<<endl;
    return 0;
}
*/
/*
const int N = 210;
int st[5][5] = {
    {0,-1,1,1,-1},
    {1,0,1,1,-1},
    {-1,1,0,-1,1},
    {-1,-1,1,0,1},
    {1,1,-1,-1,0}
};
int as[N],bs[N];
int n,na,nb;
int main(){
    cin>>n>>na>>nb;
    for(int i=0;i<na;i++) cin>>as[i];
    for(int i=0;i<nb;i++) cin>>bs[i];
    for(int i=na;i<n;i++){
        as[i] = as[i%na];
    }
    for(int i=nb;i<n;i++){
        bs[i] = bs[i%nb];
    }
    int sa = 0,sb = 0;
    for(int i=0;i<n;i++){
        if(st[as[i]][bs[i]]==1) sa++;
        else if(st[as[i]][bs[i]]==-1) sb++; 
    }
    cout<<sa<<" "<<sb<<endl;
    return 0;
}
*/
//难点在于判断是否有解
/*
const int N = 11;
bool st[170000];//X+10*Y+100*XX+1000*YY+10000*DIR1+40000*DIR2
int nex[4] = {-1,0,1,0},ney[4] = {0,1,0,-1};
char g[N][N];
int fx,fy,cx,cy,d1 = 0,d2 = 0;
int gettag(){
    return fx+fy*10+cx*100+cy*1000+d1*10000+d2*40000;
}
int solve(){
    int res = 0;
    st[gettag()] = true;
    int nx,ny,d;
    int cnt = 0;
    while(true){
        cnt++;
    

        nx = fx + nex[d1],ny = fy + ney[d1];
        if(nx<0 || nx>=10 || ny<0 || ny>=10 || g[nx][ny]=='*') d1 = (d1+1)%4;
        else fx = nx,fy = ny;

        nx = cx + nex[d2],ny = cy + ney[d2];
        if(nx<0 || nx>=10 || ny<0 || ny>=10 || g[nx][ny]=='*') d2 = (d2+1)%4;
        else cx = nx,cy = ny;
        
        if(fx==cx && fy==cy){
            res = cnt;
            break;
        }
        if(st[gettag()]) break;
        else st[gettag()] = true;
    }
    return res;
}
int main(){
    for(int i=0;i<10;i++) cin>>g[i];
    for(int i=0;i<10;i++)
        for(int j=0;j<10;j++)
            if(g[i][j]=='F') fx = i,fy = j;
            else if(g[i][j]=='C') cx = i,cy = j;
    cout<<solve()<<endl;
    return 0;
}
*/
/*
int n;
int num[110];
void solve(){
    for(int i=n;i>=0;i--){
        if(num[i]){
            if(num[i]<0){
                cout<<"-";
                if(i==0 || num[i]!=-1) cout<<-num[i];
            } 
            else{
                if(i!=n) cout<<"+";
                if(i==0 || num[i]!=1) cout<<num[i];
            }
            if(i!=0){
                if(i!=1) cout<<"x^"<<i;
                else cout<<"x";
            }
                
        }
    }
}   
int main(){
    cin>>n;
    for(int i=n;i>=0;i--) cin>>num[i];
    solve();
    return 0;
}
*/
/*
//(100/3+1)*26*8
const int N = 7100;
char res[N],str[110];
int a,b,c,n;
int check(int i){
    if(str[i]>='a' && str[i]<='z' && str[i+2]>='a' && str[i+2]<='z'){
        if(str[i]<str[i+2]) return 1;
        else return 2;
    }
    if(str[i]>='0' && str[i]<='9' && str[i+2]>='0' && str[i+2]<='9'){
        if(str[i]<str[i+2]) return 3;
        else return 4;
    }
    return 0;
}
void parse(){
    int cnt = 0,cc = 0;
    char tmp[26*8];
    n = strlen(str);
    for(int i=0;i<n;i++){
        res[cnt++] = str[i];
        if(i+2<n && str[i+1]=='-'){
            int st = check(i);
            if(st==0) continue;
            else if(st==2 || st==4){
                res[cnt++] = str[i+1];
                i++;
            }else{
                if(str[i+2]==str[i]+1){
                    i++;
                }else{
                    cc = 0;
                    for(char now=str[i]+1;now<str[i+2];now++){
                        if(a==3){
                            for(int j=0;j<b;j++) tmp[cc++] = '*';
                        }else{
                            if(st==3){
                                for(int j=0;j<b;j++) tmp[cc++] = now;
                            }else{
                                for(int j=0;j<b;j++){
                                    if(a==1) tmp[cc++] = now;
                                    else tmp[cc++] = now-'a'+'A';
                                }
                            }
                        }
                    }
                    if(c==1) for(int j=0;j<cc;j++) res[cnt++] = tmp[j];
                    else for(int j=cc-1;j>=0;j--) res[cnt++] = tmp[j];
                    i++;
                }
            }
        }
    }
}
int main(){
    cin>>a>>b>>c;
    cin>>str;
    parse();
    cout<<res<<endl;
    return 0;
}
*/
/*
const int N = 25;
const int inf = 10000;
typedef pair<int,int> pii;
int n,m;
int id[N][N],tt[N][N];
int a[N*N];
int cnt[N],ti[N];
set<pii> q[N];
int assign(){
    int res = 0;
    for(int i=1;i<=m;i++) q[i].insert({0,inf});
    memset(cnt,0,sizeof cnt);
    memset(ti,0,sizeof ti);
    for(int i=0;i<n*m;i++){
        int t = a[i]-1;
        int qid = id[t][cnt[t]],nowt = tt[t][cnt[t]];
        // cout<<i<<" "<<qid<<" "<<q[qid].size()<<endl;
        for(auto it = q[qid].begin();it!=q[qid].end();it++){
            int fir = (*it).first,sec = (*it).second;

            // cout<<i<<" "<<t<<" "<<nowt<<" "<<ti[t]<<" "<<fir<<" "<<sec<<" "<<qid<<" "<<q[qid].size()<<endl;

            if((fir>=ti[t] && sec-fir>=nowt) || (fir<ti[t] && ti[t]+nowt<=sec)){
                q[qid].erase(it);
                int newt = nowt;
                if(fir>=ti[t]){
                    if(fir+nowt<sec) q[qid].insert({fir+nowt,sec});
                    newt += fir;
                }else{
                    q[qid].insert({fir,ti[t]});
                    if(ti[t]+nowt<sec) q[qid].insert({ti[t]+nowt,sec});
                    newt += ti[t];
                }
                
                res = max(res,newt);
                ti[t] = newt;
                // cout<<t<<" "<<nowt<<" "<<newt<<endl;
                cnt[t]++;
                break;
            } 
        } 
    }
    return res;
}
int main(){
    cin>>m>>n;
    for(int i=0;i<n*m;i++) cin>>a[i];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>id[i][j];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            cin>>tt[i][j];
    cout<<assign()<<endl;
    return 0;
}
*/

struct Mem{
    string name,wk;
    int v,rank,id;
}mems[120];
int n;
int change(string str){
    if(str=="HuFa") return 0;
    else if(str=="ZhangLao") return 1;
    else if(str=="TangZhu") return 2;
    else if(str=="JingYing") return 3;
    else return 4;
}
bool cmp1(Mem &a,Mem &b){
    //按照帮派贡献排序
    if(a.v!=b.v) return a.v>b.v;
    else return a.id<b.id;
}
bool cmp2(Mem &a,Mem &b){
    //按照职位等级id对于输出顺序排序
    int wka = change(a.wk),wkb = change(b.wk);
    if(wka!=wkb) return wka<wkb;
    else{
        if(a.rank!=b.rank) return a.rank>b.rank;
        else return a.id<b.id;
    }
}
void assignwk(){
    int cnt = 0;
    for(int i=3;i<n;i++){
        if(cnt<2) mems[i].wk = "HuFa";
        else if(cnt<6) mems[i].wk = "ZhangLao";
        else if(cnt<13) mems[i].wk = "TangZhu";
        else if(cnt<38) mems[i].wk = "JingYing";
        else mems[i].wk = "BangZhong";
        cnt++;
    }
}

int main(){
    //默认字符串按照降序排列 字典序越小则越大
    // char demo[6] = "abc",demo2[6] = "abcd";
    // cout<<(demo<demo2)<<endl;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>mems[i].name>>mems[i].wk>>mems[i].v>>mems[i].rank;
        mems[i].id = i;
    }
    sort(mems+3,mems+n,cmp1);
    assignwk();
    sort(mems+3,mems+n,cmp2);
    for(int i=0;i<n;i++){
        cout<<mems[i].name<<" "<<mems[i].wk<<" "<<mems[i].rank<<endl;
    }
    return 0;
}