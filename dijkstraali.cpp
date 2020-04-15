//
// Created by anranzhai on 2020/4/14.
//
//
// Created by anranzhai on 2020/4/13.
//
//n个城市n个人，每个城市一个人，选择一个城市x，所有人去那聚会，聚合结束所有人返回各自城市。
//有m条单向路径，保证每个人可以到达城市x，一个人所消耗时间为往返距离和，且每个人都会选择最短路径，问最长的距离是多少。
//第一行 输入 n,m,l 对应城市、路径、聚会城市
//接下来m行，x,y,z从城市x到城市y的距离为z
//输出
//输出最长距离
//eg：输入：
//4 8 2
//1 2 4
//1 3 2
//1 4 7
//2 1 1
//2 3 5
//3 1 2
//3 4 4
//4 2 3
//输出10
#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
int mindis(vector<int> &distance,vector<bool> &visited){
    int min=INT32_MAX;
    int pos=-1;
    for(int i=1;i<=distance.size()-1;i++){
        if(!visited[i]&&distance[i]<min){
            min=distance[i];
            pos=i;
        }
    }
    return pos;
}

void dijkstra(int start,vector<int> &dis,vector<map<int,int>> &edge){
    vector<bool> visited(dis.size(), false);
    visited[start]=true;
    for(int i=1;i<visited.size()-1;i++){
        int posmin=mindis(dis,visited);
        visited[posmin]= true;
        for(auto end:edge[posmin]){
            if(dis[end.first]>dis[posmin]+end.second)
                dis[end.first]=dis[posmin]+end.second;
        }
    }
}

int main(){
    int n,m,c;
    cin>>n>>m>>c;
    vector<map<int,int>> edge(n+1,map<int,int>());
    vector<int> distance(n+1,INT32_MAX);
    vector<vector<int>> dis(n+1,distance);
    for(int i=1;i<=m;i++){
        int x,y,l;
        cin>>x>>y>>l;
        dis[x][y]=l;
        edge[x].emplace(y,l);
    }

    for(int i=1;i<=n;i++){
        dis[i][i]=0;
    }
    for(int i=1;i<=n;i++){
        dijkstra(i,dis[i],edge);
    }

    int sum=0;
    for(int i=1;i<=n;i++){
        sum+=dis[i][c];
        sum+=dis[c][i];
    }
    cout<<sum;
    return 0;
}

