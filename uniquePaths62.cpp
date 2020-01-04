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

int combination(int x,int y){
    if(x==1)
        return 1;
    long product=1;
    int limit=0,remainder=0;
    if(x-y>y) {
        limit = x - y;
        remainder = y;
    }
    else{
        limit=y;
        remainder=x-y;
    }
    for(int i=x;i>limit;i--){
        product*=i;
    }
    for(int i=remainder;i>1;i--){
        product/=i;
    }
    return product;
}
//factorial会超出int 和 long的界限
//int factorial(int x){
//    if(x==1)
//        return 1;
//    return x*factorial(x-1);
//}
//阶乘，任务可叙述为：从m+n-2步中选出哪m-1步是向下走，就可以确定走法数
int uniquePathscombination(int m, int n) {
    if(m==0||n==0||m==1||n==1)
        return std::min(m,n);
//    return factorial(m+n-2)/factorial(m-1)/factorial(n-1);
    return combination(m+n-2,m-1);
}

int main(){
    std::cout<<uniquePathscombination(10,10);
}