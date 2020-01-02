//
// Created by Administator on 2019/12/28.
//
#include <iostream>
#include <vector>

//递归
//leetcode超时
int uniquePaths(int m, int n) {
    if(m==0||n==0||m==1||n==1)
        return std::min(m,n);
    else if(m == 2 && n == 2)
        return 2;
    else if((m == 3 && n == 2) || (m == 2 && n == 3))
        return 3;
    else
        return uniquePaths(m-1,n)+uniquePaths(m,n-1);
}

//动态规划
//时间复杂度：O(m * n)
//空间复杂度：O(m * n)
int uniquePathsDP(int m, int n) {
    if(m==0||n==0||m==1||n==1)
        return std::min(m,n);
    std::vector<std::vector<int>> dp(n,std::vector<int>(m,1));
    for(int i=1;i<=n-1;i++){
        for(int j=1;j<=m-1;j++){
            dp[i][j]=dp[i-1][j]+dp[i][j-1];
        }
    }
    return dp[n-1][m-1];
}

//动态规划,优化空间消耗
//时间复杂度不变O(m*n），空间复杂度变小O(n)。
int uniquePathsDPImp(int m, int n) {
    if(m==0||n==0||m==1||n==1)
        return std::min(m,n);
    std::vector<int> dp(m,1);
    for(int i=1;i<=n-1;i++){
        for(int j=1;j<=m-1;j++){
            dp[j]+=dp[j-1];
        }
    }
    return dp[m-1];
}

int main(){
    std::cout<<uniquePathsDPImp(7,3);
}