//
// Created by anranzhai on 10/5/19.
//
#include <iostream>
#include <vector>

//闭合数k
//为了枚举某些内容，我们通常希望将其表示为更容易计算的不相交子集的总和。考虑有效括号序列 S 的 闭包数：至少存在 index >= 0，
//使得 S[0], S[1], ..., S[2*index+1]是有效的。 显然，每个括号序列都有一个唯一的闭包号。 我们可以尝试单独列举它们。
std::vector<std::string> generateParenthesis(int n) {
    if(n==0)
        return std::vector<std::string>{""};//切记不可用std::vector<std::string>();这是个空vector会在每一步
        // 循环到auto left:generateParenthesis(0)的时候停止循环也不能执行下面往ret里添加元素的步骤
    std::vector<std::string> ret;
    for(int k=0;k<n;k++){
        for(auto left:generateParenthesis(k)){
            for(auto right:generateParenthesis(n-1-k)){
                ret.emplace_back('('+left+')'+right);
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

int main(){
    std::vector<std::string> vec=generateParenthesis(3);;
    for(auto v:vec){
        std::cout<<v<<std::endl;
    }
}