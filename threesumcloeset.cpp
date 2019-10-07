//
// Created by anranzhai on 10/3/19.
//
#include <iostream>
#include <vector>
#include <algorithm>

int threeSumClosest(std::vector<int>& nums,int target) {
    int len=nums.size();
    if(len<3)return 0;
    std::sort(nums.begin(),nums.end());
    int closest=nums[0]+nums[1]+nums[2];
    for(int cur=0;cur<len-2;cur++){
        int twoSum=target-nums[cur];
        for(int low=cur+1,high=len-1;low<high;){
            if(std::abs(twoSum-nums[low]-nums[high])<std::abs(target-closest)){
                closest=nums[low]+nums[high]+nums[cur];
            }
            if(nums[low]+nums[high]<twoSum){
                low++;
            } else if(nums[low]+nums[high]>twoSum){
                high--;
            } else
                return target;

        }
        //可有可无，因为最后的和存在唯一性，但加上速度快一些，空间消耗少一些
        while(cur+1<len-2 && nums[cur+1]==nums[cur]){
            cur++;
        }
    }
    return closest;
}

int main(){
    std::vector<int> vector{1,1,1,1};
    std::cout<<threeSumClosest(vector,-100)<<std::endl;
}