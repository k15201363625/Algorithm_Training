#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//食物链 
//拓展域/带权并查集
//带权并查集 本质关系即向量
//关系传递即向量运算 关系判断即向量运算
/*
int p[50010],d[50010];
int find(int x){
    if(p[x]==x) return p[x];
    int tmp = find(p[x]);
    d[x] = (d[p[x]]+d[x])%3;
    return p[x] = tmp;
}
int mod(int x){
    return (x%3+3)%3;
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++) p[i] = i;
    int ans = 0;
    int rel,x,y;
    for(int i=0;i<m;i++){
        cin>>rel>>x>>y;
        if(x>n || y>n){
            ans++;
            continue;
        }
        if(x==y && rel==2){
            ans++;
            continue;
        }
        int px = find(x),py = find(y);
        if(px==py){
            if(mod(d[x]-d[y])!=rel-1) ans++;
        }else{
            p[px] = py;
            // d[x] + d[px] - d[y] == rel - 1
            d[px] = mod(d[y]-d[x]+rel-1);
        }
    }
    cout<<ans<<endl;
    return 0;
}
*/

//拓展域做法本质是拆点并查集
//复杂度会在合并的时候变成 O(m)/O(C(m,2))
//空间复杂度变成O(m*n) 本题m==3
int p[150010];
int n,m;
int find(int x){
    if(p[x]!=x) p[x] = find(p[x]);
    return p[x];
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n*3;i++) p[i] = i;
    int rel,x,y;
    int ans = 0;
    for(int i=0;i<m;i++){
        cin>>rel>>x>>y;
        if(x>n || y>n){
            ans++;
        }else{
            if(rel==1){
                if(find(x)==find(y+n) || find(x)==find(y+2*n))
                    ans++;
                else{
                    p[find(x)] = find(y);
                    p[find(x+n)] = find(y+n);
                    p[find(x+2*n)] = find(y+2*n);
                }
            }else{
                if(x==y || find(x)==find(y) || find(x)==find(y+2*n))
                    ans++;
                else{
                    p[find(x)] = find(y+n);
                    p[find(x+n)] = find(y+2*n);
                    p[find(x+2*n)] = find(y);
                }
            }
        }
    }
    cout<<ans<<endl;
    return 0;
}