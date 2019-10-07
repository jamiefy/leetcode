//
// Created by anranzhai on 10/3/19.
//
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> threeSum(std::vector<int>& nums) {
    std::vector<std::vector<int>> ret;
    int len=nums.size();
    if(len<3)return ret;
    std::sort(nums.begin(),nums.end());
    for(int cur=0;cur<len-2;cur++){
        if(nums[cur]>0)break;//对于排序过的数组，第一个数大于零后面的肯定大于零，那么加和不可能为零
        int twoSum=-nums[cur];
        for(int low=cur+1,high=len-1;low<high;){
            if(nums[low]+nums[high]<twoSum){
                low++;
            } else if(nums[low]+nums[high]>twoSum){
                high--;
            } else{
                ret.push_back({nums[cur],nums[low],nums[high]});
                //low+1<high or low<high都可以，反正都是越界，但是相比来说low+1<high执行用时更短，内存消耗更少
                while(low+1<high && nums[low+1]==nums[low]){
                    low++;
                }
                while(high-1>low && nums[high-1]==nums[high]){//high-1>lowor low<high都可以，同上
                    high--;
                }
                //跳过无意义的相等数之后不要忘记还要移动指针，同if和else if处理，不然会进入死循环
                low++;
                high--;
            }
        }
        while(cur+1<len-2 && nums[cur+1]==nums[cur]){
            cur++;
        }
    }
    return ret;
}

int main(){
    std::vector<int> vector{-1,0,1,2,-1,-4};
    std::vector<std::vector<int>> ret=threeSum(vector);
    for(int i=0;i<ret.size();i++){
        std::cout<<ret[i][0]<<" "<<ret[i][1]<<" "<<ret[i][2]<<std::endl;
    }
}