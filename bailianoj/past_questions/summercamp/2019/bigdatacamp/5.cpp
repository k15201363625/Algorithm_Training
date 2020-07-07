#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//线段树维护区间异或和
const int N = 1e5+10;
#define lr o<<1
#define rr o<<1|1
struct Seg{
    int l,r,sum;
}tr[N<<2];
int w[N];
inline void pushup(int o){
    tr[o].sum = tr[lr].sum ^ tr[rr].sum;
}
void build(int o,int l,int r){
    if(l==r){
        tr[o].l = tr[o].r = l;
        tr[o].sum = w[l];
        return;
    } 
    tr[o].l = l,tr[o].r = r;
    int mid = (l+r)>>1;
    build(lr,l,mid);
    build(rr,mid+1,r);
    pushup(o);
}
void update(int o,int x,int v){
    //修改操作
    tr[o].sum ^= (w[x]^v);
    if(tr[o].l == tr[o].r){
        w[x] = v;//最后修改
        return;
    }
    if(tr[lr].r>=x && tr[lr].l<=x) update(lr,x,v);
    else if(tr[rr].r>=x && tr[rr].l<=x) update(rr,x,v);
    pushup(o); 
}
int query(int o,int l,int r){
    if(tr[o].r<l || tr[o].l>r)
        return 0;
    if(tr[o].l>=l && tr[o].r<=r) 
        return tr[o].sum;
    return query(lr,l,r)^query(rr,l,r);
}

int main(){
    int n,q;
    int a,b,c;
    while(cin>>n>>q){
        for(int i=1;i<=n;i++) w[i] = i;
        build(1,1,n);
        int res = 0;
        for(int i=0;i<q;i++){
            cin>>a>>b>>c;
            if(a==0) res ^= query(1,b,c);
            else update(1,b,c);
            
        }
        cout<<res<<endl;
    }
    return 0;
}