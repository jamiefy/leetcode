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
void addOperatorsHelper(string nums, int target, vector<string>& result, string path, int start, long eval) {
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
        //下一次的开始坐标是start+cnt而不是start+1
        if(start==0)
            addOperatorsHelper(nums,target,result,path+s,start+cnt,eval+num);
        else{
            addOperatorsHelper(nums,target,result,path+"+"+s,start+cnt,eval+num);
            addOperatorsHelper(nums,target,result,path+"-"+s,start+cnt,eval-num);
        }
    }
}

void addOperatorsHelper2(string nums, int target, vector<string>& result, string path, int index, long eval,long pre) {
    if (index == nums.length()) {
        if (target == eval) {
            result.emplace_back(path);
        }
        return;
    }
        char s=nums[index];
        long num=s-'0';
        if(index==0)
            addOperatorsHelper2(nums,target,result,path+s,index+1,eval,num);
        else{
            //当前一个值为0时，不能直接连接数字,避免"01"这种以0开头的字符串
            if(pre!=0)
                //用递归实现数字直接相连的可能组合,目前为止计算的结果一定要注意上一个数字的正负号(注意当有*号时不能这么去0开头的数字组合，因为0*1为0但是后面还可以直接续数，而且2*1到2*12不能通过eval-pre+pre*10+(pre>0?num:-num)得到)
                addOperatorsHelper2(nums,target,result,path+s,index+1,eval-pre+pre*10+(pre>0?num:-num),pre*10+(pre>0?num:-num));
            addOperatorsHelper2(nums,target,result,path+"+"+s,index+1,eval+num,num);
            addOperatorsHelper2(nums,target,result,path+"-"+s,index+1,eval-num,-num);
        }
}

vector<string> addOperators(string nums, int target) {
    vector<string> result;
    addOperatorsHelper2(nums, target, result, "", 0, 0,0);
    return result;
}


int main(){
    string str;
    getline(cin,str);
    int target;
    cin>>target;
    vector<string> ret=addOperators(str,target);
    for(auto r:ret)
        cout<<r<<endl;
    return 0;
}