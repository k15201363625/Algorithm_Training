#include<iostream>
#include<cstring>
#include<cstdio>
using namespace std;
//构建树
struct TreeNode{
    int left,right;
}bst[30];
void insert(int root,int v){
    if(root>v){
        if(bst[root].left==0) bst[root].left = v;
        else insert(bst[root].left,v);
    }else{
        if(bst[root].right==0) bst[root].right = v;
        else insert(bst[root].right,v);
    }
}
void preorder_traverse(int root){
    if(root==0) return;
    cout<<char('A'+root-1);
    preorder_traverse(bst[root].left);
    preorder_traverse(bst[root].right);
}
string info[27];
int cnt = 0;
int build(){
    memset(bst,0,sizeof bst);
    int root = info[cnt-1][0] - 'A' + 1;
    for(int i=cnt-1;i>=0;i--){
        int j = 0;
        if(i==cnt-1) j = 1;
        while(j<info[i].length()){
            insert(root,info[i][j]-'A'+1);
            j++;
        } 
    }
    return root;
}
int main(){
    char str[27];
    int root = 0;
    while(cin>>str){
        if(str[0]=='$'){
            root = build();
            preorder_traverse(root);
            cout<<endl;
            break;
        }
        if(str[0]=='*'){
            root = build();
            preorder_traverse(root);
            cout<<endl;
            root = 0;
            cnt = 0;
            continue;
        }
        info[cnt++] = str;
        /*
        if(!root){
            //不能只清空root 需要清空其余数据位
            memset(bst,0,sizeof bst);
            root = str[0] - 'A' + 1;
            for(int i=1;i<strlen(str);i++){
                insert(root,str[i]-'A'+1);
            }
        }else{
            for(int i=0;i<strlen(str);i++){
                insert(root,str[i]-'A'+1);
            }
        }
        */
    }
    return 0;
}