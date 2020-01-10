//
// Created by Administator on 2020/1/4.
//
#include <iostream>
#include <vector>

//动态规划
//时间复杂度：O(m * n)
//空间复杂度：O(m)
int uniquePathsWithObstacles(std::vector<std::vector<int>>& obstacleGrid) {
    int n=obstacleGrid.size();
    if(n==0)
        return 0;
    int m=obstacleGrid[0].size();
    if(m==0 || obstacleGrid[0][0]==1)
        return 0;
    //采用long避免dp[j]+=dp[j-1];超出int界限
    std::vector<long> dp(m,1);
    for(int i=0;i<=n-1;i++){
        for(int j=0;j<=m-1;j++){
            //如果遇见障碍物，则设置通过此点的路径为0
            if(obstacleGrid[i][j]==1){
                dp[j]=0;
            } else{
                if(i==0 || j==0)
                    dp[j]= j==0 ? dp[j] : dp[j-1];
                else
                    dp[j]+=dp[j-1];
            }
        }
    }
    return dp[m-1];
}

//动态规划(可直接采用形参数组作为动态规划数组-空间复杂度：O(1)，减小空间消耗，但是此题中不可行会超过int的最大界限),所以需要再创建动态数组，会消耗更多的空间
//时间复杂度：O(m * n)
//空间复杂度：O(m * n)
int uniquePathsWithObstaclesDP(std::vector<std::vector<int>>& obstacleGrid) {
    int row=obstacleGrid.size();
    if(row==0)
        return 0;
    int col=obstacleGrid[0].size();
    if(col==0 || obstacleGrid[0][0]==1)
        return 0;
    //采用long避免dp[j]+=dp[j-1];超出int界限
    std::vector<std::vector<long>> dp(row,std::vector<long>(col,1));
    for(int i=0;i<=row-1;i++){
        for(int j=0;j<=col-1;j++){
            //如果遇见障碍物，则设置通过此点的路径为0
            if(obstacleGrid[i][j]==1){
                dp[i][j]=0;
            } else{
                if(i==0 || j==0){
                    if(i!=0 || j!=0)
                        dp[i][j]= j==0 ? dp[i-1][j] : dp[i][j-1];
                }
                else
                    dp[i][j]=dp[i-1][j]+dp[i][j-1];
            }
        }
    }
    return dp[row-1][col-1];
}

int uniquePathsWithObstaclesDp(std::vector<std::vector<int>>& obstacleGrid) {
    int row=obstacleGrid.size();
    if(row==0)
        return 0;
    int col=obstacleGrid[0].size();
    if(col==0 || obstacleGrid[0][0]==1)
        return 0;
    //采用long避免dp[j]+=dp[j-1];超出int界限,设置初始值均为0，经判断可通过则设置为1
    std::vector<std::vector<long>> dp(row,std::vector<long>(col,0));
    //开始节点初始设置为1
    dp[0][0]=1;
    for(int i=0;i<=row-1;i++){
        for(int j=0;j<=col-1;j++){
            //如果遇见障碍物，则设置通过此点的路径为0
            if(obstacleGrid[i][j]==1){
                dp[i][j]=0;
            } else{
                //没有遇见障碍物的情况下，第一行和第一列均仅能进入一个if，其他节点两个if均能进入
                if(i-1>=0)
                    dp[i][j]+=dp[i-1][j];
                if(j-1>=0)
                    dp[i][j]+=dp[i][j-1];
            }
        }
    }
    return dp[row-1][col-1];
}

int main(){
    std::vector<int> row1{0,0,0},row2{0,1,0},row3{0,0,0};
    std::vector<std::vector<int>> vec{row1,row2,row3};
    std::cout<<uniquePathsWithObstaclesDp(vec);
}