//
// Created by anranzhai on 10/8/19.
//
#include <iostream>
#include <vector>

int dichotomy(std::vector<int>& nums,int target,int low,int high){
    int mid=low+(high-low)/2;
    if(target==nums[mid])
        return mid;
    else if(target<nums[mid])
        return low<mid?dichotomy(nums,target,low,mid-1):low;
    else
        return mid<high?dichotomy(nums,target,mid+1,high):high+1;
}

int searchInsert(std::vector<int>& nums, int target) {
    if(nums.size()==0)
        return 0;
    return dichotomy(nums,target,0,nums.size()-1);
}

//直接循环判断快于递归
int searchInsertImp(std::vector<int>& nums, int target) {
    int left = 0, right = nums.size() - 1;
    while (left <= right) {
        int mid =left+ (-left + right) / 2;
        if (nums[mid] == target) {
            return mid;
        } else if (nums[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return left;//返回小于等于target的最大索引值
}