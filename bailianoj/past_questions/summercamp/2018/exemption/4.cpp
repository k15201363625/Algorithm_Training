#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
bool cmp(vector<int> &a,vector<int>& b){
    if(a.size()!=b.size()) return a.size()<b.size();
    for(int i=a.size()-1;i>=0;i--){
        if(a[i]<b[i]) return true;
        else if(a[i]>b[i]) return false;
    }
    return false;
}
void output(vector<int>& a){
    for(int i=a.size()-1;i>=0;i--)
        cout<<a[i];
    cout<<endl;
}
void add(vector<int>& a,vector<int>& b,bool op){
    cout<<"======"<<endl;
    output(a),output(b);

    vector<int> res;
    int t = 0,id = 0;
    while(id<a.size() || id<b.size()){
        if(id<a.size()) t += a[id];
        if(id<b.size()) t += (op?b[id]:-b[id]);
        res.push_back((t%10+10)%10);
        if(t<0 && t%10!=0) t = t/10-1;
        else t/=10;
        id++;
    }
    while(t) res.push_back(t%10),t/=10;
    while(res.back()==0) res.pop_back();
    if(res.size()==0) res.push_back(0);
    a.clear();
    for(int i=0;i<res.size();i++) a.push_back(res[i]);
    output(res);
    cout<<"======="<<endl;
}
vector<int> getvec(char str[],int l,int r){
    vector<int> res(r-l+1);
    for(int i=l;i<=r;i++)
        res[r-l-(i-l)] = str[i]-'0';
    return res;
}
vector<int> f[55];//f[n][m] 前i个位置放了j个加号
int rec[55];//上一次最优分界点所在位置
char str[55];
int main(){
    int m,n;
    while(cin>>m){
        cin>>str;
        n = strlen(str);
        // vector<int> tmp(n);
        // for(int i=n-1;i>=0;i--){
        //     tmp[n-1-i] = str[i]-'0';
        // }
        for(int i=0;i<=m;i++) f[i].clear();
        vector<int> tmp = getvec(str,0,n-1);
        f[0] = tmp,rec[0] = 0;
        for(int i=1;i<=n-1;i++)
            for(int j=min(i,m);j>=1;j--){
                //f[i][j] = min(f[i-1][j],f[i-1][j-1]+change)
                //初始化 f[i][0] = origin
                vector<int> copy = f[j-1];
                tmp = getvec(str,rec[j-1],n-1);
                add(copy,tmp,false);
                tmp = getvec(str,rec[j-1],i-1);
                add(copy,tmp,true);
                tmp = getvec(str,i,n-1);
                add(copy,tmp,true);
                output(copy);
                cout<<"------"<<i<<" "<<j<<endl;
                if(f[j].size()==0 || cmp(copy,f[j])){
                    output(f[j]);
                    rec[j] = i;
                    f[j] = copy;
                }
            }
        //结果为f[n-1][m]
        output(f[m]);
    }
    return 0;
}