#include<cstdio>
#include<iostream>
#include<algorithm>
using namespace std;
/*
bool st[1010];
int main(){
    int n,num;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>num;
        st[num] = true;
    }
    int ans = 0;
    for(int i=0;i<=n;i++){
        if(!st[i]){
            ans = i;
            break;
        }
    }
    cout<<ans<<endl;
    return 0;
}
*/

const int N = 20;
int st[N][N];
int nex[8] = {0,0,-1,1,-1,1,-1,1},ney[8] = {-1,1,0,0,1,-1,-1,1};
int n;
bool judge(int x,int y){
    bool res = false;
    int last = 0,nx = x,ny = y;
    for(int i=0;i<8;i++){
        if(i%2==0) last = 1;   
        nx = x,ny = y;
        for(int k=0;k<=4;k++){
            nx += nex[i],ny += ney[i];
            if(nx<0 || nx>=n || ny<0 || ny>=n || st[nx][ny]!=st[x][y]) break;
            last++;  
        }
        if(last>=5){
            res = true;
            break;
        }
    }
    return res;
}
int main(){
    int x,y,res=0,step=0;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>x>>y;
        if(i%2==0) st[x][y] = 1;
        else st[x][y] = 2;
        if(step) continue;
        if(judge(x,y)){
            res = i%2+1;
            step = (i+1);
        }
    }
    if(!res) cout<<"Tie"<<endl;
    else{
        if(res==1) cout<<"A"<<" ";
        else cout<<"B"<<" ";
        cout<<step<<endl;
    } 
    return 0;
}