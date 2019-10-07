//
// Created by anranzhai on 10/7/19.
//
#include <iostream>
#include <vector>

int removeElement(std::vector<int>& nums, int val) {
    for(auto item=nums.begin();item!=nums.end();){
        if(*item==val)
            nums.erase(item);
        else
            item++;
    }
    return nums.size();
}


int removeElementDoublePointer(std::vector<int>& nums, int val) {
    int low=0,high=0;
    for(;high<nums.size();high++){
        if(nums[high]!=val){
            nums[low]=nums[high];
            low++;
        }
    }
    //把多余入栈的high-low个弹出
    while(low++<high)
        nums.pop_back();
    return nums.size();
    //或者直接不弹出直接return low;
}

//当要删除的元素少的时候运行效率极高
int removeElementSwap(std::vector<int>& nums, int val) {
    int cur=0;
    int len=nums.size();
    for(;cur<len;){
        if(nums[cur]==val){
            nums[cur]=nums[len-1];
            len--;
        }
        else
            cur++;
    }
    return len;
}

int main(){
    std::vector<int> nums{3,2,2,3};
    std::cout<< removeElementSwap(nums,3);
}