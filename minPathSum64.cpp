//
// Created by Administator on 2020/1/9.
//
#include <iostream>
#include <vector>

//动态规划：左上角->右下角
//时间复杂度：O(m*n)
//空间复杂度：O(1),采用形参矩阵原地动态规划
int minPathSum(std::vector<std::vector<int>>& grid) {
    if(grid.size()==0 || grid[0].size()==0)
        return 0;
    for(int j=1;j<grid[0].size();j++)
        grid[0][j]+=grid[0][j-1];
    for(int i=1;i<grid.size();i++)
        grid[i][0]+=grid[i-1][0];
    if(grid.size()==1 || grid[0].size()==1)
        return grid[grid.size()-1][grid[0].size()-1];
    for(int i=1;i<grid.size();i++){
        for(int j=1;j<grid[0].size();j++){
                grid[i][j]+=std::min(grid[i-1][j],grid[i][j-1]);
        }
    }
    return grid[grid.size()-1][grid[0].size()-1];
}

//动态规划:右下角->左上角
//时间复杂度 ：O(mn)。遍历整个矩阵恰好一次。
//空间复杂度 ：O(1)
int minPathSumDP(std::vector<std::vector<int>>& grid) {
    if(grid.size()==0 || grid[0].size()==0)
        return 0;
    for(int i=grid.size()-1;i>=0;i--){
        for(int j=grid[0].size()-1;j>=0;j--){
            if(i == grid.size() - 1 && j != grid[0].size() - 1)
                grid[i][j] = grid[i][j] +  grid[i][j + 1];
            else if(j == grid[0].size() - 1 && i != grid.size() - 1)
                grid[i][j] = grid[i][j] + grid[i + 1][j];
            else if(j != grid[0].size() - 1 && i != grid.size() - 1)
                grid[i][j] = grid[i][j] + std::min(grid[i + 1][j], grid[i][j + 1]);
            else
                grid[i][j] = grid[i][j];
        }
    }
    return grid[0][0];
}

//动态规划：创建一个一维动态数组
int minPathSumDPSingleDimension(std::vector<std::vector<int>>& grid) {
    if(grid.size()==0 || grid[0].size()==0)
        return 0;
    std::vector<int> dp(grid[0].size(),grid[grid.size()-1][grid[0].size()-1]);
    for(int i=grid.size()-1;i>=0;i--){
        for(int j=grid[0].size()-1;j>=0;j--){
            if(i == grid.size() - 1 && j != grid[0].size() - 1)
                dp[j] = grid[i][j] +  dp[j + 1];
            else if(j == grid[0].size() - 1 && i != grid.size() - 1)
                dp[j] = grid[i][j] + dp[j];
            else if(j != grid[0].size() - 1 && i != grid.size() - 1)
                dp[j] = grid[i][j] + std::min(dp[j], dp[j + 1]);
        }
    }
    return dp[0];
}

//递归
//时间复杂度：O(2^(m+n))，leetcode超时
//空间复杂度：O(m+n)，递归的深度是m+n。
int recursive(std::vector<std::vector<int>>& grid,int i,int j){
    if (i == grid.size() - 1 && j == grid[0].size() - 1) return grid[i][j];
    return grid[i][j]+std::min(recursive(grid,i+1,j),recursive(grid,i,j+1));
}

int minPathSumRecursive(std::vector<std::vector<int>>& grid) {
    if(grid.size()==0 || grid[0].size()==0)
        return 0;
    return recursive(grid,0,0);
}


