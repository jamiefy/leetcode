//
// Created by anranzhai on 2020/2/29.
//
#include <iostream>
#include <vector>
bool search(std::vector<int>& nums, int target) {
    if(nums.size()==0)
        return false;
    int left=0,right=nums.size()-1;
    while(left<right){
        while(nums[left]==nums[right]){
            left++;
            if(left==right)
                break;
        }
        if(nums[left]==target||nums[right]==target)return true;
        int mid=left+(right-left)/2;
        if(nums[mid]==target)return true;
        else if (nums[mid]==nums[right])
            right=mid-1;
        else if(nums[left]>nums[mid]^nums[left]>target^nums[mid]<target)
            left=mid+1;
        else
            right=mid-1;
    }
    return nums[left]==target;
}

bool searchMinor(std::vector<int>& nums, int target) {
    if(nums.size()==0)
        return false;
    int left=0,right=nums.size()-1;
    while(left<right){
        while(nums[left]==nums[right]){
            left++;
            if(left==right)
                break;
        }
        if(nums[left]==target||nums[right]==target)return true;
        int mid=left+(right-left)/2;
        if(nums[mid]==target)return true;
        else if(nums[mid]==nums[right]||nums[left]<=nums[mid]^nums[left]<target^nums[mid]>target)
            right=mid-1;
        else
            left=mid+1;
    }
    return nums[left]==target;
}

int main(){
    std::vector<int> vec{1,1};
    std::cout<<search(vec,0);
}