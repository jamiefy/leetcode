//
// Created by anranzhai on 10/6/19.
//
#include <iostream>
#include <vector>
#include <iterator>

int removeDuplicates(std::vector<int>& nums) {
    for(std::vector<int>::iterator it=nums.begin();it!=nums.end();it++){
        for(auto compare=it+1;compare!=nums.end();compare++){
            if(*it==*compare){
                nums.erase(compare);
                //删除元素后后面的数自动补上来，指针指向原数组compare+1位置的元素
                // 应继续对该位置元素进行判断，通过compare--中和循环的compare++
                compare--;
            }
        }
    }
    return nums.size();
}

int removeDuplicate(std::vector<int>& nums) {
    if(nums.size()==0)return 0;
    int low=0;
    for(int high=1;high<nums.size();high++){
        if(nums[low]!=nums[high]){
            low++;
            nums[low]=nums[high];
        }
    }
    return low+1;
}


int main(){
    std::vector<int> test({0,0,1,1,1,2,2,3,3});
    std::cout<<removeDuplicates(test);
}
