#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<map>
#include<queue>
#include<vector>//unique不能用在int[]上面
using namespace std;
// 贪心问题
//通常套路：先通过例子/经验规律进行猜测 之后尝试证明正确性
// greedy常用证明方法
// 1 证明ans<=cnt cnt<=ans ==> ans==cnt
// 2 通过反证法证明
// 3 通过替换调整法证明(属于反证法) 最优结果一定可以调整为当前解法并且不会变差
// 4 数学归纳法
// 5 直接通过分析证明
//常见模型：
// 区间+点问题：
    // 区间被最少点覆盖 == 区间中最多可以选出多少不连续的区间
    // 区间与点最大匹配问题(二分最大匹配 结合二分图证明)
    // 区间最少需要划分成多少组不相交的区间
    // 一个大区间至少需要几个小的区间可以覆盖
// 不等式+公式问题：
    // 排序不等式
    //     可以拓展到有意来情况下的贪心合并方法
    // 绝对值不等式
    // 通过替换调整得到相应排序规则公式(奶牛 国王的游戏)
// 经典模型
    // 哈弗曼树
    // dijkstra最短路算法

// 防晒
// 属于区间与点匹配问题 可以通过最大二分图匹配没有增光路方式证明
//方法：
// 按照区间前端点排序 倒着枚举每个区间 每个区间和最靠后可以匹配的点匹配
/*
错误代码
typedef pair<int,int> pii;
const int N = 2510;
pii intervals[N];
map<int,int> spf;
vector<int> dots;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++){
        // cin>>intervals[i].second>>intervals[i].first;
        cin>>intervals[i].first>>intervals[i].second;
    }
    // for(int i=0;i<m;i++) cin>>spf[i].first>>spf[i].second; 
    //存在相同防晒霜 所以需要用map
    int a,b;
    for(int i=0;i<m;i++) {
        cin>>a>>b;
        dots.push_back(a);
        spf[a] += b;
    }
    sort(intervals,intervals+n);
    sort(dots.begin(),dots.end());
    dots.erase(unique(dots.begin(),dots.end()),dots.end());
    // sort(spf,spf+m);使用map自动有序 但是需要使用upperbound查找 设置哨兵更方便代码
    int j = dots.size()-1,res = 0;
    for(int i=n-1;i>=0;i--){
        int l=intervals[i].first,r = intervals[i].second;
        //此处可以用upperbound实现logn查找 不过复杂度第二部分会稍微高一点
        while(j>=0 && dots[j]>r) j--;
        // cout<<l<<" "<<r<<" "<<dots[j]<<endl;
        // cout<<j<<endl;
        if(j<0) break;
        if(dots[j]<l) continue;
        if(spf[dots[j]]>1){
            spf[dots[j]]--;
            res ++;
        }else{
            res ++;
            j--;
        }
    } 
    cout<<res<<endl;
    return 0;
}
*/

//错误原因 没有想清楚排序关键字 应该按照起点排序 此时为了找到符合的点 不能直接降序扫描 而应该使用map动态查找
/*
typedef pair<int,int> pii;
const int N = 2510;
pii intervals[N];
map<int,int> spf;
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=0;i<n;i++) cin>>intervals[i].first>>intervals[i].second;
    int a,b;
    for(int i=0;i<m;i++){
        cin>>a>>b;
        spf[a] += b;
    }
    sort(intervals,intervals+n);
    //为了方便查找 插入哨兵
    // 保证元素不会被删空 不用判断spf.size()==0 如果只插入一个在当前是可以的(直插入0可以)
    spf[0] = 1,spf[1001] = 1;
    int res = 0;
    for(int i=n-1;i>=0;i--){
        //找到对应的点 使用map方便 upperbound nlogn
        //使用平衡树的结构支持动态删除点 动态查找某个符合条件的点
        auto now = spf.upper_bound(intervals[i].second);
        now--;
        if(now->first>=intervals[i].first){
            res ++;
            if(--now->second==0) 
                spf.erase(now);
        }
    }
    cout<<res<<endl;
    return 0;
}
*/

// 畜栏预定
// 使用最少区间分组全部区间 保证内部不相交
// 使用贪心 按照区间起点排序 只有不满足所有已有分组 才新加分组
// 主需要维护每个分组的末端点 以及对应的最小值--> heap
// 50000 nlogn可以
// 使用cnt>=ans cnt<=ans 可以证明
/*
const int N = 5e5+10;
typedef pair<int,int> pii;
// vector<pair<int,int>> res[N];
pair<pii,int> cows[N];
int res[N];
int cnt = 0;
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++) cin>>cows[i].first.first>>cows[i].first.second,cows[i].second = i;
    sort(cows,cows+n);
    // priority_queue<int,vector<int>,greater<int>> pq; 为了保存方案 需要再保存对应的区间
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq; 
    // res[cnt++].push_back({cows[0].first,cows[0].second});
    res[cows[0].second] = ++cnt;
    pq.push({cows[0].first.second,1});
    for(int i=1;i<n;i++){
        int l = cows[i].first.first,r = cows[i].first.second;
        if(l<= pq.top().first){
            // res[cnt++].push_back({l,r});
            res[cows[i].second] = ++cnt;
            pq.push({r,cnt});
        }else{
            int goal = pq.top().second;
            // res[goal].push_back({l,r});
            res[cows[i].second] = goal;
            pq.pop();
            pq.push({r,goal});
        }
    }
    cout<<cnt<<endl;
    // for(int i=0;i<cnt;i++){
    //     for(auto x:res[i])
    //         cout<<x.first<<" "<<x.second<<endl;
    // }
    for(int i=0;i<n;i++) cout<<res[i]<<endl;
    return 0;
}
*/
// 国王游戏
// 排序的时间复杂度是 O(nlogn)
// 这道题目的时间复杂度瓶颈在高精度计算上，最坏情况下所有 Ai=9999，则前 ii 个数的乘积大约是4i位，
// 每次乘一个新的数就需要4i的计算量，所以总共的计算量是 O(4∗∑i)=O(n2)
// 按照Ai×Bi排序即可 关键用到互不影响的特性
// 难点：高精度乘法 高精度除法 性能瓶颈高精度计算 -- O(n^2)
/*
const int N = 1010;
typedef pair<int,int> pii;
int n;
pii p[N];
vector<int> mul(vector<int>&a,int b){
    vector<int> res;
    int t = 0;
    for(int i=0;i<a.size();i++){
        t += a[i]*b;
        res.push_back(t%10);
        t/=10;
    }
    while(t) res.push_back(t%10),t/=10;
    return res;
}
vector<int> div(vector<int>&a,int b){
    vector<int> res;
    int t = 0;
    bool is_first = true;//记录首位元素
    for(int i=a.size()-1;i>=0;i--){
        t = t*10 + a[i];
        int x = t/b;//必然只有一位
        if(!is_first || x){
            is_first = false;
            res.push_back(x);
        }
        t %= b;
    }
    reverse(res.begin(),res.end());
    return res;
}
vector<int> max_vec(vector<int>& a,vector<int>& b){//不能是引用??
    if(a.size()>b.size()) return a;
    if(a.size()<b.size()) return b;
    for(int i=a.size()-1;i>=0;i--){
        if(a[i]<b[i]) return b;
        else return a;
    }
    return a;
    //或者直接用vector比较函数 前提先翻转
    // if(vector<int>(a.rbegin(),a.rend())>vector<int>(b.rbegin(),b.rend())) return a;
    // return b;
    
}
int main(){
    cin>>n;
    for(int i=0;i<=n;i++){
        int a,b;
        cin>>a>>b;
        p[i] = {a*b,a};
    }
    sort(p+1,p+n+1);
    //高精度计算
    vector<int> product(1,1);
    vector<int> res(1,0);
    product = mul(product,p[0].second);
    for(int i=1;i<=n;i++){
        vector<int> tmp = div(product,p[i].first/p[i].second);
        res = max_vec(res,tmp);//不能直接进去 因为引用问题？？
        product = mul(product,p[i].second);
    }
    for(int i=res.size()-1;i>=0;i--) cout<<res[i];
    cout<<endl;
    return 0;
}
*/
//同上思路 耍杂技的牛
/*
typedef long long ll;
const int N = 5e4+10;
pair<int,int> cows[N];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++) {
        int a,b;
        cin>>a>>b;
        cows[i] = {a+b,b};
    }
    ll res = -1e14,sum = 0;
    sort(cows,cows+n);
    for(int i=0;i<n;i++){
        res = max(res,sum - cows[i].second);
        sum += (cows[i].first-cows[i].second);
    }
    cout<<res<<endl;
    return 0;
}
*/
//雷达设备
// 属于用最少的点覆盖所有的区间问题 与求解一系列区间中最多的不重叠的区间数目相同方法
// 对于区间按照**终点**排序 每个点选取当前区间的最后端点 只在需要的时候增加点
/*
const int N = 1e3+10;
pair<double,double> intervals[N];
int main(){
    int n;
    double d,x,y,len;
    cin>>n>>d;
    bool judge = true;
    for(int i=0;i<n;i++){
        cin>>x>>y;
        if(y>d) judge = false;
        len = sqrt(d*d-y*y);
        // intervals[i] = {x - len,x + len}; 错误 应该按照右端点排序
        intervals[i] = {x+len,x-len};
    }
    if(judge==false){
        cout<<-1<<endl;
    }else{
        sort(intervals,intervals+n);

        double lastx = -2e7;
        int res = 0;
        for(int i=0;i<n;i++){
            if(lastx<intervals[i].second){
                res ++;
                lastx = intervals[i].first;
            }
        }
        cout<<res<<endl;
    }
    return 0;
} 
*/

// 给树染色 难题(贪心)
// 贪心：
// 依据1：排序不等式 没有以来情况下优先给大的染色
// 依据2：当解除依赖由于1 一个节点和他的父亲节点必然紧挨(当这个节点当前最大) 可以看成一体
// 依据3：当存在整体后 如果比较选择哪个整体 推导公式得到选择均值大的优先好
// 由于上面的依据==> 由于是一个递归选择的过程 必须先选择上面 并且保证依赖关系
//                 所以可以一边找最大一边合并 直到合并为单一结点 这样保证了合并过程中每次优先合并大的子节点 
//                 从而保证即便对于整棵树的正确性
// 最终做法是：每次找出当前权值最大的非根节点，将其染色顺序排在紧随父节点之后的位置，
//      然后将该点合并进父节点中，更新父节点的权值。直到将所有点都合并进根节点为止。
// note:这样计算太麻烦 需要不断更新判断重新计算 使用增量算法可以方便计算
// typedef pair<int,int> pii;
// const int N = 1e3+10;
// int w[N],fa[N],sz[N];//需要维护size avg方便计算
// double avg[N];
// bool st[N];
/*
错误代码 由于不支持实时修改 可能当前所得到的最大值不是更新后的数值 即错误的数值
所以需要用每次On暴力搜索方式得到目标
int main(){
    int n,r;
    cin>>n>>r;
    int ans = 0;
    for(int i=1;i<=n;i++) cin>>w[i],sz[i]=1,avg[i]=w[i],ans+=w[i];
    int a,b;
    for(int i=0;i<n-1;i++) {
        cin>>a>>b;
        fa[b] = a;
    }
    priority_queue<pii> pq;//就要大根堆
    for(int i=1;i<=n;i++){
        if(i!=r) pq.push({avg[i],i});
    }
    //合并n-1次
    int cnt = 0;//因为pq不支持修改 所以只能这样统计
    while(cnt<n-1){
        int now = pq.top().second;
        pq.pop();
        if(st[now]) continue;
        st[now] = true;
        cout<<now<<endl;
        cnt ++;
        int f = fa[now];
        ans += sz[f]*w[now];
        w[f] += w[now];
        sz[f] += sz[now];
        avg[f] = (double)w[f]/sz[f];
        //根节点的时候 不需要插入
        if(f!=r)
            pq.push({avg[f],f});
    }
    cout<<ans<<endl;
    return 0;
}
*/
//正确代码
/*
int n,r;
int find(){
    //暴力搜索
    int res = -1;
    double nowavg = 0;
    for(int i=1;i<=n;i++){
        if(i!=r && avg[i]>nowavg){
            nowavg = avg[i];
            res  = i;
        }
    }
    return res;
}
int main(){
    while(cin>>n>>r,n||r){
        memset(fa,0,sizeof fa);
        int ans = 0;
        for(int i=1;i<=n;i++) cin>>w[i],sz[i]=1,avg[i]=w[i],ans+=w[i];
        int a,b;
        for(int i=0;i<n-1;i++) {
            cin>>a>>b;
            fa[b] = a;
        }
        for(int i=0;i<n-1;i++){//只需要找到n-1次进行合并即可
            int now = find();
            int f = fa[now];
            ans += sz[f]*w[now];
            w[f] += w[now];
            sz[f] += sz[now];
            avg[f] = (double)w[f]/sz[f];
            avg[now] = -1;//防止被选择
            //坑点 为了保证计算正确性 需要每次合并后将子节点的父节点改成自己的父节点 才能正确增量计算**
            for(int i=1;i<=n;i++)
                if(fa[i]==now)
                    fa[i] = f;
        }
        cout<<ans<<endl;
    }    
    return 0;   
}
*/

//哈弗曼树模型
// 合并果子
// 基于huffmantree构建即可 证明只需要证明首次选择最小最佳并且f[n-1]与f[n]最优解重叠
/*
int main(){
    int n;
    cin>>n;
    priority_queue<int,vector<int>,greater<int>> pq;
    int x;
    for(int i=0;i<n;i++){
        cin>>x;
        pq.push(x);
    }
    int res = 0;
    //仍然采用增量计算 
    while(pq.size()>1){
        int a = pq.top();pq.pop();
        int b = pq.top();pq.pop();
        res += a+b;
        pq.push(a+b);
    }
    cout<<res<<endl;
    return 0;
}
*/
// 对于强化版 大数据情况下需要采用基数排序 + 队列优化
// 由于数据范围有限 使用基数排序很好 On
// 充分应用性质 每次产生的新节点只会更大不会更小 所以将堆插入操作优化为将生成的元素加入新的队列
// 此时由于性质两个队列都是单调的 所以每次只需要在两个队列头部选择即可
/*
const int N = 1e5+10;
queue<long long> a,b;
int cnt[N];
//数据量太大 需要使用scanf 还有一个点过不去 所以需要用快读/使用手写queue
void read(int &x){ //显著提升速度 快了很多
    int f=1;x=0;char s=getchar();
    while(s<'0'||s>'9'){if(s=='-')f=-1;s=getchar();}
    while(s>='0'&&s<='9'){x=x*10+s-'0';s=getchar();}
    x*=f;
}
int main(){
    int n;
    read(n);
    int num;
    for(int i=0;i<n;i++){
        read(num);
        cnt[num] ++;
    }
    for(int i=1;i<=(int)1e5;i++){
        while(cnt[i]--)
            a.push(i);
    }
    long long ans = 0;
    for(int i=0;i<n-1;i++){
        long long x,y;
        if(b.empty() || (!a.empty() && a.front()<b.front())){
            x = a.front();
            a.pop();
        }else{
            x = b.front();
            b.pop();
        }
        if(b.empty() || (!a.empty() && a.front()<b.front())){
            y = a.front();
            a.pop();
        }else{
            y = b.front();
            b.pop();
        }
        ans += (x+y);
        b.push(x+y);
    }
    printf("%lld\n",ans);
    return 0;
}
*/
// 绝对值不等式应用
// 糖果合并 -- 贪心
// 偏数学推导：--> n个未知数 n-1有效方程 所以主需要将其他变量用x1表示出来
//  发现目标表达式变成了绝对值和 采用绝对值不等式 目标变成了中位数
//10^6 提醒了只能用n算法 所以有了贪心
//xi = |x1-c_(i-1)|  c_(i) = a1+...+ai-i*avg = ai+c_(i-1) -avg
/*
typedef long long ll;
const int N = 1e6+10;
ll a[N],c[N];
ll ans,mid,avg;
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++) scanf("%lld",&a[i]),avg+=a[i];
    avg /= n;
    for(int i=1;i<=n;i++) c[i] = c[i-1]+a[i]-avg;
    //利用绝对值不等式 只需要找出中位数
    sort(c+1,c+n+1);
    mid = c[n/2];
    for(int i=1;i<=n;i++) ans += abs(c[i]-mid);
    printf("%lld\n",ans);
    return 0;
}
*/
//区间覆盖 给定一个区间 用最少的区间实现覆盖
//方案：按照区间左端点排序
//      初始start为开头结点 之后选取能覆盖start点的结束点最靠后的区间 并且用结束点更新start
//      直到当前start>目标区间右端点
//note:可能无法完全覆盖
/*
const int N = 1e5+10;
pair<int,int> intervals[N];

int main(){
    int s,t;
    cin>>s>>t;
    int n;
    cin>>n;
    for(int i=0;i<n;i++) cin>>intervals[i].first>>intervals[i].second;
    sort(intervals,intervals+n);
    int tmp = -1e9-10;
    int i=0,news = tmp;
    int res = 0;
    bool success = false;
    while(i<n){
        if(intervals[i].first<=s){
            if(intervals[i].second>tmp)
                tmp = intervals[i].second;
            i++;
        }else if(tmp!=(-1e9-10)){
            s = tmp;
            tmp = -1e9-10;
            res ++;
            if(s>=t) {
                success = true;
                break;
            }
        }else{//没有被更新时候特殊判断
            break;
        }
    }
    if(i==n && tmp>=t) success = true,res ++;
    if(success) 
        cout<<res<<endl;
    else 
        cout<<-1<<endl;
    return 0;
}
*/
// 区间覆盖加强版 p2082 luogu
// 给定n个区间 求覆盖后的总长度 不算严格的贪心
// 重点在于对区间排序
typedef long long ll;
const int N = 1e5+10;
pair<ll,ll> intervals[N];
int main(){
    int n;
    cin>>n;
    for(int i=0;i<n;i++) cin>>intervals[i].first>>intervals[i].second;
    sort(intervals,intervals+n);
    ll res = 0,ed = -1;
    for(int i=0;i<n;i++){
        ll l = intervals[i].first,r = intervals[i].second;
        if(l>ed){
            ed = r;
            res += (r-l+1);
        }else if(r>ed){
            res += (r-ed);
            ed = r;
        }
    }
    cout<<res<<endl;
    return 0;
}
// 也可以用括弧匹配思想 对于括弧位置排序 每次找到一对匹配的最远括弧更新一次答案
// 也需要对于括弧排序 只是通过括弧计数实现匹配统计
