#include <iostream>
#include <vector>
#include <memory>
#include <map>

class Solution {
public:
    // @brief 运行时间220ms 内存消耗9.3M
    std::vector<int> twoSum(std::vector<int>& nums, int target) {
        int length=nums.size();
        std::vector<int> array;
        for(int i=0;i<length;i++){
            for(int j=i+1;j<length;j++){
                if(nums[i]+nums[j]==target){
                    array.emplace_back(i);
                    array.emplace_back(j);
                    return array;
                };
            }
        }
    }
    // @brief 运行时间24ms 消耗内存11.3M
    std::vector<int> twoSumImprove(std::vector<int>& nums, int target) {
        int length=nums.size();
        std::vector<int> array;
        std::map<int,int> map;
        for(int i=0;i<length;i++){
            map[nums[i]]=i;
        }
        for(int i=0;i<length;i++){
            int another=target-nums[i];
            // @brief 确保不重复使用同一个数据加和
            if(map[another] && map[another]!=i){
                array.emplace_back(i);
                array.emplace_back(map[another]);
                break;
            }
        }
        return array;
    }
};

int main() {
    int target;
    std::vector<int> nums={3,6,7,8,2,1,0,5};
    while(std::cin>>target){
        std::shared_ptr<Solution> solution=std::make_shared<Solution>();
        std::vector<int> array=solution->twoSumImprove(nums,target);
        std::cout<<"["<<array[0]<<','<<array[1]<<']';
    }
}