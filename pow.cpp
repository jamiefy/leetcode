//
// Created by Administrator on 2019/11/5.
//
#include <iostream>
#include <cmath>

//暴力实现，超出实现限制
double myPowViolent(double x, int n) {
    //正规做法先列举临界值，虽然不列举在leetcode上也能通过
    if(x==1||x==0)
        return x;
    if(x==-1)
        return n%2==0?-x:x;
    if(n==0)
        //保证返回double值
        return (double)1;

    double num=x;
    long count=2;
    long long countSum;
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

//分情况进行递归
double fastPow(double x, int n){
    if(n==0)
        return 1;
    double half=fastPow(x,n/2);
    if(n%2==0)
        return half*half;
    else
        return half*half*x;
}
//快速幂，分奇偶判断
//时间复杂度：O(logn).每一次我们使用公式 (x^n)^2 = x^(2 * n),n都变为原来的一半.因此我们需要至多O(logn)次操作来得到结果。
//空间复杂度：O(logn).每一次计算,我们需要存储x^n/2的结果。我们需要计算O(logn)次,所以空间复杂度为O(logn)。
double myPow(double x, int n){
    //正规做法先列举临界值
    if(x==1||x==0)
        return x;
    if(x==-1)
        return n%2==0?-x:x;
    if(n==0)
        return (double)1;

    long count=n;
    if(n<0){
        x=1/x;
        count=-count;
    }
    return fastPow(x,count);
}

//使用公式 x^{a + b} = x^a * x^b,可以把n看成一系列正整数之和n=b0+b1+b2+···+bi，如果我们可以很快的得到x^bi的值，计算x^n的总时间
//将被降低。使n的二进制从最低位(LSB)到最高位(MSB)(Least Significant Bit意为最低有效位；MSB（Most Significant Bit)最高有效位)
//表示为b0,b1,b2,b3,...,blength_limit.则n=bi*2^i的加和，由于bi的个数最多为O(logn)，我们可以在O(logn)时间内得到所有的x^(2^i),
//对于所有满足bi=1的i,我们用结果累乘x^(2^i),这也就只需要O(logn)的时间。
//时间复杂度：O(logn). 对每一个 n 的二进制位表示，我们都至多需要累乘 1 次，所以总的时间复杂度为 O(logn) 。
//空间复杂的：O(1). 我们只需要用到 2 个变量来保存当前的乘积和最终的结果 x 。
double myPowBinary(double x, int n){
    //正规做法先列举临界值
    if(x==1||x==0)
        return x;
    if(x==-1)
        return n%2==0?-x:x;
    if(n==0)
        return (double)1;

    long long count=n;
    if(n<0){
        x=1/x;
        count=-count;
    }
    double ans=1;
    double current_product=x;
    for(long long i=count;i>0;i/=2){
        if(i%2==1){
            //eg.当i=count时若b0=1，则说明2^0对应的二进制位为1，应该累乘x^(2^0)也就是x,此时current_product正为初始赋值x
            //eg.当i=count/2时若b1=1，则说明2^1对应的二进制位为1，应该累乘x^(2^1)也就是x^2,此时current_product正为循环一次x*x
            ans=ans*current_product;
        }
        //x^(2^i)=x^(2^(i-1)) * x^(2^(i-1))
        current_product=current_product*current_product;
    }
    return ans;
}

//二进制
//时间复杂度：O(logn).
//空间复杂的：O(1).
double myPowBin(double x, int n){
    if(x==1||x==0)
        return x;
    if(x==-1)
        return n%2==0?-x:x;
    if(n==0)
        return (double)1;
    if(n==INT32_MIN)
        return (double)0;

    int count=n;
    if(n<0){
        x=1/x;
        count=-count;
    }
    int last;
    double ans=1;
    double current_product=x;
    for(int i=0;i<30;i++){
        last=count&0x01;
        if(last!=0){
            ans=ans*current_product;
        }
        count=count>>1;
        if(count==0)break;
        current_product=current_product*current_product;
    }
    return ans;
}

int main(){
    std::cout<<myPowBinary(2,10);
}