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
    for(int i=index;i<candidates.size()&&target-candidates[index]>=0;i++){
        out.emplace_back(candidates[i]);
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
    //对于排序过的数组可直接进行该if判断，可以减少大量的组合判断，空间消耗减小，时间消耗极大减小
    if(target / candidates[index]==0)return;//或target / candidates[index]<=0或target / candidates[index]==0||target-candidates[index]<0
    else{
        for (int count = 1; count >= 0; count--) {
            if(count)
                out.emplace_back(candidates[index]);
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
    std::vector<int> candidates{10,1,2,7,6,1,5};
    std::vector<std::vector<int>> com=combinationSum(candidates,8);
    for(int i=0;i<com.size();i++){
        for(int j=0;j<com[i].size();j++){
            std::cout<<com[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}

