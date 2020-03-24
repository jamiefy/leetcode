//
// Created by anranzhai on 2020/3/24.
//
#include <iostream>
#include <vector>
#include<string>
#include<unordered_map>
//有一种特殊的DNA，仅仅由核酸A和T组成，长度为n，顺次连接
//科学家有一种新的手段，可以改变这种DNA。每一次，科学家可以交换该DNA上两个核酸的位置，也可以将某个特定位置的核酸修改为另一种核酸。
//现在有一个DNA，科学家希望将其改造成另一种DNA，希望你计算最少的操作次数。
//ATTTAA
//TTAATT
//3
int minSwap(std::string original,std::string goal){
    if(original.size()!=goal.size()) return -1;
    int len=original.size();
    std::unordered_map<char, int> numAToriginal;
    std::unordered_map<char, int> numATgoal;
    int cnt = 0;
    for(auto i = 0; i < len; ++i){
        ++numAToriginal[original[i]];
        ++numATgoal[goal[i]];
    }
    //变少的字母少的那一部分肯定是直接改变
    char p=numAToriginal['A']-numATgoal['A']>0?'A':'T';
    //少的个数就是直接改变的次数
    cnt += std::abs(numAToriginal['A'] - numATgoal['A']);
    for(auto i = 0; i < len; ++i)
        //变多的字母（A或者T）如果直接改变，则肯定存在变少的字母对应他直接改变（因为除去变少的那部分之后其他字母总量不变），
        //因为是求最少操作次数，所以直接交换
        if(original[i] != p && goal[i] == p)
            ++cnt;
}

int main(){
    std::string original;
    std::string goal;
    std::cin>>original;
    std::cin>>goal;
    std::cout<<minSwap(original,goal)<<std::endl;
    return 0;
}