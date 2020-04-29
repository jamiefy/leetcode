//
// Created by anranzhai on 2020/4/29.
//
//给定一个无序整型数组arr，找到数组中未出现的最小正整数。
//【举例】
//arr=[-1,2,3,4] 返回1
//arr=[1,2,3,4] 返回5
#include <iostream>
#include <vector>
using namespace std;

int findmin(vector<int> &nums){
    //允许的最小数字为left+1
    int left=0;
    //个数，也是允许的最大数字
    int right=nums.size();
    while(left<right){
        if(nums[left]==left+1)//位置正确，即i+1在i位
            left++;
        //不合法，超出范围，<=left或者>right或者重复即nums[index-1]==nums[left]，可排除上一个if判断index=left+1
        else if(nums[left]>right||nums[left]<=left||nums[nums[left]-1]==nums[left])
            nums[left]=nums[--right];
        else{//>left且<=right但是不该放到left位将其放到正确位置即nums[left]-1位置
            int tmp=nums[left];
            nums[left]=nums[nums[left]-1];
            nums[tmp-1]=tmp;
        }
    }
    return left+1;//left=right-1时已经正在处理第right个数，当left==right时跳出循环，说明此时前left个数均存在在正确位置
}