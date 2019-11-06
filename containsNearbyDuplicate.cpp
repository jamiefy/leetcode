//
// Created by Administrator on 2019/11/6.
//
#include <iostream>
#include <vector>
#include <unordered_set>

bool containsNearbyDuplicate(std::vector<int>& nums, int k) {
    std::unordered_set<int> n;
    for(int i=0;i<nums.size();i++){
        if(n.find(nums[i])!=n.end())return true;
        else
            n.insert(std::move(nums[i]));
        if(i>=k)
            n.erase(nums[i-k]);
        }
    return false;
}

int main(){
    std::vector<int> vec{1,2,3,4,5,2,1,4};
    std::cout<<containsNearbyDuplicate(vec,4);
}