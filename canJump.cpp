//
// Created by Administator on 2019/12/6.
//
#include <iostream>
#include <vector>
#include <algorithm>

//递归：查找第一个零之前的位置能通过跳跃达到的最远的位置，然后就可以从该位置开始新一轮的判断
//时间复杂度：O(n^2),其中 n 是数组 nums 的元素个数,(1+n)*n/2。
bool search(std::vector<int>::iterator start,std::vector<int>::iterator end,std::vector<int>& nums,int index){
    std::vector<int>::iterator it=std::find(start,end,0);
    if(it==end || it+1==end) return true;
    for(std::vector<int>::iterator iter=start;iter<it;iter++){
        index++;
    }
    int max=0;
    //i>=0表示遍历该零之前所有位置，避免前面跳过的位里能达到更远的地方
    for(int i=index-1;i>=0;i--){
        if(nums[i]>index-i){
            max=std::max(max,nums[i]-index+i);
        }
    }
    if(max){
        it+=max;
        return search(it,end,nums,index+max);
    }
    return false;
}

bool canJump(std::vector<int>& nums) {
    if(nums.size()==0)
        return false;
    return search(nums.begin(),nums.end(),nums,0);
}

//回溯：低效，模拟从第一个位置跳到最后位置的所有方案。从第一个位置开始，模拟所有可以跳到的位置，然后从当前位置重复上述操作，当
//没有办法继续跳的时候，就回溯。
//时间复杂度：O(2^n)，最多有 2^n种从第一个位置到最后一个位置的跳跃方式，其中 n 是数组 nums 的元素个数。leetcode运行速度超出时间限制
//空间复杂度：O(n)，回溯法只需要栈的额外空间
bool backTracking(int position,std::vector<int>& nums){
    if(position==nums.size()-1)
        return true;
    int furthest=std::min((position+nums[position]),(int)(nums.size()-1));
    for(int index=position+1;index<=furthest;index++){
        if(backTracking(index,nums))
            return true;
    }
    return false;
}

bool canJumpBackTracking(std::vector<int>& nums) {
    if(nums.size()==0)
        return false;
    return backTracking(0,nums);
}

int main(){
    std::vector<int> vec{2,0,2,0,1};
    std::cout<<canJumpBackTracking(vec);
}