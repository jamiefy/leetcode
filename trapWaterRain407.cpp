//
// Created by anranzhai on 2020/6/8.
//
#include <vector>
#include <iostream>
#include <queue>
#include <array>
using namespace std;

//思路：从边界最低处A出发，在A的四周，比A处还低的位置B一定能储水。
//B的储水量 = A的高度-B的高度。并将B填充为新的边界。
//如果A的周围没有比A低的，但是A处在边界无法储水。A的周围中最低的位置为新的边界。
//如此，不断收缩储水区域的边界。
//由于每次都要找出边界中最低的位置A。用优先级队列存储边界。<-重中之重
//对位置A还要遍历其四周的位置。整个框架基于bfs。
struct node{
    int x,y,h;
    node(int _x=0,int _y=0,int _h=0):x(_x),y(_y),h(_h){}
    bool operator<(const node& o)const{
        return h > o.h;
    }
};
int trapRainWater(vector<vector<int>>& heightMap) {
    int row=heightMap.size();
    int col=heightMap[0].size();
    if(row<3 || col<3)
        return 0;

    vector<int> directions{-1,0,1,0,-1};
    vector<vector<int>> visited(row,vector<int>(col,0));
    priority_queue<node> que;
    //边界初始化
    for(int i=0;i<row;i++){
        que.emplace(i,0,heightMap[i][0]);
        que.emplace(i,col-1,heightMap[i][col-1]);
        visited[i][0]=visited[i][col-1]=1;
    }
    for(int i=0;i<col;i++){
        que.emplace(0,i,heightMap[0][i]);
        que.emplace(row-1,i,heightMap[row-1][i]);
        visited[0][i]=visited[row-1][i]=1;
    }

    int ans=0;
    while(!que.empty()){
        auto top=que.top();
        que.pop();
        for(int k=0;k<4;k++){
            int r=top.x+directions[k];
            int c=top.y+directions[k+1];
            if(r<0 || c<0 || r>=row || c>=col || visited[r][c]==1)
                continue;
            visited[r][c]=1;
            int fill=max(0,top.h-heightMap[r][c]);
            ans+=fill;
            que.emplace(r,c,max(top.h,heightMap[r][c]));
        }
    }
    return ans;
}

int main(){
    vector<vector<int>> vec{{1,4,3,1,3,2},{3,2,1,3,2,4},{2,3,3,2,3,1}};
    cout<<trapRainWater(vec);
}