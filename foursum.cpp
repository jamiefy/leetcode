//
// Created by anranzhai on 10/4/19.
//
#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> fourSum(std::vector<int>& nums, int target) {
    int len = nums.size();
    std::vector<std::vector<int>> ret;
    if(len<4)
        return ret;
    std::sort(nums.begin(),nums.end());
    for (int curOne = 0; curOne < len - 3; curOne++) {
        //加上下面两行速度和空间消耗明显优化
        if(nums[curOne]+nums[len-1]+nums[len-2]+nums[len-3]<target)continue;
        if(nums[curOne]+nums[curOne+1]+nums[curOne+2]+nums[curOne+3]>target)continue;
        for (int curTwo = curOne + 1; curTwo < len - 2; curTwo++) {
            int twoSum = target - nums[curOne] - nums[curTwo];
            for (int low = curTwo + 1, high = len - 1; low < high;) {
                if (nums[low] + nums[high] < twoSum)
                    low++;
                else if (nums[low] + nums[high] > twoSum)
                    high--;
                else {
                    //emplace_back调用形式更加简洁，直接根据参数初始化临时对象的成员，也就是只调用了一次构造函数
                    // 而push_back是压入对象，需要触发拷贝构造和转移构造
                    //注意在此处使用ret.emplace_back(nums[curOne], nums[curTwo], nums[low], nums[high])是错误的，
                    //因为std::vector<std::vector<int>>里面vector类没有直接使用参数进行初始化的构造函数，必须使用列表
                    //ret.emplace_back(std::vector<int>({nums[curOne], nums[curTwo], nums[low], nums[high]}));正确
                    //ret.emplace_back({nums[curOne], nums[curTwo], nums[low], nums[high]});错误：emplace_back只能填
                    //TODO:参数或类的对象不能填列表（即使vector有列表初始化）
                    ret.push_back({nums[curOne], nums[curTwo], nums[low], nums[high]});
                    while (low + 1 < high && nums[low + 1] == nums[low])
                        low++;
                    while (high - 1 > low && nums[high - 1] == nums[high])
                        high--;
                    low++;
                    high--;
                }
            }
            while(curTwo+1<len-2&&nums[curTwo]==nums[curTwo+1])
                curTwo++;
        }
        while(curOne+1<len-3&&nums[curOne]==nums[curOne+1])
            curOne++;
    }
    return ret;
}

int main(){
    std::vector<int> nums{0,4,-5,2,-2,4,2,-1,4};
    std::vector<std::vector<int>> ret=fourSum(nums,12);
    for(auto vector:ret){
        std::cout<<vector[0]<<" "<<vector[1]<<" "<<vector[2]<<" "<<vector[3]<<" "<<std::endl;
    }
}