#include<iostream>
#include<cstring>
#include<map>
using namespace std;
/*
const int N = 210;
char se[N];
int mod(int x){
    return (x%26+26)%26;
}
int main(){
    cin.getline(se,N);
    for(int i=0;i<strlen(se);i++){
        if(se[i]>='A' && se[i]<='Z'){
            se[i] = 'A'+mod(se[i]-'A'-5);
        }
    }
    cout<<se<<endl;
    return 0;
}
*/

//热血格斗场 平衡树
const int N = 1e5+10;
int n;
typedef map<int,int> mii;
mii mems;
int a[N],b[N],cnt=0;
int main(){
    cin>>n;
    int id,v;
    mems.insert({1000000000,1});
    int vv,v1,v2;
    mii::iterator it,suf,pre;
    for(int i=0;i<n;i++){
        cin>>id>>v;
        mems.insert({v,id});
        a[cnt] = id;
        it = mems.find(v),pre = it,suf = it;
        suf++,pre--;
        int pid = (*pre).second,sid = (*suf).second;
        if(suf==mems.end()) b[cnt++] = pid;
        else if(pre==mems.end()) b[cnt++] = sid;
        else{
            vv = (*it).first,v1 = (*suf).first,v2 = (*pre).first;
            if(v1-vv==vv-v2) b[cnt++] = pid;
            else if(v1-vv<vv-v2) b[cnt++] = sid;
            else b[cnt++] = pid;
        }  
    }
    for(int i=0;i<cnt;i++) cout<<a[i]<<" "<<b[i]<<endl;
    return 0;

}