//
// Created by anranzhai on 2020/5/15.
//
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//并查集
vector<int> parent;
vector<int> ranknums;
void init(int n){
    ranknums.resize(n,1);
    for(int i=0;i<n;i++){
        parent.emplace_back(i);
        //      ranknums.emplace_back(1);
    }
}

int find(int x){
    return parent[x]==x?x:parent[x]=find(parent[x]);
}

void unite(int x,int y){
    int xroot=find(x);
    int yroot=find(y);
    if(xroot==yroot)
        return;
    if(ranknums[xroot]>ranknums[yroot])
        parent[yroot]=xroot;
    else{
        if(ranknums[xroot]==ranknums[yroot])
            ranknums[yroot]++;
        parent[xroot]=yroot;
    }
    return;
}

int findCircleNum(vector<vector<int>>& M) {
    int n=M.size();
    if(n==0)return 0;
    init(n);
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(M[i][j])
                unite(i,j);
        }
    }
    int cnt=0;
    for(int i=0;i<n;i++){
        if(parent[i]==i)
            cnt++;
    }
    return cnt;
}

//广度优先搜索bfs
int findCircleNumbfs(vector<vector<int>>& M) {
    auto n = M.size();
    if (n == 0)return 0;
    queue<int> que;
    vector<bool> visited(n, false);
    auto cnt=0;
    for(auto i=0;i<n;i++){
        if(!visited[i]){
            que.emplace(i);
            while(!que.empty()){
                auto front=que.front();
                que.pop();
                for(int j=0;j<n;j++){
                    if(M[front][j]&&!visited[j]){
                        visited[j]=true;
                        que.emplace(j);
                    }
                }
            }
            cnt++;
        }
    }
    return cnt;
}

//深度优先搜索
void dfs(vector<vector<int>>& M,vector<int>& visited,int index)
{
    for(int i=0;i<M.size();i++){
        if(M[index][i]&&visited[i]==0){
            visited[i]=1;
            dfs(M,visited,i);
        }
    }
    return;
}
int findCircleNumdfs(vector<vector<int>>& M) {
    auto n = M.size();
    if (n == 0)return 0;
    vector<int> visited(n,0);
    int cnt=0;
    for(int i=0;i<n;i++){
        if(visited[i]==0){
            visited[i]=1;
            dfs(M,visited,i);
            cnt++;
        }
    }
    return cnt;
}


class Solution {
public:
    void init(int n){
        for(int i=0;i<n;i++){
            parent.emplace_back(i);
            rank.emplace_back(0);
        }
    }

    int find(int x){
        return parent[x]==x?x:parent[x]=find(parent[x]);
    }

    void unite(int x,int y){
        int xroot=find(x);
        int yroot=find(y);
        if(xroot==yroot)return;
        if(rank[xroot]<rank[yroot])
            parent[xroot]=yroot;  // 合并是从rank小的向rank大的连边
        else
        {
            parent[yroot]=xroot;
            if(rank[xroot]==rank[yroot]) rank[xroot]++;
        }
        return;
    }

    int findCircleNum(vector<vector<int>>& M) {
        int n=M.size();
        if(n==0)return 0;
        init(n);
        for(int i=0;i<n;i++){
            for(int j=i+1;j<n;j++){
                if(M[i][j])
                    unite(i,j);
            }
        }
        int cnt=0;
        for(int i=0;i<n;i++){
            if(parent[i]==i)
                cnt++;
        }
        return cnt;
    }
private:
    vector<int> parent;
    vector<int> rank;
};

int main(){
    vector<vector<int>> nums{{1,0,0,1},{0,1,1,0},{0,1,1,1},{1,0,1,1}};
    Solution s;
    cout<<s.findCircleNum(nums);
}