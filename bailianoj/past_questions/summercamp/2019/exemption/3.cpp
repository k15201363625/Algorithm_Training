#include<iostream>
#include<cstring>
#include<algorithm>
#include<unordered_map>
using namespace std;
typedef unordered_map<string,int> msi;
string hs[19] = {"pop","no","zip","zotz","tzec","xul","yoxkin","mol","chen","yax","zac","ceh","mac","kankin","muan","pax","koyab","cumhu","uayet"};
string ts[20] = {"imix","ik","akbal","kan","chicchan","cimi","manik","lamat","muluk","ok","chuen","eb","ben","ix","mem","cib","caban","eznab","canac","ahau"};
msi haab;
void solve(int days){
    int year = days/260;
    int resd = days%260;
    int a = resd%13+1,b = resd%20;
    cout<<a<<" "<<ts[b]<<" "<<year<<endl; 
}
int main(){
    int n;
    cin>>n;
    for(int i=1;i<=19;i++) haab[hs[i-1]] = i;
    double tmp;
    int year;
    string mon;
    int totalday = 0;
    cout<<n<<endl;
    for(int i=0;i<n;i++){
        cin>>tmp>>mon>>year;
        totalday = year * 365 + (haab[mon]-1)*20 + int(tmp);
        solve(totalday);
    }
    return 0;
}