//
// Created by anranzhai on 2020/6/2.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <queue>
using namespace std;

//拓扑排序->有向无环图:邻接表+BFS
//时间复杂度 O(N+M)： 遍历一个图需要访问所有节点和所有临边，N 和 M 分别为节点数量和临边数量；
//空间复杂度 O(N+M)： 为建立邻接表所需额外空间，adjacency 长度为 N ，并存储 M 条临边的数据
//执行时间最快
bool canFinishBFS(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> indegrees(numCourses,0);
    vector<vector<int>> adjacencytable(numCourses,vector<int>());
    for(int i=0;i<prerequisites.size();i++){
        adjacencytable[prerequisites[i][1]].emplace_back(prerequisites[i][0]);
        indegrees[prerequisites[i][0]]++;
    }

    queue<int> que;
    for(int i=0;i<numCourses;i++){
        if(indegrees[i]==0)
            que.emplace(i);
    }
    while(!que.empty()){
        auto del=que.front();
        que.pop();
        numCourses--;
        for(auto adjacency:adjacencytable[del]){
            if(--indegrees[adjacency]==0){
                que.emplace(adjacency);
            }
        }
    }
    return numCourses==0;
}

//拓扑排序->有向无环图:邻接表+栈实现的DFS
//时间复杂度 O(N+M)： 遍历一个图需要访问所有节点和所有临边，N 和 M 分别为节点数量和临边数量；
//空间复杂度 O(N+M)： 为建立邻接表所需额外空间，adjacency 长度为 N ，并存储 M 条临边的数据
//执行时间较长
bool canFinishDFS(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> indegrees(numCourses,0);
    vector<vector<int>> adjacencytable(numCourses,vector<int>());
    for(int i=0;i<prerequisites.size();i++){
        adjacencytable[prerequisites[i][1]].emplace_back(prerequisites[i][0]);
        indegrees[prerequisites[i][0]]++;
    }

    stack<int> que;
    for(int i=0;i<numCourses;i++){
        if(indegrees[i]==0)
            que.emplace(i);
    }
    while(!que.empty()){
        auto del=que.top();
        que.pop();
        numCourses--;
        for(auto adjacency:adjacencytable[del]){
            if(--indegrees[adjacency]==0){
                que.emplace(adjacency);
            }
        }
    }
    return numCourses==0;
}


bool dfs(vector<vector<int>>& adjacencytable,vector<int>& flag,int index){
    if(flag[index]==1) return false;//在此次深度优先遍历中已经遍历过一次index，所以存在环
    if(flag[index]==-1)return true;//从index节点向下深度优先遍历不存在环
    flag[index]=1;
    for(auto n:adjacencytable[index]){
        if(!dfs(adjacencytable,flag,n)) return false;
    }
    flag[index]=-1;//index的所有邻接点均遍历完
    return true;
}
bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
    vector<int> flag(numCourses,0);//flag:0-未访问，1-访问过一次，-1-已删除
    vector<vector<int>> adjacencytable(numCourses,vector<int>());
    for(int i=0;i<prerequisites.size();i++){
        adjacencytable[prerequisites[i][1]].emplace_back(prerequisites[i][0]);
    }
    for(int i=0;i<numCourses;i++){
        if(!dfs(adjacencytable,flag,i))return false;
    }
    return true;
}

int main(){
    vector<vector<int>> vec{{1,0},{1,2}};
    bool flag=canFinish(3,vec);
    cout<<1;
}