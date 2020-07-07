#include<iostream>
#include<cstring>
#include<sstream>
#include<algorithm>
#include<queue>
using namespace std;
//朴素bfs最短路 输入处理难点
string st,ed;
string dic[40];
int cnt = 0;
int h[40],e[2000],ne[2000],idx = 0;
void add(int a,int b){
    e[idx] = b,ne[idx] = h[a],h[a] = idx++;
}
int countdiff(string &a,string &b){
    int cnt = 0;
    for(int i=0;i<a.length();i++){
        if(a[i]!=b[i]) cnt++;
    }
    return cnt;
}
bool stat[40];
int d[40];
int bfs(){
    memset(stat,false,sizeof stat);
    memset(d,0,sizeof d);
    queue<int> q;
    q.push(0);
    stat[0] = true,d[0] = 0;
    while(q.size()){
        int t = q.front();
        q.pop();
        if(t==1) break;
        for(int i=h[t];i!=-1;i=ne[i]){
            int j = e[i];
            if(!stat[j]){
                stat[j] = true;
                d[j] = d[t]+1;
                q.push(j);
            }
        }
    }
    if(d[1] == 0 && !stat[1]) return 0;
    else return d[1] + 1;
}
int main(){
    memset(h,-1,sizeof h);
    cin>>st>>ed;
    dic[cnt++] = st,dic[cnt++] = ed;
    int diff = countdiff(st,ed);
    if(diff==1){
        add(0,1),add(1,0);
    }
    char ss[200];
    string tmp;
    getchar();
    cin.getline(ss,200);
    stringstream sin(ss);
    while(sin>>tmp){
        if(tmp==st || tmp==ed) continue;
        dic[cnt] = tmp;
        for(int i=0;i<=cnt-1;i++){
            diff = countdiff(dic[i],tmp);
            if(diff==1){
                add(i,cnt),add(cnt,i);
            }
        }
        cnt++;
    }
    cout<<bfs()<<endl;
    return 0;
}