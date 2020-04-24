//
// Created by anranzhai on 2020/4/24.
//
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
//动态规划自顶向下
int minimumTotal(vector<vector<int>>& triangle) {
    if(triangle.size()==0)
        return -1;
//    if(triangle.size()==1)没必要的判断不加
//        return triangle[0][0];
    vector<vector<int>> dp(triangle.size(),vector<int>());
    for(int i=1;i<=triangle.size();i++){
        dp[i-1]=vector<int>(i,0);
    }
    dp[0][0]=triangle[0][0];
    int minpath=0;
    for(int i=1;i<triangle.size();i++){
        if(i==triangle.size()-1)
            minpath=dp[i-1][0]+triangle[i][0];
        for(int j=0;j<=i;j++){
            if(j>0 && j<=i-1)
                dp[i][j]=min(dp[i-1][j-1]+triangle[i][j],dp[i-1][j]+triangle[i][j]);
            else if(j==0)
                dp[i][j]=dp[i-1][j]+triangle[i][j];
            else if(j==i)
                dp[i][j]=dp[i-1][j-1]+triangle[i][j];
            if(i==triangle.size()-1 && minpath>dp[i][j]){
                minpath=dp[i][j];
            }
        }
    }
    return minpath;
}

//动态规划自底向上
int minimumTotalDownToTop(vector<vector<int>>& triangle) {
    int n=triangle.size();
    if (n== 0)
        return -1;
//    if (n == 1)去掉执行时间减半
//        return triangle[0][0];
    int size=triangle[n-1].size();
    int dp[size];
    for(int i=0;i<size;i++)
        dp[i]=triangle[n-1][i];
    for(int i=n-2;i>=0;i--){
        for(int j=0;j<=i;j++){
            dp[j]=min(dp[j],dp[j+1])+triangle[i][j];
        }
    }
    return dp[0];
}

int main(){
    vector<vector<int>> vec{{2},{3,4},{6,5,7},{4,1,3,8}};
    cout<<minimumTotalDownToTop(vec);
    return 0;
}