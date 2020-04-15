//
// Created by anranzhai on 2020/4/15.
//
#include <bits/stdc++.h>
using namespace std;
//A是有序无重复数组
//暴力循环,前提是数组A无重复数字
int lenLongestFibSubseqCyc(vector<int>& A) {
    int ans=0;
    map<int,int> nums;
    for(int i=0;i<A.size();i++){
        nums.emplace(A[i],i);
    }
    for(int start=0;start<A.size()-1;start++){
        for(int j=start+1;j<=A.size()-1;j++){
            int pre=A[start];
            int cur=A[j];
            int len=2;
            //即使存在以下步骤存在斐波那契数列长度也小于当前最大长度，则直接跳过不进行考虑
            if (ans - 2>A.back() / (pre + cur))
                break;
            while(nums.count(pre+cur)){
                int tmp=cur;
                cur=pre+cur;
                pre=tmp;
                len++;
            }
            ans=max(ans,len);
        }
    }
    return ans>=3?ans:0;
}

//设 longest[i, j] 是结束在 [i, j] 的最长路径。那么 如果 (i, j) 和 (j, k) 是连通的， longest[j, k] = longest[i, j] + 1。
//由于 i 由 A.index(A[k] - A[j]) 唯一确定，所以这是有效的：我们在 i 潜在时检查每组 j < k，并相应地更新 longest[j, k]。
int lenLongestFibSubseq(vector<int>& A) {
    map<int,int> nums;
    vector<vector<int>> dp(A.size(),vector<int>(A.size(),2));
    for(int i=0;i<A.size();i++){
        nums.emplace(A[i],i);
    }
    int ans=0;
    for(int end=0;end<=A.size()-1;end++){
        for(int j=0;j<end;j++) {
            if(A[end]-A[j]<A[j]&&nums.count(A[end]-A[j])){
                dp[j][end]=dp[nums[A[end]-A[j]]][j]+1;
                ans=max(ans,dp[j][end]);
            }
        }
    }
    return ans>=3?ans:0;
}

int main(){
    vector<int> vec{2,4,7,8,9,10,14,15,18,23,32,50};
    cout<<lenLongestFibSubseq(vec);
    return 0;
}