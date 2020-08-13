//
// Created by I538989 on 2020/8/5.
//
#include <iostream>
#include <vector>
#include <queue>
using namespace std;
//采用122的峰谷法，不正确，因为最多可以两次而不是所有profit里最大的两个
int maxProfit(vector<int>& prices) {
    if(prices.empty()||prices.size()==1)return 0;
    priority_queue<int> que;
    int valley = prices[0];
    int peak = prices[0];
    for(int i=0;i<prices.size()-1;i++){
        while(i<prices.size()-1&&prices[i]>=prices[i+1])i++;
        valley=prices[i];
        while(i<prices.size()-1&&prices[i]<=prices[i+1])i++;
        peak=prices[i];
        que.emplace(peak-valley);
    }
    int profit=que.top();
    que.pop();
    return que.empty()?profit:profit+que.top();
}

int main(){
    vector<int> nums{1,2,4,2,5,7,2,4,9,0};
    int profit=maxProfit(nums);
    cout<<profit;
}