//
// Created by anranzhai on 10/7/19.
//
#include <iostream>
#include <algorithm>

int divide(int dividend, int divisor) {
    if(dividend==INT32_MIN&&divisor==-1)
        return INT32_MAX;
    //异或相同为0，不同为1
    int sign = (dividend > 0) ^ (divisor > 0);
    int ans = 0;

    //正数存在边界问题，采用负数计算
    if(dividend>0) {
        dividend = -dividend;
    }
    if(divisor>0) divisor = -divisor;

//减法提交到leetcode上会超出时间限制，所以采用移位
//    while(dividend<=divisor){
//        dividend-=divisor;
//        count++;
//    }

//dividend = divisor*2^2 + divisor*2^1 + divisor*2^0
//ans = 2^2 + 2^1 + 2^0
//力扣这个不支持负数的移位，-3左移几位都不行
    while(dividend<=divisor) {
        int count = 1, base = divisor;
        while (dividend <= (base << 1)) {
            base <<= 1;
            count <<= 1;
        }
        dividend -= base;
        ans += count;
    }
    return sign?-ans:ans;
}

int divideLC(int dividend, int divisor) {
    //异或相同为0，不同为1
    int sign = (dividend > 0) ^ (divisor > 0);
    long ans = 0;
    long divid=dividend;
    long divis=divisor;
    if(dividend<0) {
        divid = -divid;
    }
    if(divisor<0) divis = -divis;

//减法提交到leetcode上会超出时间限制，所以采用移位
//    while(dividend<=divisor){
//        dividend-=divisor;
//        count++;
//    }

//dividend = divisor*2^2 + divisor*2^1 + divisor*2^0
//ans = 2^2 + 2^1 + 2^0
//力扣这个不支持负数的移位，-3左移几位都不行
    while(divid>=divis) {
        long count = 1, base = divis;
        while (divid >= (base << 1)) {
            base <<= 1;
            count <<= 1;
        }
        divid -= base;
        ans += count;
    }
    if(!sign&&ans>INT32_MAX)return INT32_MAX;
    return sign?-ans:ans;
}

int main(){
    std::cout<<divideLC(-2147483648,
                        -1
    );
}