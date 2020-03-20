//
// Created by anranzhai on 2020/3/20.
//
#include <iostream>
#include <vector>
//双指针
void moveZeroes(std::vector<int>& nums) {
    if(nums.size()==0||nums.size()==1)
        return;
    int i=0,j=1;
    for(;i<nums.size()&&j<nums.size();j++){
        if(nums[i]==0){
            if(nums[j]!=0){
                nums[i++]=nums[j];
                nums[j]=0;
            }
        } else{
            i++;
        }
    }
}

void moveZeroesImp(std::vector<int>& nums) {
    int lastNonZeroFoundAt = 0;
    // If the current element is not 0, then we need to
    // append it just in front of last non 0 element we found.
    for (int i = 0; i < nums.size(); i++) {
        if (nums[i] != 0) {
            nums[lastNonZeroFoundAt++] = nums[i];
        }
    }
    // After we have finished processing new elements,
    // all the non-zero elements are already at beginning of array.
    // We just need to fill remaining array with 0's.
    for (int i = lastNonZeroFoundAt; i < nums.size(); i++) {
        nums[i] = 0;
    }
}

//如果当前元素是非 0 的，那么它的正确位置最多可以是当前位置或者更早的位置
//用swap函数，执行时间消耗更多一些
void moveZeroesSwap(std::vector<int>& nums) {
    for (int lastNonZeroFoundAt = 0, cur = 0; cur < nums.size(); cur++) {
        if (nums[cur] != 0) {
            std::swap(nums[lastNonZeroFoundAt++], nums[cur]);
        }
    }
}