//
// Created by anranzhai on 2020/4/1.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
//最优
void _quicksort(std::vector<int>& nums, int left, int right) {
    if(left>=right)
        return;
    int r = rand() % (right - left + 1)+left; // 随机选一个作为我们的主元
    std::swap(nums[right], nums[r]);
    int base=nums[right];
    int i=left;
    for(int j=left;j<right;j++){
        if(nums[j]<base)
            std::swap(nums[i++],nums[j]);
    }
    //交换中间值和i所在位置
    std::swap(nums[i],nums[right]);
    _quicksort(nums, left, i-1);
    _quicksort(nums, i+1, right);
}

void randomized_quicksort(std::vector<int>& nums, int left, int right) {
    if(left>=right)
        return;
    int i = rand() % (right - left + 1)+left; // 随机选一个作为我们的主元
    std::swap(nums[left], nums[i]);
    int base=nums[left];
    int low=left,high=right;
    while(low<high){
        while(nums[high]>=base && low<high)high--;
        nums[low]=nums[high];
        while(nums[low]<=base && low<high)low++;
        nums[high]=nums[low];
    }
    nums[low]=base;
    randomized_quicksort(nums, left, low-1);
    randomized_quicksort(nums, low+1, right);
}

void quicksort(std::vector<int>& nums, int left, int right) {
    if(left>=right)
        return;
    int i = rand() % (right - left + 1)+left; // 随机选一个作为我们的主元
    std::swap(nums[left], nums[i]);
    int base=nums[left];
    int low=left,high=right;
    while(low<high){
        //high必须放前面,high放前面才能保证每次交换的数包括base，最后交换到中间
        while(nums[high]>=base && low<high)high--;
        if(low<high)
            std::swap(nums[low++],nums[high]);
        while(nums[low]<=base && low<high)low++;
        if(low<high)
            std::swap(nums[low],nums[high--]);
    }
    quicksort(nums, left, low-1);
    quicksort(nums, low+1, right);
}

std::vector<int> sortArray(std::vector<int>& nums) {
    srand((unsigned)time(NULL));
    _quicksort(nums, 0, (int)nums.size() - 1);
    return nums;
}

int main(){
    std::vector<int> vec{5,2,3,7,3,4,1};
    vec=sortArray(vec);
    for(auto v:vec)
        std::cout<<v<<std::endl;
}