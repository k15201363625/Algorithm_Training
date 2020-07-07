#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
#include<cmath>
using namespace std;
const int N = 510;
int res[N*2],sav[N*2],num[N*2];
void mul(int a[],int b[]){
    memset(sav,0,sizeof sav);
    for(int i=0;i<500;i++)
        for(int j=0;j<500;j++)
            sav[i+j] += a[i]*b[j];
    //统一计算进位
    for(int i=0;i<500;i++){
        sav[i+1] += sav[i]/10;
        sav[i] %= 10;
    }
    memcpy(a,sav,sizeof sav);
}

int main(){
    int p;
    cin>>p;
    cout<<(int)(log10(2)*p+1)<<endl;
    memset(res,0,sizeof res),memset(num,0,sizeof num);
    res[0] = 1,num[0] = 2;
    //稳定500*500*logp
    while(p){
        if(p&1) mul(res,num);
        p>>=1;
        mul(num,num);
    }
    res[0] -= 1;
    int cnt = 0;
    for(int i=499;i>=0;i--){
        cout<<res[i];
        cnt++;
        if(cnt%50==0) cout<<endl;
    }
    return 0;
}

//acwing
//数组形式高精度模板
string add(char x[],char y[])
{
    int l1=strlen(x);
    reverse(x,x+l1);
    int l2=strlen(y);
    reverse(y,y+l2);
    int lm=max(l1,l2);
    for(int i=0;i<lm;++i)
    {
        if(x[i]==NULL)x[i]='0';
        if(y[i]==NULL)y[i]='0'; 
        x[i]=x[i]-'0';
        y[i]=y[i]-'0';
    }
    string ans;
    int j=0;
    for(int i=0;i<lm;++i)
    {
        j=x[i]+y[i]+j;
        if(j>=10)ans=ans+char(j-10),j=1;
        else ans=ans+char(j),j=0;
    }
    int l=ans.size();
    ans=ans+char(j);
    for(int i=l-1+j;i>=0;--i)
    {
        cout<<char(ans[i]+'0');
    }
    return "y";
}
void sub(char a[],char b[])
{
    int ans[200008];
    int l1=strlen(a);
    int l2=strlen(b);
    reverse(a,a+l1);
    reverse(b,b+l2);
    int lm=max(l1,l2); 
    for(int i=0;i<lm;++i)
    {
        if(a[i]==NULL)a[i]='0';
        if(b[i]==NULL)b[i]='0'; 
        a[i]=a[i]-'0';
        b[i]=b[i]-'0';
    }
    int j=0; 
    for(int i=0;i<lm;i++)
    {
        j=(a[i]-b[i])-j;
        if(j<0){ans[i]=j+10,j=1;}
        else ans[i]=j,j=0;
    }
    if(j)cout<<"-";
    bool flag=false;
    for(int i=lm;i>=0;--i)
    {
        if(ans[i])flag=true;
        if(flag)
        cout<<char(ans[i]+'0');
     } 
     if(flag==false)cout<<"0";
 } 

char stra[100001],strb[100001];
int x[100001],y[100001];
int cans[10000001];

string mul(char numa[],char numb[])
{
    string pns;
    int la=strlen(numa);
    int lb=strlen(numb);
    reverse(stra,stra+la);
    reverse(strb,strb+lb);
    for(int i=0;i<la;i++)
        x[i]=stra[i]-'0';
    for(int i=0;i<lb;i++)
        y[i]=strb[i]-'0';
    for(int i=0;i<la;i++)
    {
        for(int j=0;j<lb;j++)
        {
            cans[i+j]=cans[i+j]+x[i]*y[j];
        }
    }
    for(int i=0;i<la+lb-1;i++)
    {
        cans[i+1]=cans[i+1]+cans[i]/10;
        cans[i]=cans[i]%10;
        pns=char(cans[i]+'0')+pns;
    }
    if(cans[la+lb-1]>0)
    {
        pns=char(cans[la+lb-1]+'0')+pns;
    }
    return pns;
}

int main()
{
    cin>>stra>>strb;
    cout<<mul(stra,strb);
    return 0;
}
