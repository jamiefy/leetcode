//
// Created by anranzhai on 2020/3/3.
//
#include <vector>
int findMin(std::vector<int>& nums,int left,int right) {
    int min=nums[left];
    for(int i=left;i<=right;i++){
        min=std::min(min,nums[i]);
    }
    return min;
}

int findMin(std::vector<int>& nums) {
    if(nums.size()==1)
        return nums[0];
    if(nums.size()==2)
        return nums[0]<=nums[1]?nums[0]:nums[1];
    int left=0,right=nums.size()-1;
    while(left<right){
        int middle=left+(right-left)/2;
        if(nums[left]<nums[right])
            return nums[left];
        if(nums[middle]>nums[middle+1])
            return nums[middle+1];
        if(nums[middle]<nums[middle-1])
            return nums[middle];
        if(nums[left]==nums[middle]&&nums[middle]==nums[right])
            return findMin(nums,left,right);
        else if(nums[left]==nums[middle])
            left=middle+1;
        else if(nums[middle]==nums[right])
            right=middle-1;
        else{
            if(nums[left]<nums[middle])
                left=middle+1;
            else
                right=middle-1;
        }
    }
    return nums[left]<=nums[right]?nums[left]:nums[right];
}

int findMinImp(std::vector<int>& nums) {
    int left=0,right=nums.size()-1;
    while(left<right){
        int mid=left+(right-left)/2;//mid满足left<=mid<right
        if(nums[right]>nums[mid])
            right=mid;
        else if(nums[right]<nums[mid])
            left=mid+1;
        else
            right=right-1;//left<right保证不会超出界限
    }
    return nums[left];//最小值肯定会有的
}

int findMinImprove(std::vector<int>& nums) {
    int low = 0, high = nums.size() - 1;

    while(high - low > 1){
        // skip the same element, this would cause the O(n) run-time compllexity
        while(high - low > 1 && nums[low] == nums[high]){//精妙之笔
            low++;
        }

        // binary search
        int mid = low + (high - low) / 2;
        // If the array is not rotated, then return nums[low].
        // Note: checking the equal situation
        if(nums[low] <= nums[mid] && nums[mid] <= nums[high]){
            return nums[low];
        }

        // move the high pointer to the middle, if sub-array from low to mid is rotated.
        if(nums[low] > nums[mid]){
            high = mid;
            continue;
        }

        // move the low pointer to the middle, if sub-array from mid to high is rotated.
        if(nums[mid] >= nums[high]){
            low = mid;
            continue;
        }
    }

    // checking the edge case.
    if(high == low)  return nums[low];
    return nums[low] < nums[high] ? nums[low]: nums[high];
}