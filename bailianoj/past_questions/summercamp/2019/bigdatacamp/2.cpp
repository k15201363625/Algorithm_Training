#include<cstring>
#include<iostream>
#include<iomanip>
#include<cmath>
using namespace std;
//二分 错误原因 本题的精确到cm指的是计算都使用cm而非更加精细的单位 并不是精确到cm 所以需要转换为int整数二分 使用double过度精细反倒不行
const double eps = 1e-4;
const int N = 1e5+10;
int n,k;
double lens[N];
bool check(double goal){
    int cnt = 0;
    for(int i=0;i<n;i++){
        cnt += (int)floor(lens[i]/goal);
        if(cnt>=k) return true;
    }
    return false;
}
int main(){
    // cout<<(int)(5.7/2.2)<<endl;//自动下取整
    cin>>n>>k;
    double maxlen = 0.0;
    for(int i=0;i<n;i++){
        cin>>lens[i];
        maxlen = max(maxlen,lens[i]);
    }

    double l = 0.0,r = maxlen;
    while(r-l>eps){
        double mid = (l+r)/2;
        if(check(mid)) l = mid;
        else r = mid;
    }
    if(l>=0.01) cout<<fixed<<setprecision(2)<<l<<endl;
    else cout<<fixed<<setprecision(2)<<0.0<<endl;
    
    return 0;
}