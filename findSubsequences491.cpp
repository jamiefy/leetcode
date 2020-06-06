//
// Created by anranzhai on 2020/6/5.
//
#include <iostream>
#include <vector>
#include <set>
using namespace std;

void dfs(vector<int>& nums,set<vector<int>>& ret,vector<int>& base,int index){
    for(int i=index+1;i<=nums.size()-1;i++){
        if(nums[i]>=nums[index]){
            vector<int> cur(base);
            cur.push_back(nums[i]);
            ret.emplace(cur);
            dfs(nums,ret,cur,i);
        }
    }
}

vector<vector<int>> findSubsequencesDFS(vector<int>& nums) {
    auto size=nums.size();
    if(size<2)
        return vector<vector<int>>();

    set<vector<int>> ret;
    for(int i=0;i<size-1;i++){
        vector<int> vec{nums[i]};
        dfs(nums,ret,vec,i);
    }
    return vector<vector<int>>(ret.begin(),ret.end());
}


//执行速度极快
void dfs(vector<int>& nums,vector<vector<int>>& ret,vector<int>& base,int index){
    if(index>=nums.size()){
        if(base.size()>=2){
            ret.push_back(base);
        }
        return;
    }

    if(base.empty() || nums[index]>=base.back()){
        base.push_back(nums[index]);
        dfs(nums,ret,base,index+1);
        base.pop_back();
    }
    //当前位与前一位相等,说明 加上前一位跳过该位 与 跳过前一位加上该位 会产生相同的序列，直接返回略去加上前一位跳过该位->去重
    if(index>0&&!base.empty()&&nums[index]==base.back())return;
    //当前位与前一位不相等，
    dfs(nums,ret,base,index+1);
}

vector<vector<int>> findSubsequences(vector<int>& nums) {
    auto size=nums.size();
    if(size<2)
        return vector<vector<int>>();

    vector<vector<int>> ret;
    vector<int> vec;
    dfs(nums,ret,vec,0);
    return ret;
}

int main(){
    vector<int> vec{4,6,7,7};
    vector<vector<int>> ret=findSubsequences(vec);
    cout<<1;
}