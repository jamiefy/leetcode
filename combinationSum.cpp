//
// Created by anranzhai on 2019/10/25.
//
#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

//DFS+回溯+剪枝,通过递归的深度决定DFS的深度,相比于comSumSort函数空间消耗减少，因为是压进去一个弹出来一个而不是一堆压进去弹出来一堆
void comSumSortDFS(std::vector<int>& out,std::vector<std::vector<int>>& ret,std::vector<int>& candidates,int target,int index) {
    if (target == 0){
        ret.emplace_back(out);
        return;
    }
    for(int i=index;i<candidates.size()&&target-candidates[index]>=0;i++){
        out.emplace_back(candidates[i]);
        comSumSortDFS(out,ret,candidates,target-candidates[i],i);
        out.pop_back();
    }
}

////DFS+回溯+剪枝，通过high的大小决定DFS的深度和递归的深度，排序可以使得在回溯过程中进行剪枝，优化算法
void comSumSort(std::vector<int>& out,std::vector<std::vector<int>>& ret,std::vector<int>& candidates,int target,int index) {
    if (target == 0){
        ret.emplace_back(out);
        return;
    }
    if(index==candidates.size())return;
    int high = target / candidates[index];
    //对于排序过的数组可直接进行该if判断，可以减少大量的组合判断，空间消耗减小，时间消耗极大减小
    if(high==0)return;
    else{
        for (int count = high; count >= 0; count--) {
            for (int i = count; i > 0; i--) {
                out.emplace_back(candidates[index]);
            }
            comSumSort(out,ret,candidates, target - count * candidates[index], index + 1);
            for (int i = count; i > 0; i--) {
                out.pop_back();
            }
        }
    }
}

//DFS+回溯：不排序将数组直接进行回溯
void comSum(std::vector<int>& out,std::vector<std::vector<int>>& ret,std::vector<int>& candidates,int target,int index) {
    //当上层传过来的sum为0时，说明加和成功可以压入ret
    if (target == 0){
        ret.emplace_back(out);
        return;
    }
    //如果上层传过来的sum不为0且index==candidates.size()时，说明已经遍历过candidates中的最后一个数
    //且总的加和不等于target，所以返回上一层
    if(index==candidates.size())return;
    //以每个数单独重复组合成sum需要的最大个数为上限，遍历每个数每种个数与其他数字可能的组合，依次递归调用
    int count = target / candidates[index];
    for (; count >= 0; count--) {
        for (int i = count; i > 0; i--) {
            out.emplace_back(candidates[index]);
        }
        //把剩下数应该的sum和剩下数最开始数字的索引值传进去
        comSum(out,ret,candidates, target - count * candidates[index], index + 1);
        //下层不管有没有成功在返回这层之后都应该把该层压入vector的数弹出（上层压入的回到上层之后才能弹出）
        for (int i = count; i > 0; i--) {
            out.pop_back();
        }
    }
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::vector<int> out;
    std::vector<std::vector<int>> ret;
    std::sort(candidates.begin(),candidates.end());
    comSumSortDFS(out,ret,candidates,target,0);
    return ret;
}

std::vector<std::vector<int>> combinationSumDP(std::vector<int>& candidates, int target) {
    std::unordered_set<std::string> out;
    std::vector<std::unordered_set<std::string>> targetVec(target+1,std::unordered_set<std::string>());
    std::sort(candidates.begin(),candidates.end());
    for(int i=1;i<=target;i++){
        for(int j=0;j<candidates.size();j++){
            if(i==candidates[j])
                targetVec[i].insert(std::to_string(i));
            else if(i>candidates[j]){
                for(auto str:targetVec[i-candidates[j]]){
                    targetVec[i].insert(str+std::to_string(candidates[j]));
                }
            } else
                break;
        }
    }
    std::vector<std::vector<int>> ret;
    for(auto str:targetVec[target]){
        for(auto c:str){

        }
    }
    return ret;
}


int main(){
    std::vector<int> candidates{8,7,4,3};
    std::vector<std::vector<int>> com=combinationSumDP(candidates,11);
    for(int i=0;i<com.size();i++){
        for(int j=0;j<com[i].size();j++){
            std::cout<<com[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}