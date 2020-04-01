//
// Created by anranzhai on 2020/4/1.
//
#include <iostream>
#include <vector>
void sink(std::vector<int> &nums, int index, int maxIndex){
    for(;(index<<1)+1<=maxIndex;) {
        int lson = (index<<1) + 1;
        int rson = (index<<1) + 2;
        int large;
        if (nums[index] < nums[lson])
            large = lson;
        else
            large = index;
        //是右孩子和最大值比较而不是和父亲比较
        if (rson <= maxIndex && nums[large] < nums[rson])
            large = rson;
        if (large != index){
            std::swap(nums[index], nums[large]);
            index=large;
        } else
            break;
    }
}
void buildMaxHeap(std::vector<int> &nums,int maxIndex){
    for(int i=maxIndex>>1;i>=0;i--){
        sink(nums,i,maxIndex);
    }
}
std::vector<int> sortArray(std::vector<int>& nums) {
    int len = (int)nums.size()-1;
    buildMaxHeap(nums, len);
    for (int i = len; i >= 1; --i) {
        std::swap(nums[i], nums[0]);
        len -= 1;
        sink(nums, 0, len);
    }
    return nums;
}

int main(){
    std::vector<int> vec{5,2,3,7,3,4,1};
    vec=sortArray(vec);
    for(auto v:vec)
        std::cout<<v<<std::endl;
}