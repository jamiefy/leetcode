//
// Created by anranzhai on 2020/3/2.
//
#include <iostream>
#include <vector>
#include <queue>

using PII = std::pair<int, int>;
static constexpr int dirs[4][2] = {{0,  1},
                                            {0,  -1},
                                            {1,  0},
                                            {-1, 0}};

//时间复杂度:O(MNlog(MN))。优先队列优化的 Dijsktra 算法的时间复杂度为 O((M+N)logM)，其中 NN 和 MM 分别是图中的点数和边数。在我们的建模中，点的数量为 MNMN，边的数量不超过 4MN4MN 但与 4MN4MN 同阶，带入即可得到时间复杂度为 O(MN \log (MN))O(MNlog(MN))。
//
//空间复杂度:O(MN)。优先队列优化的 Dijkstra 算法需要用到最多 MM 个元素的优先队列（堆）以及若干长度为 NN 表示状态的数组。带入我们建模中的点数和边数，即可得到空间复杂度为 O(MN)。
int minCostDijkstra(std::vector<std::vector<int>> &grid) {
    if(grid.size()==0 || (grid.size()==1 && grid[0].size()==1))
        return 0;
    int m=grid.size(),n=grid[0].size();
    std::vector<int> dis(m*n,INT_MAX);
    std::vector<int> seen(m*n,0);
    // priority_queue<int,vector<int>,less<int>>等价于priority_deque<int> q;其中第二个参数( vector )，是来承载底层数据结构堆的容器，第三个参数( less )，
    //则是一个比较类，less 表示数字大的优先级高，而 greater 表示数字小的优先级高
    //默认排序是从小到大，先比较first，在first相等的情况下比较second,new_dis作为first将所有节点区分为一层一层的
    std::priority_queue<PII,std::vector<PII>,std::greater<PII>> q;
    dis[0]=0;
    q.emplace(0,0);

    while(!q.empty()){
        auto [cur_dis,cur_pos]=q.top();
        q.pop();

        if(seen[cur_pos])
            continue;
        seen[cur_pos]=1;
        int x = cur_pos / n;
        int y = cur_pos % n;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            int new_pos = nx * n + ny;
            int new_dis = cur_dis + (grid[x][y] != i + 1);

            if(nx>=0&&nx<m&&ny>=0&&ny<n&&new_dis<dis[new_pos]){
                dis[new_pos]=new_dis;
                q.emplace(new_dis,new_pos);
            }
        }
    }
    return dis[m*n-1];
}

//0-1广度优先搜索寻找最短路径，双端队列代替普通先进先出队列
//时间复杂度：O(MN)O(MN)。在常规的广度优先搜索中，每个节点最多被添加进队列一次，而在 0-1 广度优先搜索中，每个节点最多被添加进双端队列两次（即队首一次，队尾一次）。
//空间复杂度：O(MN)，与常规的广度优先搜索一致。
int minCostBFS(std::vector<std::vector<int>>& grid) {
    int m = grid.size();
    int n = grid[0].size();
    std::vector<int> dist(m * n, INT_MAX);
    std::vector<int> seen(m * n, 0);
    dist[0] = 0;
    std::deque<int> q;
    q.push_back(0);

    while (!q.empty()) {
        auto cur_pos = q.front();
        q.pop_front();
        if (seen[cur_pos]) {
            continue;
        }
        seen[cur_pos] = 1;
        int x = cur_pos / n;
        int y = cur_pos % n;
        for (int i = 0; i < 4; ++i) {
            int nx = x + dirs[i][0];
            int ny = y + dirs[i][1];
            int new_pos = nx * n + ny;
            int new_dis = dist[cur_pos] + (grid[x][y] != i + 1);

            if (nx >= 0 && nx < m && ny >= 0 && ny < n && new_dis < dist[new_pos]) {
                dist[new_pos] = new_dis;
                if (grid[x][y] == i + 1) {
                    q.push_front(new_pos);
                }
                else {
                    q.push_back(new_pos);
                }
            }
        }
    }
    return dist[m * n - 1];
}

int main(){
    std::vector<std::vector<int>> vec{{1,1,1,1},{2,2,2,2},{1,1,1,1},{2,2,2,2}};
    std::cout<<minCostDijkstra(vec);
}