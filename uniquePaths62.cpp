//
// Created by Administator on 2019/12/28.
//
#include <iostream>

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

int main(){
    std::cout<<uniquePaths(7,3);
}