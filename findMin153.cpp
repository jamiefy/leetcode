//
// Created by anranzhai on 2020/2/29.
//
#include <vector>
int findMin(std::vector<int>& nums) {
    if(nums[0]<=nums[nums.size()-1])
        return nums[0];
    int left=0,right=nums.size()-1;
    while(left<=right){
        int mid=left+(right-left)/2;
        if(nums[left]==nums[mid]){
            return nums[left]<nums[right]?nums[left]:nums[right];
        }
        else if(nums[left]<nums[mid])
            left=mid;
        else if(nums[left]>nums[mid])
            right=mid;
    }
    return -1;
}

int findMinOther(std::vector<int> nums) {
    if(nums[0]<=nums[nums.size()-1])
        return nums[0];
    int left=0,right=nums.size()-1;
    //进去的都是至少三个的
    while (right >= left) {
        // Find the mid element
        int mid = left + (right - left) / 2;

        // if the mid element is greater than its next element then mid+1 element is the smallest
        // This point would be the point of change. From higher to lower value.
        if (nums[mid] > nums[mid + 1]) {
            return nums[mid + 1];
        }

        // if the mid element is lesser than its previous element then mid element is the smallest
        if (nums[mid - 1] > nums[mid]) {
            return nums[mid];
        }

        // if the mid elements value is greater than the 0th element this means
        // the least value is still somewhere to the right as we are still dealing with elements
        // greater than nums[0]
        if (nums[mid] > nums[0]) {
            left = mid + 1;
        } else {
            // if nums[0] is greater than the mid value then this means the smallest value is somewhere to
            // the left，当是三个的时候此时right=mid-1=left会进入nums[mid - 1] > nums[mid]结束函数，均可以满足mid-1或mid+1不超界
            right = mid - 1;
        }
    }
    return -1;
}
