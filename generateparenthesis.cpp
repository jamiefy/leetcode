//
// Created by anranzhai on 10/5/19.
//
#include <iostream>
#include <vector>

//闭合数k
std::vector<std::string> generateParenthesis(int n) {
    std::vector<std::string> ret;
    if(n==0)
        ret.emplace_back("");
    else{
        for(int k=0;k<n;k++){
            for(auto left:generateParenthesis(k)){
                for(auto right:generateParenthesis(n-1-k)){
                    ret.emplace_back('('+left+')'+right);
                }
            }
        }

    }
    return ret;
}

//回溯法
void backtracking(std::vector<std::string> &ret,std::string cur,int left,int right,int n){
    if(cur.length()==2*n){
        ret.emplace_back(cur);
        return;
    } else{
        if(left<n)
            backtracking(ret,cur+'(',left+1,right,n);
        if(right<left)
            backtracking(ret,cur+')',left,right+1,n);
    }
}

std::vector<std::string> generateParentheisBacktracking(int n) {
    std::vector<std::string> ret;
    backtracking(ret,"",0,0,n);
    return ret;
}



//暴力枚举法,leetcode上会超出内存限制
std::vector<std::string> ret;
bool isValid(std::string s){
    int balance = 0;
    for (char c: s) {
        if (c == '(') balance++;
        else balance--;
        if (balance < 0) return false;
    }
    return (balance == 0);
}

void generateAll(std::string s,int n){
    if(s.size()==2*n){
        if(isValid(s))ret.emplace_back(s);
    }
    else if(s.size()==0)generateAll(s+'(',n);
    else{
        s+='(';
        generateAll(s,n);
        s+=')';
        generateAll(s,n);
    }
}

std::vector<std::string> generateParentheisEnumerateing(int n) {
    generateAll("",n);
    return ret;
}

