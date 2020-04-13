#include <climits>

//
// Created by anranzhai on 2020/4/13.
//
#include <string>
#include <vector>
#include <iostream>
using namespace std;
void dfs(const string& num, const int target, int pos, string& exp, int len, long prev, long curr, vector<string>* ans){
    if(pos == num.length()){
        if(curr == target) ans->push_back(exp.substr(0, len));
        return;
    }

    long n = 0;
    int s = pos;
    int l = len;
    if(s != 0) ++len;
    while(pos<num.size()){
        n = n*10 + (num[pos]-'0');
        if(num[s] == '0' && pos-s>0) break;
        if(n > INT_MAX) break;
        exp[len++] = num[pos++];
        if(s == 0){
            dfs(num, target, pos, exp, len, n, n, ans);
            continue;
        }
        //len是exp长度
        exp[l] = '+'; dfs(num, target, pos, exp, len, n, curr+n, ans);
        exp[l] = '-'; dfs(num, target, pos, exp, len, -n, curr-n, ans);
        exp[l] = '*'; dfs(num, target, pos, exp, len, prev*n, curr-prev+prev*n, ans);
    }
}
vector<string> addOperatorsMutiply(string num, int target) {
    vector<string> ans;
    string exp(num.length()*2, '\0');
    dfs(num, target, 0, exp, 0, 0, 0, &ans);
    return ans;
}



// path: 目前为止的表达式
// 字符串开始的位置
// eval 目前为止计算的结果
void addOperatorsHelper(string nums, int target, vector<string>& result, string path, int start, long long eval,long long pre) {
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
        long long num=atoll(s.c_str());
        //下一次的开始坐标是start+cnt而不是start+1
        if(start==0)
            addOperatorsHelper(nums,target,result,path+s,start+cnt,eval+num,num);
        else{
            addOperatorsHelper(nums,target,result,path+"+"+s,start+cnt,eval+num,num);
            addOperatorsHelper(nums,target,result,path+"-"+s,start+cnt,eval-num,-num);
            addOperatorsHelper(nums,target,result,path+"*"+s,start+cnt,eval-pre+pre*num,pre*num);
        }
    }
}

vector<string> addOperators(string nums, int target) {
    vector<string> result;
    addOperatorsHelper(nums, target, result, "", 0, 0,0);
    return result;
}

int main(){
    string str;
    getline(cin,str);
    long target;
    cin>>target;
    vector<string> ret=addOperatorsMutiply(str,target);
    for(auto r:ret)
        cout<<r<<endl;
    return 0;
}