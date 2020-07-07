#include<iostream>
#include<cstring>
#include<algorithm>
#include<queue>
#include<unordered_map>
using namespace std;
//典型bfs 可以使用dfs限制深度搜索这样共容易记录路径 
//如果使用bfs需对于每个节点记录路径 耗费空间 
//所以为了保证可以存储 空间足够需要使用queue 并将内容放入queue
//此外由于无线范围 需要使用map存储st记录表 不能用bool数组
struct Node{
    int idx;
    vector<char> road;//开组空间可能不够
};
int s,t;
void bfs(){
    unordered_map<int,bool> mp;
    queue<Node> q;
    q.push({s});
    mp[s] = true;
    while(q.size()){
        Node top = q.front();
        q.pop();
        int nowidx = top.idx;
        if(nowidx==t){
            cout<<top.road.size()<<endl;
            for(int i=0;i<top.road.size();i++){
                cout<<top.road[i];
            }
            cout<<endl;
            return;
        }
        if(!mp[nowidx*3]){
            Node temp = top;
            temp.idx = nowidx*3;
            temp.road.push_back('H');
            mp[nowidx*3] = true;
            q.push(temp);
        }
        if(!mp[nowidx/2]){
            Node temp = top;
            temp.idx = nowidx/2;
            temp.road.push_back('0');
            mp[nowidx/2] = true;
            q.push(temp);
        }
        

    }
}
int main(){
    while(cin>>s>>t,s||t){
        bfs();
    }
    return 0;
}