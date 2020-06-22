//
// Created by anranzhai on 2020/6/21.
//
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
/*
分治归并
    以操作符为界限，将运算表达式分割为两个不同的部分，在递归计算（在这个运算符处分割，其实也是代表将这个运算符最后一个算）
    递归终止条件：字符串中就一个数字
    在递归的过程中，会有一部分字符串会重复多次计算，所以在前面的基础上加入哈希表，同空间换时间，时间确实快了，从12ms->4ms
*/
bool isOp(const char& c){
    return c == '+' || c == '-' || c == '*';
}

int calculate(const int& num1, const char& op, const int& num2){
    if(op == '+')
        return num1 + num2;
    else if(op == '-')
        return num1 - num2;
    else
        return num1 * num2;
}

vector<int> diffWaysToCompute(string input) {
    if(input.size()==0)
        return vector<int>();
    int num=0;
    int index=0;
    for(;index<input.size()&&isdigit(input[index]);index++){
        num=num*10+input[index]-'0';
    }
    unordered_map<string,vector<int>> nmap;
    if(index==input.size()){
        nmap[input]=vector<int>{num};
        return nmap[input];
    }
    vector<int> ret;
    for(int i=0;i<input.size();i++){
        if(isOp(input[i])){
            string s1 = input.substr(0,i);
            string s2 = input.substr(i+1);
            vector<int> result1,result2;
            if(nmap.count(s1))
                result1=nmap[s1];
            else
                result1=diffWaysToCompute(input.substr(0,i));
            if(nmap.count(s2))
                result2=nmap[s2];
            else
                result2=diffWaysToCompute(input.substr(i+1));
            for(auto r1:result1){
                for(auto r2:result2){
                    ret.push_back(calculate(r1,input[i],r2));
                }
            }
        }
    }
    nmap[input]=ret;
    return ret;
}
