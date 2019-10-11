//
// Created by Administrator on 2019/10/11.
//
#include <iostream>
#include <vector>

std::vector<int> searchRange(std::vector<int>& nums, int target) {
    std::vector<int> ret{-1,-1};
    int low=0,high=nums.size()-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        if(nums[mid]==target){
            int start=mid,end=mid;
            //难以保证二分查找对数级的复杂度 时间复杂度可能达到O(n)
            while(--start>=0&&nums[start]==target){}//必须加大括号
            while(++end<=nums.size()-1&&nums[end]==target){}
            ret[0]=++start;
            ret[1]=--end;
            return ret;
        } else if(nums[mid]>target)
            high=mid-1;
        else
            low=mid+1;
    }
    return ret;
}

int searchBound(std::vector<int>& nums,int target,bool left){
    int low=0,high=nums.size();
    while(low<high){
        int mid=low+(high-low)/2;
        if(nums[mid]>target || (left&&nums[mid]==target))
            high=mid;
        else
            low=mid+1;
    }
    return low;
}

//详细解释参见'拓展.md'.1
std::vector<int> searchRangeImp(std::vector<int>& nums, int target) {
    std::vector<int> ret{-1,-1};
    int leftIndex=searchBound(nums,target, true);
    if(leftIndex==nums.size() || nums[leftIndex]!=target)
        return ret;
    ret[0]=leftIndex;
    ret[1]=searchBound(nums,target, false)-1;
    return ret;
}

int searchBoundEqual(std::vector<int>& nums,int target,bool left){
    int low=0,high=nums.size()-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        if(nums[mid]>target || (left&&nums[mid]==target))
            high=mid-1;
        else
            low=mid+1;
    }
    return low;
}

std::vector<int> searchRangeE(std::vector<int>& nums, int target) {
    std::vector<int> ret{-1,-1};
    int leftIndex=searchBoundEqual(nums,target, true);
    if(leftIndex==nums.size()||nums[leftIndex]!=target)
        return ret;
    ret[0]=leftIndex;
    //因为low=mid+1所以减一得到mid对应的值，如果等于目标值则返回mid如果不等于或者low=0则不存在
    //但是前面leftIndex存在所以说明rightIndex绝对存在，所以可以直接填索引值
    ret[1]=searchBoundEqual(nums,target, false)-1;
    return ret;
}

int binarySearch(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size()-1; // 注意

    while(left <= right) {
        int mid = (right + left) / 2;
        if(nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            left = mid + 1; // 注意
        else if (nums[mid] > target)
            right = mid - 1; // 注意
    }
    return -1;
}

int binarySearchBound(std::vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size(); // 注意

    while(left < right) {
        int mid = (right + left) / 2;
        if(nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            left = mid + 1; // 注意
        else if (nums[mid] > target)
            right = mid - 1; // 注意
    }
    //循环没有等于号就要单独判断剩余这个数是否等于目标值
    return nums[left]==target?left:-1;

}

int main(){
    std::vector<int> nums{1,2,3,4,5,6};
    std::cout<<binarySearch(nums,7)<<" "<<binarySearchBound(nums,7)<<std::endl;
}