//
// Created by anranzhai on 2020/2/27.
//
#include <iostream>
#include <vector>
int climbStairs(int n) {
    if(n<=2)
        return n;
    return climbStairs(n-1)+climbStairs(n-2);
}

int climbStairsDP(int n) {
    std::vector<int> dp(n+1,0);
    if(n<=2)
        return n;
    dp[1]=1;
    dp[2]=2;
    for(int i=3;i<=n;i++){
        dp[i]=dp[i-1]+dp[i-2];
    }
    return dp[n];
}

int climbStairsDPImp(int n) {
    if(n<=2)
        return n;
    int first=1;
    int second=2;
    for(int i=3;i<=n;i++){
        int cur=first+second;
        first=second;
        second=cur;
    }
    return second;
}

int main(){
    std::cout<<climbStairs(3);
}