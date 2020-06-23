//
// Created by I538989 on 6/23/2020.
//
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int partition(vector<int>& nums, int left,int right){
    int value=nums[right];
    while(left<right){
        while(nums[left]>=value&&left<right)left++;
        nums[right]=nums[left];
        while(nums[right]<value&&left<right)right--;
        nums[left]=nums[right];
    }
    nums[left]=value;
    return left;
}

int findKthLargestPartition(vector<int> nums, int k) {
    int left=0,right=nums.size()-1;
    while(left<=right){
        int pos=partition(nums,left,right);
        if(pos==k-1)
            return nums[pos];
        else if(pos<k-1)
            left=pos+1;
        else
            right=pos-1;
    }
    return -1;
}

int findKthLargest(vector<int> nums, int k) {
    priority_queue<int,vector<int>,greater<>> que;
    for(auto& n:nums){
        que.emplace(n);
        if(que.size()>k)
            que.pop();
    }
    return que.top();
}

int main()
{
    cout<<findKthLargest({3,2,1,5,6,4},2);
}