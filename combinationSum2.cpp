//
// Created by 54293 on 2019/10/28.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

void comSumSortDFS(std::vector<int>& out,std::set<std::vector<int>>& ret,std::vector<int>& candidates,int target,int index) {
    if (target == 0){
        ret.insert(out);
        return;
    }
    //arget-candidates[index]>=0实现剪枝
    for(int i=index;i<candidates.size()&&target-candidates[index]>=0;i++){
        out.emplace_back(candidates[i]);
        //避免重复传进去i+1而不是i，实现DFS+回溯
        comSumSortDFS(out,ret,candidates,target-candidates[i],i+1);
        out.pop_back();
    }
}

////DFS+回溯+剪枝，通过high的大小决定DFS的深度和递归的深度，排序可以使得在回溯过程中进行剪枝，优化算法
void comSumSort(std::vector<int>& out,std::set<std::vector<int>>& ret,std::vector<int>& candidates,int target,int index) {
    if (target == 0){
        ret.insert(out);
        return;
    }
    if(index==candidates.size())return;
    //对于排序过的数组可直接进行该if判断，可以减少的组合判断，空间和时间消耗减小，实现剪枝
    if(target / candidates[index]==0)return;//或target / candidates[index]<=0或target / candidates[index]==0||target-candidates[index]<0
    else{
        //一个元素只能用1次或者0次
        for (int count = 1; count >= 0; count--) {
            if(count)
                out.emplace_back(candidates[index]);
            //避免元素重复使用，传进去index+1而不是index，实现DFS+回溯
            comSumSort(out,ret,candidates, target - count * candidates[index], index + 1);
            if(count)
                out.pop_back();
        }
    }
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::vector<int> out;
    std::vector<std::vector<int>> ret;
    std::set<std::vector<int>> s;
    std::sort(candidates.begin(),candidates.end());
    comSumSort(out,s,candidates,target,0);
    for(auto vec:s){
        ret.emplace_back(vec);
    }
    return ret;
}

int main(){
    std::vector<int> candidates{10,1,2,7,6,1,5};
    std::vector<std::vector<int>> com=combinationSum(candidates,8);
    for(int i=0;i<com.size();i++){
        for(int j=0;j<com[i].size();j++){
            std::cout<<com[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

