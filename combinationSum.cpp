//
// Created by anranzhai on 2019/10/25.
//
#include <iostream>
#include <vector>
#include <set>
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
//动态规划，极大增加时间消耗，同时也了增加空间消耗
std::vector<std::vector<int>> combinationSumDP(std::vector<int>& candidates, int target) {
    std::set<std::vector<int>> out;
    std::vector<std::set<std::vector<int>>> targetVec(target+1,out);
    //把candidates排序保证在i<candidates[j]的情况下直接停止继续判断candidates里比candidates[j]更大的值，
    //因为比i大的值肯定不是通过加和可以等于i的数
    std::sort(candidates.begin(),candidates.end());
    //动态规划思想，从底向上，一步步推导，对于目标值target，它一定是由比它小的数相加得到的。比如5=1+4=2+3，
    //而4=3+1=2+2，3=2+1，2=1+1...，也就是说，从1开始，我们依次求解每个数可以有几种形成的方式，则数值更
    //高的数的组合方式建立在数值低的数的组合方式上得到，显然target=candidates[j]+(target-candidates[j])
    //即target可以由candidates[j]和targetVec[target-candidates[j]]中的数字组合加和得到
    for(int i=1;i<=target;i++){
        for(int j=0;j<candidates.size();j++){
            if(i==candidates[j])
                targetVec[i].emplace(std::vector<int>{i});
            else if(i>candidates[j]){
                for(auto vec:targetVec[i-candidates[j]]){
                    //把candidates[j]加入到组合中，不要忘记在插入set之后再把vec中多余的candidates[j]弹出来
                    //使targetVec[i-candidates[j]](类型是set)中的所有vec自身加和还是i-candidates[j]
                    vec.emplace_back(candidates[j]);
                    //排序是为了使set能识别数字一样的vector使不重复插入
                    std::sort(vec.begin(),vec.end());
                    targetVec[i].insert(vec);
                    vec.pop_back();
                }
            } else
                break;
        }
    }
    std::vector<std::vector<int>> ret;
    for(auto v:targetVec[target])
        ret.emplace_back(v);
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