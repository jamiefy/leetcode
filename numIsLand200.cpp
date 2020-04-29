//
// Created by anranzhai on 2020/4/28.
//
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

//广度优先搜索
//时间复杂度：O(MN)，其中 MM 和 NN 分别为行数和列数。
//
//空间复杂度：O(\min(M, N))，在最坏情况下，整个网格均为陆地，队列的大小可以达到min(M,N)。
int rowdir[4]={-1,0,+1,0};
int coldir[4]={0,+1,0,-1};
void bfs(vector<vector<char>>& grid,int row,int col) {
    queue<pair<int, int>> land;
    land.emplace(row, col);
    //在压入队列的时候就更改grid对应位置的值表示该位置访问过，避免重复压入队列,而不是在弹出的时候更改状态
    grid[row][col] = '0';
    while (!land.empty()) {
        int i = land.front().first;
        int j = land.front().second;
        land.pop();
        for (int k = 0; k < 4; k++) {
            int x = i + rowdir[k];
            int y = j + coldir[k];
            if (x < 0 || y < 0 || x > grid.size() - 1|| y > grid[0].size() - 1 ||grid[x][y] == '0')
                continue;
            else{
                land.emplace(x, y);
                grid[x][y]='0';
            }
        }
    }
}

//深度优先搜索
//时间复杂度：O(MN)，其中 M 和 N 分别为行数和列数。
//空间复杂度：O(MN)，在最坏情况下，整个网格均为陆地，深度优先搜索的深度达到 MN。
void dfs(vector<vector<char>>& grid,int row,int col){
    grid[row][col]='0';
    if(row-1>=0&&grid[row-1][col]=='1')
        dfs(grid,row-1,col);
    if(col+1<grid[0].size()&&grid[row][col+1]=='1')
        dfs(grid,row,col+1);
    if(row+1<grid.size()&&grid[row+1][col]=='1')
        dfs(grid,row+1,col);
    if(col-1>=0&&grid[row][col-1]=='1')
        dfs(grid,row,col-1);
}

int numIslands(vector<vector<char>>& grid) {
    if(grid.size()==0)
        return 0;
    int ans=0;
    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[0].size();j++){
            if(grid[i][j]=='1'){
                dfs(grid,i,j);
                ans++;
            }
        }
    }
    return ans;
}
//并查集
class UnionFind {
public:
    UnionFind(vector<vector<char>>& grid) {
        count = 0;
        int m = grid.size();
        int n = grid[0].size();
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == '1') {
                    parent.push_back(i * n + j);
                    ++count;
                }
                else {
                    parent.push_back(-1);
                }
                rank.push_back(0);
            }
        }
    }

    int find(int i) {
        //并查集的压缩路径，使每个节点都指向根节点
        return parent[i]==i?i:(parent[i]=find(parent[i]));
    }

    void unite(int x, int y) {
        int rootx = find(x);
        int rooty = find(y);
        if (rootx != rooty) {
            if (rank[rootx] < rank[rooty])
                parent[rootx]=rooty;
            else{
                parent[rooty]=rootx;
                if (rank[rootx] == rank[rooty]) rank[rootx] += 1;
            }
            --count;
        }
    }

    int getCount() const {
        return count;
    }

private:
    vector<int> parent;
    vector<int> rank;
    int count;
};

int numLand(vector<vector<char>> &grid) {
    int nr = grid.size();
    if (!nr) return 0;
    int nc = grid[0].size();

    UnionFind uf(grid);
    for (int r = 0; r < nr; ++r) {
        for (int c = 0; c < nc; ++c) {
            if (grid[r][c] == '1') {
                grid[r][c] = '0';
                //对相邻的节点进行相连
                if (r - 1 >= 0 && grid[r-1][c] == '1') uf.unite(r * nc + c, (r-1) * nc + c);
                if (r + 1 < nr && grid[r+1][c] == '1') uf.unite(r * nc + c, (r+1) * nc + c);
                if (c - 1 >= 0 && grid[r][c-1] == '1') uf.unite(r * nc + c, r * nc + c - 1);
                if (c + 1 < nc && grid[r][c+1] == '1') uf.unite(r * nc + c, r * nc + c + 1);
            }
        }
    }

    return uf.getCount();
}


int main(){
    vector<vector<char>> vec{{'1','1','0','0','0'},
                             {'1','1','0','0','0'},
                             {'0','0','1','0','0'},
                             {'0','0','0','1','1'}};
    cout<<numIslands(vec);
}