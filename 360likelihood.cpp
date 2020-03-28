//
// Created by anranzhai on 2020/3/27.
//
#include <bits/stdc++.h>
//除法分子分母都必须是float，不然
float likelihood(float n, float m);
//B先抽A赢的概率
float funB(float n, float m){
    if(n==0)return 1;
    if(m==0)return 0;
    if(m==1)return 1/(n+1);
    return m/(n+m)*((m-1)/(n+m-1)*likelihood(n,m-2)+n/(n+m-1)*likelihood(n-1,m-1));
}
//A先抽A赢的概率
float likelihood(float n, float m){
    if(n==0)return 0;
    if(m==0)return 1;
    //A抽中的概率+A第一轮没抽中的概率*后期抽中的概率
    return n/(n+m)+m/(n+m)*funB(n,m-1);
}

int main(){
    int n,m;
    std::cin>>n>>m;
    //输出自动补零
    std::cout.setf(std::ios::fixed);
    std::cout<<std::setprecision(4)<<likelihood(n,m)<<std::endl;
    //或者std::cout<<std::fixed<<std::setprecision(4)<<likelihood(n,m)<<std::endl;
}
