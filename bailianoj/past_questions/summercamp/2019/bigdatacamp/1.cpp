#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
/*
const int N = 1e3+10;
int xs[N],ys[N];
int main(){
    int T;
    cin>>T;
    while(T--){
        int n,mind = 0x3f3f3f3f;
        cin>>n;
        for(int i=0;i<n;i++){
            cin>>xs[i]>>ys[i];
        }
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++){
                if(i==j) continue;
                mind = min(mind,(xs[i]-xs[j])*(xs[i]-xs[j])+(ys[i]-ys[j])*(ys[i]-ys[j]));
            }
        cout<<mind<<endl;
    }
    return 0;
}
*/
/*
class Patient{
public:
    int num,years;
    string id;
    Patient(){}
};
class OldPatient : public Patient{
public:
    bool operator<(const OldPatient& o) const{
        if(years!=o.years) return years>o.years;
        else return num<o.num;
    }
}os[110];
class YoungPatient : public Patient{
public:
    bool operator<(const YoungPatient& o) const{
        return num<o.num;
    }
}ys[110];

int main(){
    int n;
    cin>>n;
    int years;
    string id;
    int ocnt = 0,ycnt = 0;
    for(int i=0;i<n;i++){
        cin>>id>>years;
        if(years<60){
            ys[ycnt].id = id,ys[ycnt].years = years,ys[ycnt++].num = i;
        }else{
            os[ocnt].id = id,os[ocnt].years = years,os[ocnt++].num = i;
        }
    }
    sort(ys,ys+ycnt);
    sort(os,os+ocnt);
    for(int i=0;i<ocnt;i++) cout<<os[i].id<<endl;
    for(int i=0;i<ycnt;i++) cout<<ys[i].id<<endl;
    return 0;
}
*/

//小型dp
/*
int main(){
    int n,m;
    cin>>n>>m;
    int maxa=0,maxb=0,tmp=0;
    int ca,cb;
    for(int i=0;i<n;i++){
        cin>>ca>>cb;
        if(i==0){
            maxa = ca,maxb = cb;
            continue;
        }
        tmp = maxa;
        maxa = max(maxa+ca,maxb+cb-m);
        maxb = max(tmp+ca-m,maxb+cb);
    }
    cout<<max(maxa,maxb)<<endl;
    return 0;
}
*/

//小型模拟
//CIN自动个过滤空格 但是之后如果使用getchar需要先吸收掉空格换行等
char g[25][25];
int row,col;
void getbin(int num,char str[]){
    for(int i=0;i<=4;i++){
        if(num&(1<<i))
            str[4-i] = '1';
        else
            str[4-i] = '0';
    }
    str[5] = '\0';
}
char str[90];
char res[90][6];
bool st[25][25];
int dirx[4] = {0,1,0,-1},diry[4] = {1,0,-1,0};
bool getnepos(int &x,int &y,int &nowd){
    int nx = x + dirx[nowd],ny = y + diry[nowd];
    if(nx>=0 && nx<row && ny>=0 && ny<col && !st[nx][ny]){
        st[nx][ny] = true;
        x = nx,y = ny;
        return true;
    }
    nowd = (nowd+1)%4;
    nx = x + dirx[nowd],ny = y + diry[nowd];
    x = nx,y = ny;
    if(st[nx][ny]) return false;
    else{
        st[nx][ny] = true;
        return true;
    }
}
void draw(){
    memset(st,0,sizeof st);
    int x = 0,y = -1,dir = 0;
    for(int i=0;i<strlen(str);i++){
        for(int j=0;j<5;j++){
            if(getnepos(x,y,dir)) 
                g[x][y] = res[i][j];
            else 
                cout<<"error"<<endl;
        }
    }
    for(int i=strlen(str)*5+1;i<=row*col;i++){
        getnepos(x,y,dir);
        g[x][y] = '0';
    }
}
int main(){
    // itoa(3,str,2);
    cin>>row>>col;
    char tmp = getchar();
    int cnt = 0;
    while(tmp = getchar()){
        if(tmp=='\n') break;
        str[cnt++] = tmp;
    }
    str[cnt] = '\0';
    for(int i=0;i<strlen(str);i++){
        if(str[i] == ' '){
            for(int j=0;j<5;j++) res[i][j] = '0';
            res[i][5] = '\0';
        }
        else getbin(str[i]-'A'+1,res[i]);
    }
    //开始填充
    draw();
    for(int i=0;i<row;i++)
        for(int j=0;j<col;j++)
            cout<<g[i][j];
    cout<<endl;
    return 0;
}