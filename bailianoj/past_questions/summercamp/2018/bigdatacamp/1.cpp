#include<iostream>
#include<cstring>
using namespace std;
/*
const int N = 2e5+10;
int primes[N];
bool st[N];
int n,cnt = 0;
void getprimes(){
    for(int i=2;i<N;i++){
        if(!st[i]) primes[cnt++] = i;
        if(cnt==n) break;
        for(int j=0;primes[j]*i<=N;j++){
            st[primes[j]*i] = true;
            if(i%primes[j] == 0) break;
        }
    }
}
int main(){
    cin>>n;
    getprimes();
    cout<<primes[n-1]<<endl;
    return 0;
}
*/

char s1[110],s2[110],s3[110],res[110];
bool st[27],st2[27];
char mp[27],mp2[27];
int main(){
    cin>>s1>>s2>>s3;
    bool judge = true;
    for(int i=0;i<strlen(s1);i++){
        if(st2[s2[i]-'A'] && mp2[s2[i]-'A']!=s1[i]){
            judge = false;
            break;
        }
        mp[s1[i]-'A'] = s2[i];
        mp2[s2[i]-'A'] = s1[i];
        st[s1[i]-'A'] = true;
        st2[s2[i]-'A'] = true;
    }
    for(int i=0;i<26;i++){
        if(!st2[i]){
            judge = false;
            break;
        }
    }
    if(judge){
        for(int i=0;i<strlen(s3);i++)
            res[i] = mp[s3[i]-'A'];
        res[strlen(s3)] = '\0';
    }
    if(!judge) cout<<"Failed"<<endl;
    else cout<<res<<endl;
        
    return 0;
}