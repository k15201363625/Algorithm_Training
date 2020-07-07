#include <iostream>
#include <vector>
#include<algorithm>
using namespace std;

vector<int> add(vector<int> &A, vector<int> &B)
{
    if (A.size() < B.size()) return add(B, A);

    vector<int> C;
    int t = 0;
    for (int i = 0; i < A.size(); i ++ )
    {
        t += A[i];
        if (i < B.size()) t += B[i];
        C.push_back(t % 10);
        t /= 10;
    }

    if (t) C.push_back(t);
    return C;
}
bool cmp(vector<int> &A, vector<int> &B)
{
    if (A.size() != B.size()) return A.size() > B.size();

    for (int i = A.size() - 1; i >= 0; i -- )
        if (A[i] != B[i])
            return A[i] > B[i];

    return true;
}

vector<int> sub(vector<int> &A, vector<int> &B)
{
    vector<int> C;
    for (int i = 0, t = 0; i < A.size(); i ++ )
    {
        t = A[i] - t;
        if (i < B.size()) t -= B[i];
        C.push_back((t + 10) % 10);
        if (t < 0) t = 1;
        else t = 0;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}
vector<int> getnum(string &a){
    vector<int> A;
    for (int i = a.size() - 1; i >= 0; i -- ) A.push_back(a[i] - '0');
    return A;
}
void outputnum(vector<int> &A){
    for (int i = A.size() - 1; i >= 0; i -- ) cout << A[i];
    cout << endl;
}

vector<int> mul(vector<int> &A, int b)
{
    vector<int> C;

    int t = 0;
    for (int i = 0; i < A.size() || t; i ++ )
    {
        if (i < A.size()) t += A[i] * b;
        C.push_back(t % 10);
        t /= 10;
    }

    while (C.size() > 1 && C.back() == 0) C.pop_back();

    return C;
}

vector<int> div(vector<int> &A, int b, int &r)
{
    vector<int> C;
    r = 0;
    for (int i = A.size() - 1; i >= 0; i -- )
    {
        r = r * 10 + A[i];
        C.push_back(r / b);
        r %= b;
    }
    reverse(C.begin(), C.end());
    while (C.size() > 1 && C.back() == 0) C.pop_back();
    return C;
}
/*
int main(){
    int n;
    cin>>n;
    vector<int> res,num;
    res.push_back(0),num.push_back(1);
    for(int i=1;i<=n;i++){
        num = mul(num,i);
        res = add(res,num);
    }
    outputnum(res);
    return 0;
}
*/
/*
//贪心+高精
//整数拆分问题 如果为可相同 目标拆成2 3 
//如果不相同 目标拆成越多越好 所以从小开始 对于余数 单元提升 避免重复即可
//而总结规律为 加到超过 如果超过为1 则去掉2 n->n+1 ；如果超过不为1 则去掉超过的对应的数字
//以上是贪心 可以通过取对数转换为n^2的01背包问题
// https://www.luogu.com.cn/problem/solution/P1249
int nums[1000],cnt = 0;
int main(){
    int n;
    cin>>n;
    int num = 2,sum = 0;
    while(sum<n){
        sum += num;
        num++;
    }
    num --;
    if(sum==n){
        for(int i=2;i<=num;i++) nums[cnt++] = i;
    }else{
        if(sum-n==1){
            for(int i=3;i<num;i++) nums[cnt++] = i;
            nums[cnt++] = num+1;
        }else{
            for(int i=2;i<=num;i++){
                if(i==sum-n) continue;
                nums[cnt++] = i;
            }
        }
    }
    vector<int> res;
    res.push_back(1);
    for(int i=0;i<cnt;i++){
        res = mul(res,nums[i]);
    }
    for(int i=0;i<cnt;i++) cout<<nums[i]<<" ";
    cout<<endl;
    outputnum(res);
    return 0;
}
*/
/*
int main(){
    int T,n,k;
    cin>>T;
    while(T--){
        cin>>n>>k;
        vector<int> res;
        res.push_back(1);
        for(int i=2;i<=n;i++) res = mul(res,i);
        int ans = 0;
        for(int i=0;i<res.size();i++) if(res[i]==k) ans++;
        cout<<ans<<endl;
    }
    return 0;
}
*/
