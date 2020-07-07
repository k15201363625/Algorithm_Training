#include<iostream>
#include<cstring>
#include<algorithm>
using namespace std;
//归并排序过程完成判断 类似普通逆序对计数 只是需要代码分离
const int N = 2e5+10;
int a[N],b[N];
int n;
int cnt = 0;
void merge(int l,int mid,int r){
    int i = l,j = mid + 1;
    memcpy(b+l,a+l,(r-l+1)*sizeof(int));//注意跟的是size
    //首先统计 
    while(i<=mid && j<=r){
        if(b[i]>2*b[j]){
            cnt += mid - i + 1;
            j++;
        }else{
            i++;
        }
    }
    //之后排序 需要额外收尾
    i = l,j = mid + 1;
    int k = l;
    while(i<=mid && j<=r){
        if(b[i]<b[j]) a[k++] = b[i++];
        else a[k++] = b[j++];
    }
    while(i<=mid) a[k++] = b[i++];
    while(j<=r) a[k++] = b[j++];
}
void solve(int l,int r){
    if(l==r) return;
    int mid = (l+r)>>1;
    solve(l,mid);
    solve(mid+1,r);
    merge(l,mid,r);
}
int main(){
    cin>>n;
    for(int i=0;i<n;i++) cin>>a[i];
    solve(0,n-1);
    cout<<cnt<<endl;
    return 0;
}