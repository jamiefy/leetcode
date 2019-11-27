//
// Created by Administator on 2019/11/26.
//
#include <iostream>
#include <vector>

//双指针
int maxSubArrayPointer(std::vector<int>& nums) {
    if(nums.size()==1)
        return nums[0];
    //
    int last=nums[0],max=nums[0];
    for(int i=0,j=1;i<j && j<nums.size();){
        //说明last对结果有增益效果
        if(nums[j]<last+nums[j]){
            last=last+nums[j];
            j++;
        } else{//说明last对结果无增益效果
            i=j;
            j=i+1;
            last=nums[i];
        }
        //比较当前值和以往最大值取最大值
        max=std::max(max,last);
    }
    return max;
}

int maxSubArrayDP(std::vector<int>& nums){

}

int maxSubArrayGreedy(std::vector<int>& nums){

}


int maxSubArrayDivision(std::vector<int>& nums){

}

int main(){
    std::vector<int> vec={-1,-2};
    std::cout<<maxSubArrayPointer(vec);
}