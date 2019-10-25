//
// Created by anranzhai on 2019/10/25.
//
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> ret;

bool comSum(std::vector<int>& out,std::vector<int>& candidates,int target,int index) {
    if (target == 0){
        ret.emplace_back(out);
        return true;
    }

    int high = target / candidates[index];
    if(high==0)
        return false;
    else{
        for (int count = high; count >= 0; count--) {
            for (int i = count; i > 0; i--) {
                out.emplace_back(candidates[index]);
            }
            if(!comSum(out, candidates, target - count * candidates[index], index + 1)){
                for (int i = count; i > 0; i--) {
                    out.pop_back();
                }
            }
        }
    }
}

std::vector<std::vector<int>> combinationSum(std::vector<int>& candidates, int target) {
    std::vector<int> out;
    std::sort(candidates.begin(),candidates.end());
    comSum(out,candidates,target,0);
    return ret;
}