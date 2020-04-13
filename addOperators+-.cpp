//
// Created by anranzhai on 2020/4/13.
//
#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// path: 目前为止的表达式
// 字符串开始的位置
// eval 目前为止计算的结果
void addOperatorsHelper(string nums, int target, vector<string>& result, string path, int start, long eval,int pre) {
    if (start == nums.length()) {
        if (target == eval) {
            result.emplace_back(path);
        }
        return;
    }
    //用循环实现数字直接相连的可能组合
    for(int cnt=1;cnt<=nums.size()-start;cnt++){
        // "01" 这种以 0 开头的字符串我们不用考虑，可以直接跳过
        if(nums[start]=='0'&&cnt>1)
            break;
        string s=nums.substr(start,cnt);
        long num=atoi(s.c_str());
        if(start==0)
            addOperatorsHelper(nums,target,result,path+s,start+1,eval+num,num);
        else{
            addOperatorsHelper(nums,target,result,path+"+"+s,start+1,eval+num,num);
            addOperatorsHelper(nums,target,result,path+"-"+s,start+1,eval-num,-num);
        }
    }
}

void addOperatorsHelper2(string nums, int target, vector<string>& result, string path, int index, long eval,int pre) {
    if (index == nums.length()) {
        if (target == eval) {
            result.emplace_back(path);
        }
        return;
    }
        char s=nums[index];
        long num=s-'0';
        if(index==0)
            addOperatorsHelper(nums,target,result,path+s,index+1,eval,num);
        else{
            //当前一个值为0时，不能直接连接数字,避免"01"这种以0开头的字符串
            if(pre!=0)
                //用递归实现数字直接相连的可能组合
                addOperatorsHelper(nums,target,result,path+s,index+1,eval-pre+pre*10+num,pre*10+num);
            addOperatorsHelper(nums,target,result,path+"+"+s,index+1,eval+num,num);
            addOperatorsHelper(nums,target,result,path+"-"+s,index+1,eval-num,-num);
        }
}

vector<string> addOperators2(string nums, int target) {
    vector<string> result;
    addOperatorsHelper(nums, target, result, "", 0, 0,0);
    return result;
}


int main(){
    string str;
    getline(cin,str);
    int target;
    cin>>target;
    vector<string> ret=addOperators2(str,target);
    for(auto r:ret)
        cout<<r<<endl;
    return 0;
}