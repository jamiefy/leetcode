//
// Created by anranzhai on 2020/7/1.
//
#include <vector>
#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;
using PII=pair<int,int>;
vector<int> smallestRange(vector<vector<int>>& nums) {
    PII low;
    PII high(INT32_MIN,0);
    int left=0,right=0;
    int k=nums.size();
    vector<int> index(k,0);
    priority_queue<PII,vector<PII>,greater<>> minQ;
    for(int i=0;i<k;i++) {
        minQ.emplace(nums[i][index[i]], i);
        if(high.first<nums[i][index[i]])
            high=PII(nums[i][index[i]],i);
    }
    while(minQ.size()>=k){
        low=minQ.top();
        if(high.first-low.first<right-left) {
            left=low.first;
            right=high.first;
        }
       index[low.second]++;
       minQ.pop();
       if(index[low.second]<nums[low.second].size()){
           minQ.emplace(nums[low.second][index[low.second]],low.second);
           if(nums[low.second][index[low.second]]>high.first)
               high=PII(nums[low.second][index[low.second]],low.second);
       }
    }
    return vector<int>{left,right};
}
