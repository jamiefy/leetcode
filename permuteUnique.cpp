//
// Created by Administrator on 2019/10/30.
//
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

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

std::vector<std::vector<int>> permuteUnique(std::vector<int>& nums) {
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

int main(){
    std::vector<int> vec{1,2,1};
    std::vector<std::vector<int>> ret=permuteUniqueDFS(vec);
    for(int i=0;i<ret.size();i++){
        for(int j=0;j<ret[0].size();j++){
            std::cout<<ret[i][j]<<' ';
        }
        std::cout<<std::endl;
    }
}