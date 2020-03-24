//
// Created by anranzhai on 2020/3/24.
//
#include <iostream>
#include <vector>
#include<string>
#include<unordered_map>

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
    char p=numAToriginal['A']-numATgoal['A']>0?'A':'T';
    cnt += std::abs(numAToriginal['A'] - numATgoal['A']);
    for(auto i = 0; i < len; ++i)
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