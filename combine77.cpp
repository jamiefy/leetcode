//
// Created by I538989 on 2020/7/30.
//

//
// Created by I538989 on 2020/7/30.
//
#include <iostream>
#include <vector>
using namespace std;
//递归回溯，分两种情况
void dfs(int n,int k,int num,int cnt,vector<int>& path,vector<vector<int>>& ret){
    if(cnt==k){
        ret.push_back(path);
        return;
    }
    if(num==n+1)
        return;
    //分两种情况，包含该位和不包含该位
    path.push_back(num);
    dfs(n,k,num+1,cnt+1,path,ret);
    path.pop_back();
    dfs(n,k,num+1,cnt,path,ret);
}
vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> ret;
    vector<int> vec;
    dfs(n,k,1,0,vec,ret);
    return ret;
}

//递归迭代，选择该位和该位后面k-1个数字
void dfsrecur(int n,int k,int num,int cnt,vector<int>& path,vector<vector<int>>& ret){
    if(cnt==k){
        ret.push_back(path);
        return;
    }
    if(num==n)
        return;
    for(int i=num+1;i<=n-(k-cnt)+1;i++){
        path.push_back(i);
        dfsrecur(n,k,i,cnt+1,path,ret);
        path.pop_back();
    }
}
vector<vector<int>> combinerecur(int n, int k) {
    vector<vector<int>> ret;
    vector<int> path;
    //第一个数字从1到n，当取第一个数字是i时就不考虑1-（i-1）了，因为前面的数字已经和后面的数字组合过了，再组合会重复
    for(int i=1;i<=n;i++){
        path.push_back(i);
        dfsrecur(n,k,i,1,path,ret);
        path.pop_back();
    }
    return ret;
}

//递归+剪枝
//执行速度极大提高
void dfscut(int n,int k,int num,int cnt,vector<int>& path,vector<vector<int>>& ret){
    if(cnt==k){
        ret.push_back(path);
        return;
    }
    if(num==n)
        return;
    //当剩下的数字不够k个时直接剪枝
    for(int i=num+1;i<=n-(k-cnt)+1;i++){
        path.push_back(i);
        dfscut(n,k,i,cnt+1,path,ret);
        path.pop_back();
    }
}
vector<vector<int>> combinecut(int n, int k) {
    vector<vector<int>> ret;
    vector<int> path;
    //第一个数字从1到n，当取第一个数字是i时就不考虑1-（i-1）了，因为前面的数字已经和后面的数字组合过了，再组合会重复
    for(int i=1;i<=n;i++){
        path.push_back(i);
        dfscut(n,k,i,1,path,ret);
        path.pop_back();
    }
    return ret;
}

//个数的全组合
vector<vector<int>> combine(int k) {
    vector<vector<int>> ret;
    int num=1<<k;
    for(int i=1;i<num;i++){
        vector<int> path;
        for(int j=0;j<k;j++){
            if(i&(1<<j)){
                path.push_back(j+1);
            }
        }
        ret.push_back(path);
    }
    return ret;
}

int main(){
    vector<vector<int>> ret=combine(4);
    cout<<1;
}