//
// Created by anranzhai on 2020/4/27.
//
#include <iostream>
//求n的阶乘乘积末尾有几个零=n个数每个数包含的因子中5的个数的总和
int trailingZeros(int n){
    int cnt=0;
    //n个数里有num=n/5个5的倍数
    int num=n/5;
    while(num!=0){
        //num个数里有num/5个5的倍数
        cnt+=num;
        num/=5;
    }
    return cnt;
}

int main(){
    std::cout<<trailingZeros(5);
    return 0;
}