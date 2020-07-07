#include<iostream>
#include<cstring>
#include<iomanip>
#include<unordered_map>
using namespace std;
//方法：1 bfs 2 dp完全背包---可以单一dp也可以两次dp 需要注意状态压缩后的顺序 以及dp数组大小
//背包 -- 将面值看成代价 将数额（1）看成总值 求最小总值
// https://blog.csdn.net/u013480600/article/details/40454963
const int N = 10010;
int val[7];
int f[N];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        for(int i=0;i<6;i++) cin>>val[i],val[6+i] = val[i];
        //dp 完全背包 注意递推顺序
        memset(f,0x3f,sizeof f);
        f[0] = 0;
        for(int i=0;i<6;i++)
            for(int j=val[i];j<N;j++)
                f[j] = min(f[j],f[j-val[i]]+1);
        for(int i=0;i<6;i++)
            for(int j=N-1;j>=val[i];j--)
                f[j-val[i]] = min(f[j-val[i]],f[j]+1);
        double meanv = 0;
        int maxv = 1;
        for(int i=1;i<=100;i++){
            meanv += f[i];
            maxv = max(maxv,f[i]);
        }
        cout<<fixed<<setprecision(2)<<meanv/100.0<<" "<<maxv<<endl;
    }
    return 0;
}



/* 下面实现的方法类似bfs 但是很不精简
int nums1[1000],nums2[1000],basic[7],cnt1,cnt2;
int count[110];
unordered_map<int,bool> mmap;
void init(){
    memset(count,0,sizeof count);
    cnt1 = cnt2 = 0;
    mmap.clear();
}
double meanv;
int maxv;
int solve(){
    int cc = 6,t = 2;
    while(true){
        cnt2 = 0;
        for(int i=0;i<cnt1;i++){
            for(int j=0;j<6;j++){
                for(int k=0;k<2;k++){
                    int tmp = nums1[i] + basic[j];
                    if(k==1) tmp = nums1[i] - basic[j];
                    if(tmp>=1 && tmp<=100 && !count[tmp]){
                        count[tmp] = t;
                        cc++;
                        if(cc==100){
                            return t;
                        }
                        nums2[cnt2++] = tmp;
                        mmap[tmp] = true;
                    }else if(tmp>100 && !mmap[tmp]){
                        nums2[cnt2++] = tmp;
                        mmap[tmp] = true;
                    }
                }
                
            }
        }
        cout<<cc<<" "<<cnt1<<" "<<cnt2<<endl;
        memcpy(nums1,nums2,cnt2);
        cnt1 = cnt2;
        t++;
    }
    return -1;
}
int main(){
    int T;
    cin>>T;
    for(int i=0;i<T;i++){
        init();
        cnt1 = 6;
        for(int i=0;i<cnt1;i++) cin>>basic[i],nums1[i] = basic[i],count[basic[i]] = 1,mmap[basic[i]] = true;
        maxv = solve();
        meanv = 0;
        for(int i=1;i<=100;i++) meanv += count[i];
        meanv /= 100.0;
        cout<<fixed<<setprecision(2)<<meanv<<" "<<maxv<<endl;
    }
    return 0;
}
*/
