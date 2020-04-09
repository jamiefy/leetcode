//
// Created by anranzhai on 2020/4/9.
//
//无序正整数数组，求最小不存在的数
#include <iostream>
#include <vector>
int minNoExist(std::vector<int> &nums){
    if(nums.size()==0)
        return 1;
    if(nums.size()==1)
        return nums[0]+1;
    int left=0;
    int right=nums.size();
    while(left<right){
        if(nums[left]=left+1)
            left++;
        else if(nums[left]<=left || nums[left]>right || nums[left]==nums[nums[left]-1])
            nums[left]=nums[--right];
        else
            std::swap(nums[left],nums[nums[left]]);
    }
    return left+1;
}
