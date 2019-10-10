//
// Created by Administrator on 2019/10/9.
//
#include <iostream>
#include <vector>

int search(std::vector<int>& nums, int target) {
    int len=nums.size();
    if(len==0)
        return -1;
    int low=0,high=len-1;
    while(low<=high){
        int mid=low+(high-low)/2;
        if(low==high)
            return nums[mid]==target?low:-1;
        else if(nums[mid]==nums[low]){
            if(nums[low]==target||nums[high]==target){
                return nums[low]==target?low:high;
            }
            return -1;
        }
        //先判断中心点位于左边还是右边
        else if(nums[mid]>nums[low]){//中心点在右边
            if(nums[mid]==target)
                return mid;
            else if(nums[mid]<target || nums[low]>target)
                low=mid+1;
            else
                high=mid-1;
        } else{//中心点在左边
            if(nums[mid]==target)
                return mid;
            else if(nums[mid]>target || nums[high]<target)
                high=mid-1;
            else
                low=mid+1;

        }
    }
    return -1;
}

int searchPivot(std::vector<int>& nums){
    int low=0,high=nums.size()-1;
    if(nums[high]>nums[low])return 0;
    while(low<=high){//三个数7 1 2情况下存在low==high且7 1满足nums[pivot]>nums[pivot+1]
        int pivot=low+(high-low)/2;
        if(nums[pivot]>nums[pivot+1])return pivot+1;
        else{
            if(nums[pivot]>=nums[low])low=pivot+1;
            else high=pivot-1;
        }
    }
    return 0;
}

int searchBi(std::vector<int>& nums,int target,int left,int right) {
    //left=high在有两个数且nums[mid]<target时出现且有可能满足nums[mid]==target
//    while(left<=right){
//        int mid=left+(right-left)/2;
//        if(nums[mid]==target)return mid;
//        else if(nums[mid]>target)right=mid-1;
//        else left=mid+1;
//    }
//    return -1;
    while(left<right){
        int mid=left+(right-left)/2;//单数取中间值，偶数取前一半的最后一个
        if(nums[mid]<target)left=mid+1;
        else right=mid;//当两个数&&nums[mid]>=target时不会一直循环下去，因为两个数时mid=left而不是right
    }
    return left==right&&nums[left]==target?left:-1;;
//    while(left<right){
//        int mid=left+(right-left)/2;
//        if(nums[mid]>target)right=mid-1;
//        else left=mid;//当两个数&&nums[mid]<=target时left=mid一直循环下去
//    }
//    return left==right&&nums[left]==target?left:-1;
}

//logn
int searchBiRecursive(std::vector<int>& nums, int target) {
    int len=nums.size();
    if(len==0)return -1;
    if(len==1)return nums[0]==target?0:-1;
    int pivot=searchPivot(nums);
    if(nums[pivot]==target)return pivot;
    if(pivot==0)return searchBi(nums,target,0,len-1);
    else if(nums[pivot]>target||nums[pivot-1]<target)return -1;
    else if(nums[0]>target)
        return searchBi(nums,target,pivot,len-1);
    else
        return searchBi(nums,target,0,pivot-1);
}

//精妙的异或运算
int searchImp(std::vector<int>& nums, int target) {
    int low=0,high=nums.size()-1;
    while(low<high){
        int mid=low+(high-low)/2;
        //nums[mid] < nums[0]，nums[0] > target，target > nums[mid] 三项均为真或者只有一项为真时向后规约
        if((nums[0] > target) ^ (nums[0] > nums[mid]) ^ (target > nums[mid]))
            low=mid+1;
        else
            high=mid;//high=mid-1会导致low==high时存在正确解
    }
    return low==high&&nums[low]==target?low:-1;
}
int main(){
    std::vector<int> nums{4,5,6,7,0,1,2};
    std::cout<<searchImp(nums,2)<<std::endl;
}