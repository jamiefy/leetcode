//
// Created by anranzhai on 2020/6/27.
//
#include <iostream>
#include <queue>
#include <algorithm>
#include <deque>
using namespace std;
struct Compare {
    //比较函数
    bool operator()(pair<int, int> &a, pair<int, int> &b) {
        return a.first<b.first;
    }
};
//优先队列，插入堆的时间复杂度lgk和堆排序的时间复杂度是klgk
//时间复杂度O(nklgk)
vector<int> maxSlidingWindowPRI(vector<int>& nums, int k) {
    if(nums.size()==0||k==0)
        return vector<int>();
    if(k==1)
        return nums;
    vector<int> ret;
    priority_queue<pair<int,int>,vector<pair<int,int>>,Compare> que;
    for(int i=0;i<nums.size();i++){
        que.push(pair<int,int>(nums[i],i));
        while(i-que.top().second>=k){
            que.pop();
        }
        if(que.size()>=k){
            ret.emplace_back(que.top().first);
        }
    }
    return ret;
}

//双端队列，前面是满足范围的最大的，后面相当于是单调减栈,压进去的是索引
deque<int> deq;
void clear_deq(vector<int>& nums,int i,int k){
    //弹出过期的
    if(!deq.empty()&&deq.front()==i-k)deq.pop_front();
    //使后压入的不大于deq中存在的，这样才能保证队列对列最前端是最大的
    while(!deq.empty()&&nums[deq.back()]<nums[i])deq.pop_back();
}
//时间复杂度: O(N)，每个元素被处理两次- 其索引被添加到双向队列中和被双向队列删除。
//空间复杂度：O(N)，输出数组使用了O(N−k+1) 空间，双向队列使用了O(k)。
vector<int> maxSlidingWindowDEQUE(vector<int>& nums, int k) {
    if(nums.size()==0||k==0)
        return vector<int>();
    if(k==1)
        return nums;
    for(int i=0;i<k;i++){
        clear_deq(nums,i,k);
        deq.push_back(i);
    }
    if(nums.size()<=k)
        return vector<int>{deq.front()};
    vector<int> ret(nums.size()-k+1);
    ret[0]=nums[deq.front()];
    for(int i=k;i<nums.size();){
        clear_deq(nums,i,k);
        deq.push_back(i);
        ret[i-k+1]=nums[deq.front()];
    }
    return ret;
}

vector<int> maxSlidingWindowDEQ(vector<int>& nums, int k) {
    if(nums.size()==0||k==0)
        return vector<int>();
    if(k==1)
        return nums;
    vector<int> ret;
    for(int i=0;i<nums.size();i++){
        clear_deq(nums,i,k);
        deq.push_back(i);
        if(i-k+1>=0)
            ret.push_back(nums[deq.front()]);
    }
    return nums.size()<k?vector<int>{deq.front()}:ret;
}

//从左到右遍历数组，建立数组 left。
//从右到左遍历数组，建立数组 right。
//建立输出数组 max(right[i], left[i + k - 1])，其中 i 取值范围为 (0, n - k + 1)。
//动态规划，时间复杂度O(n),我们对长度为 N 的数组处理了 3次。
//空间复杂度：O(N)，用于存储长度为 N 的 left 和 right 数组，以及长度为 N - k + 1的输出数组。
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    int n=nums.size();
    if(n==0||k==0)
        return vector<int>();
    if(k==1)
        return nums;

    vector<int> left(n);
    left[0]=nums.front();
    vector<int> right(n);
    right[n-1]=nums.back();
    for(int i=1;i<nums.size();i++){
        if(i%k==0)left[i]=nums[i];
        else left[i]=max(left[i-1],nums[j]);

        int j=n-1-i;
        if((j+1)%k==0)right[j]=nums[i];
        else right[j]=max(right[j+1],nums[j]);
    }

    vector<int> ret;
    for(int i=0;i+k-1<n;i++){
        ret.push_back(max(right[i],left[i+k-1]));
    }
    return ret;
}