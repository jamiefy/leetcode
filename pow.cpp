//
// Created by Administrator on 2019/11/5.
//
#include <iostream>
#include <cmath>

//暴力实现，超出实现限制
double myPowViolent(double x, int n) {
    if(n==0)
        return 1;
    double num=x;
    long count=2;
    long countSum;
    if(n<0){
//不能直接countSum=-n,否则当n=-2147483648时，countSum=-n=-2147483648也不能直接使用std::abs()
        countSum=n;
        countSum=-countSum;
    } else
        countSum=n;
    for(;count<=countSum;count*=2){
        num*=num;
    }
    int diff=countSum-count/2;
    for(int i=diff;i>0;i--){
        num*=x;
    }
    return n>0?num:(double)1/num;
}

//递归
double fastPow(double x, int n){
    if(n==0)
        return 1;
    double half=fastPow(x,n/2);
    if(n%2==0)
        return half*half;
    else
        return half*half*x;
}
//时间复杂度：O(\log n)O(logn). 每一次我们使用公式 (x ^ n) ^ 2 = x ^ (2 * n),
//n都变为原来的一半.因此我们需要至多O(logn)次操作来得到结果.空间复杂度：O(logn).
//每一次计算,我们需要存储x^n/2的结果。我们需要计算O(logn)次,所以空间复杂度为O(logn)
//快速幂，分奇偶判断
double myPow(double x, int n){
    long count=n;
    if(n<0){
        x=1/x;
        count=-count;
    }
    return fastPow(x,count);
}

int main(){
    std::cout<<myPow(1,-2147483648);
}