//
// Created by anranzhai on 2020/6/6.
//
#include <iostream>
#include <vector>
#include <array>
#include <algorithm>
#include <queue>
using namespace std;

//构建一个状态矩阵：
//用第一个bit存储太平洋是否能达到此点
//用第二个bit存储大西洋是否能达到此点
//最终查询点状态为3（二进制为11）的点即可。
int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
bool valid(int r, int c, int R, int C) {
    return r >= 0 && r < R && c >= 0 && c < C;
}
vector<vector<int>> pacificAtlantic(vector<vector<int>>& matrix) {
    vector<vector<int> > res;
    if (matrix.empty()) return res;
    int R = matrix.size();
    int C = matrix[0].size();
    vector<vector<int> > status(R, vector<int>(C, 0));
    queue<pair<int, int> > q;
    for (int i = 0; i < R; ++i) {
        q.push({i, 0});
        status[i][0] |= 1;
        q.push({i, C - 1});
        status[i][C - 1] |= 2;
    }
    for (int i = 0; i < C; ++i) {
        q.push({0, i});
        status[0][i] |= 1;
        q.push({R - 1, i});
        status[R - 1][i] |= 2;
    }
    while (!q.empty()) {
        auto p = q.front();
        q.pop();
        for (int i = 0; i < 4; ++i) {
            int r = p.first + dirs[i][0];
            int c = p.second + dirs[i][1];
            //当位于四周的点的值小于或等于该点的值得时候说明能流向
            if (valid(r, c, R, C) && matrix[r][c] >= matrix[p.first][p.second]) {
                if (status[r][c] != status[p.first][p.second]) {
                    //精华，如果一个为1一个为2则结果为3
                    status[r][c] |= status[p.first][p.second];
                    q.push({r, c});
                }
            }
        }
    }
    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j) {
            if (status[i][j] == 3) {
                res.push_back({i, j});
            }
        }
    }
    return res;
}

//思路是从海洋开始逆流 如果可以逆流到 就标记为1 然后检查两个海洋都可以逆流到的区域
void dfs(vector<vector<int>>& matrix,vector<vector<int>>& aux,int i,int j,int pre){
    if(i<0 || j<0 || i>matrix.size()-1 || j>matrix[0].size()-1 || aux[i][j] || matrix[i][j]<pre)
        return;
    aux[i][j]=1;
    dfs(matrix,aux,i-1,j,matrix[i][j]);
    dfs(matrix,aux,i,j+1,matrix[i][j]);
    dfs(matrix,aux,i+1,j,matrix[i][j]);
    dfs(matrix,aux,i,j-1,matrix[i][j]);
}
vector<vector<int>> pacificAtlanticDFS(vector<vector<int>>& matrix) {
    int row=matrix.size();
    if(row==0)
        return vector<vector<int>>();
    int col=matrix[0].size();

    vector<vector<int>> dplefttop(row,vector<int>(col,0));
    vector<vector<int>> dprightbottom(row,vector<int>(col,0));

    //逆流
    for(int i=0;i<row;i++){
        dfs(matrix,dprightbottom,i,col-1,matrix[i][col-1]);
        dfs(matrix,dplefttop,i,0,matrix[i][0]);
    }

    for(int j=0;j<col;j++){
        dfs(matrix,dprightbottom,row-1,j,matrix[row-1][j]);
        dfs(matrix,dplefttop,0,j,matrix[0][j]);
    }

    vector<vector<int>> ret;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(dplefttop[i][j]&&dprightbottom[i][j])
                ret.push_back(vector<int>{i,j});
        }
    }
    return ret;
}


void bfs(vector<vector<int>>& matrix,vector<vector<int>>& aux,queue<pair<int,int>>& que){
    while(!que.empty()){
        auto i=que.front().first;
        auto j=que.front().second;
        que.pop();
        //流到的区域就置为1
        aux[i][j]=1;
        if(i-1>=0 && matrix[i-1][j]>=matrix[i][j] && aux[i-1][j]!=1)
            que.emplace(i-1,j);
        if(i+1<matrix.size()&& matrix[i+1][j]>=matrix[i][j]&& aux[i+1][j]!=1)
            que.emplace(i+1,j);
        if(j-1>=0 && matrix[i][j-1]>=matrix[i][j] && aux[i][j-1]!=1)
            que.emplace(i,j-1);
        if(j+1<matrix[0].size()&&matrix[i][j+1]>=matrix[i][j]&& aux[i][j+1]!=1)
            que.emplace(i,j+1);
    }
}
vector<vector<int>> pacificAtlanticBFS(vector<vector<int>>& matrix) {
    int row = matrix.size();
    if (row == 0)
        return vector<vector<int>>();
    int col = matrix[0].size();

    vector<vector<int>> pacificAux(row, vector<int>(col, 0));
    vector<vector<int>> atlanticAux(row, vector<int>(col, 0));

    queue<pair<int,int>>  pacificQueue;
    queue<pair<int,int>> atlanticQueue;
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (i == 0 || j == 0) {
                pacificQueue.emplace(i, j);
            }
            if (i == row - 1 || j == col - 1) {
                atlanticQueue.emplace(i, j);
            }
        }
    }

    bfs(matrix, pacificAux, pacificQueue);
    bfs(matrix, atlanticAux, atlanticQueue);

    vector<vector<int>> ret;
    for(int i=0;i<row;i++){
        for(int j=0;j<col;j++){
            if(pacificAux[i][j]&&atlanticAux[i][j])
                ret.push_back(vector<int>{i,j});
        }
    }
    return ret;
}