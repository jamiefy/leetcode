//
// Created by anranzhai on 2020/2/26.
//
#include <iostream>
#include <math.h>
int mySqrt(int x) {
    if(x==1 || x==0)
        return x;
    long long i=1;
    for(;i*i<=x;)
        i++;
    return i-1;
}

int mySqrtImp(int x) {
    return std::sqrt(x);
}

//平方根运算转换为指数运算和对数运算
//时间复杂度：O(1)
//空间复杂度：O(1)
int mySqrtImprove(int x) {
    if(x==1 || x==0)
        return x;
    int left=std::exp(0.5*log(x));
    return std::pow(left+1,2)>x?left:left+1;
}

//二分查找
//时间复杂度：O(logn)
//空间复杂度：O(1)
int mySqrtBin(int x) {
    if(x<2)
        return x;
    //二分查找,x>=4则x的平方根一定大于等于2小于x/2
    long left=2,right=x/2;
    //left==right时也要进入判断,保证当left==right但left*right>x时right实现减一
    while(left<=right){
        long mid=left+(right-left)/2;
        long product=mid*mid;
        if(product==x)
            return mid;
        else if(product>x)
            right=mid-1;
        else
            left=mid+1;
    }
    return right;
}

//递归+位移
//时间复杂度：O(logn)
//空间复杂度：O(logn),递归栈的深度
int mySqrtRecursive(int x) {
    if (x < 2)
        return x;
    int left=mySqrtRecursive(x>>2)<<1;
    int right=left+1;
    if(right*right>x)
        return left;
    else
        return right;
}

//牛顿法性能最优，此方法是二次收敛的
//时间复杂度：O(logn)
//空间复杂度：O(1)
int mySqrtNewtons(int x){
    if (x < 2)
        return x;
    //牛顿法公式计算值时浮点数不能写成int或者float（使用float时leetcode会提示超出界限），如果x0=x,则收敛但x的平方根
    double x0=x;
    double x1=(x0+x/x0)/2;
    //误差小于1时结束迭代
    while(std::abs(x0-x1)>=1){
        x0=x1;
        x1=(x0+x/x0)/2;
    }
    return int(x1);
}

int main(){
    std::cout<<mySqrtNewtons(8);
}