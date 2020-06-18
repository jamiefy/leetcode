//
// Created by I538989 on 6/18/2020.
//
#include <iostream>
#include <vector>
#include <queue>
#include <functional>
using std::vector;
using std::priority_queue;
int findMaximizedCapital(int k, int W, vector<int>& Profits, vector<int>& Capital) {
    int size=Profits.size();
    if(size==0||k==0) return 0;
    bool flag=true;
    for(auto c:Capital){
        if(W<c)flag= false;
    }
    //如果W大于所有资本则取利润最大的前k个
    if(flag){
        //小顶堆
        priority_queue<int,vector<int>,std::greater<int>> que;
        for(auto p:Profits){
            que.emplace(p);
            if(que.size()>k)que.pop();
        }
        while(!que.empty()){
            W+=que.top();
            que.pop();
        }
        return W;
    }

    //没被开展的项目，以资本递增存储
    priority_queue<std::pair<int,int>,vector<std::pair<int,int>>,std::greater<std::pair<int,int>>> projects;
    for(int i=0;i<size;i++){
        projects.emplace(Capital[i],Profits[i]);
    }
    //可获取的资本小于等于W的项目,以项目利润递减存储
    priority_queue<int> available;
   while(k>0){
       //每次更新available
        while(!projects.empty()&&projects.top().first<=W) {
            available.emplace(projects.top().second);
            projects.pop();
        }
        if(!available.empty()){
            W+=available.top();
            available.pop();
        } else
            break;
        k--;
    }
    return W;
}

