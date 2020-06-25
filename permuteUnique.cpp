//
// Created by Administrator on 2019/10/30.
//
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
void backTracking(std::set<std::vector<int>> &s,std::vector<int>& nums,std::vector<int>& num){
    if(nums.size()==0)
        s.insert(num);
    for(auto it=nums.begin();it!=nums.end();it++){
        num.emplace_back(*it);
        nums.erase(it);
        backTracking(s,nums,num);
        nums.insert(it,*num.rbegin());
        num.pop_back();
    }
}

std::vector<std::vector<int>> permuteUniquepopback(std::vector<int>& nums) {
    std::set<std::vector<int>> s;
    std::vector<int> num;
    backTracking(s,nums,num);
    std::vector<std::vector<int>> ret;
    for(auto it=s.begin();it!=s.end();it++){
        ret.emplace_back(*it);
    }
    return ret;
}

void backTracking(std::set<std::vector<int>> &s,int index,std::vector<int>& nums){
    if(index==nums.size())
        s.insert(nums);
    for(int i=index;i<nums.size();i++){
        std::swap(nums[index],nums[i]);
        backTracking(s,index+1,nums);
        std::swap(nums[index],nums[i]);
    }
}

//利用set实现vector不重复,交换
std::vector<std::vector<int>> permuteUniqueSwap(std::vector<int>& nums) {
    std::set<std::vector<int>> s;
    backTracking(s,0,nums);
    std::vector<std::vector<int>> ret;
    for(auto it=s.begin();it!=s.end();it++){
        ret.emplace_back(*it);
    }
    return ret;
}

//极大减小执行时间，减小空间消耗
//DFS+剪枝，用visited标记已经填进去的数，若之前填过或者满足i>0&&nums[i]==nums[i-1]&&!visited[i-1]
//(相同数字按顺序填入或visited[i-1]相同数字按逆序填进去)条件的则剪枝
void DFS(std::vector<std::vector<int>> &ret,std::vector<int>& nums,std::vector<bool> &visited,std::vector<int> &num){
    if(num.size()==nums.size())
        ret.emplace_back(num);
    for(int i=0;i<nums.size();i++){
        if(visited[i]==true||i>0&&nums[i]==nums[i-1]&&!visited[i-1])
            continue;
        visited[i]=true;
        num.emplace_back(nums[i]);
        DFS(ret,nums,visited,num);
        //改变的一定要变回来，保证该层循环过程中visited数组和num数组不变
        visited[i]= false;
        num.pop_back();
    }
}


std::vector<std::vector<int>> permuteUniqueDFS(std::vector<int>& nums) {
    std::vector<std::vector<int>> ret;
    std::vector<bool> visited(nums.size(),false);
    std::vector<int> num;
    //排序是为了保证相等的数索引相连
    std::sort(nums.begin(),nums.end());
    DFS(ret,nums,visited,num);
    return ret;
}

void dfs(vector<int>& nums,int index,vector<vector<int>>& ret){
    if(index==nums.size()){
        ret.push_back(nums);
        return;
    }
    vector<int> cur={};//记录该位选择过的元素值，已经选择过的值不再选择
    for(int i=index;i<nums.size();i++){
        if(find(cur.begin(),cur.end(),nums[i])!=cur.end())continue;
        swap(nums[index],nums[i]);
        cur.push_back(nums[index]);
        dfs(nums,index+1,ret);
        swap(nums[index],nums[i]);
    }
}
//首先，先要给nums进行排序，这样的做目的是方便剪枝
//其次，我们已经选择过的不需要再放进去了
//接下来，如果当前节点与他的前一个节点一样，并其他的前一个节点已经被遍历过了，那我们也就不需要了。
//通过swap实现的回溯，只能通过find来除重。
vector<vector<int>> permuteUniquefind(vector<int>& nums) {
    vector<vector<int>> ret;
    dfs(nums,0,ret);
    return ret;
}

//回溯+剪枝去重
void dfs(vector<int>& nums,int index,vector<bool>& used,vector<int>& cur,vector<vector<int>>& ret) {
    if (index == nums.size()) {
        ret.push_back(cur);
        return;
    }
    //i的初始值为0而不是index，每次都要遍历所有位，从未使用的位中挑选下一位
    for(int i=0;i<nums.size();i++){
         //大前提必须是该位没有被使用过
         if(used[i])continue;
         //如果该位等于前一位且前一位没有被占用则取该位会导致重复，所以去重
         if(i>0&&nums[i-1]==nums[i]&&!used[i-1])continue;
         cur.push_back(nums[i]);
         used[i]=true;
         dfs(nums,index+1,used,cur,ret);
         used[i]=false;
         cur.pop_back();
    }
}

vector<vector<int>> permuteUnique(vector<int>& nums){
    vector<vector<int>> ret;
    sort(nums.begin(),nums.end());
    vector<bool> used(nums.size(),false);
    vector<int> cur;
    dfs(nums,0,used,cur,ret);
    return ret;
}

int main(){
    std::vector<int> vec{2,2,1,1};
    std::vector<std::vector<int>> ret=permuteUnique(vec);
    for(int i=0;i<ret.size();i++){
        for(int j=0;j<ret[0].size();j++){
            std::cout<<ret[i][j]<<' ';
        }
        std::cout<<std::endl;
    }
}