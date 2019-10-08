//
// Created by anranzhai on 10/8/19.
//
#include <iostream>
#include <vector>
#include <algorithm>

void nextPermutation(std::vector<int>& nums) {
    int len=nums.size();
    for(int left=len-2,right=len-1;left>=0;left--,right--){
        if(nums[left]<nums[right]){
            //nums[left]<nums[right]&&right<len会出现AddressSanitizer内存越界问题
            while(right<len&&nums[left]<nums[right]){right++;}
            int tmp=nums[left];
            nums[left]=nums[right-1];
            nums[right-1]=tmp;
            //实现方法如下
            std::reverse(nums.begin()+left+1,nums.end());
//            [](std::vector<int>& nums,int index){
//                int low=index,high=nums.size()-1;
//                while(low<high){
//                    int tmp=nums[low];
//                    nums[low]=nums[high];
//                    nums[high]=tmp;
//                    low++;
//                    high--;
//                }
//        }(nums,left+1);
            return;
    }
    }
//sort的时间复杂度最好是n*lgn，reverse的时间复杂度是n
//    std::sort(nums.begin(),nums.end());
    std::reverse(nums.begin(),nums.end());
}

int main(){
    std::vector<int> nums{1,2,3};
    nextPermutation(nums);
    for(int i=0;i<nums.size();i++){
        std::cout<<nums[i]<<std::endl;
    }
}
