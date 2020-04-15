//
// Created by anranzhai on 2020/4/15.
//
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;
//暴力递归，内部错误
int existNext(vector<int>::iterator it,int diff,vector<int> &A){
    if(it+1==A.end())
        return 1;
    it=find(it+1,A.end(),*it+diff);
    if(it!=A.end()){
        return existNext(it,diff,A)+1;
    } else
        return 0;
}

int longestArithSeqLengthRecursive(vector<int>& A) {
    int ans=2;
    for(int start=0;start<A.size()-1;start++){
        for(int j=start+1;j<=A.size()-1;j++){
            int diff=A[j]-A[start];
            auto it=find(A.begin()+j+1,A.end(),A[j]+diff);
            if(it!=A.end()){
                ans=max(ans,existNext(it,diff,A)+2);
                if(ans==A.size())
                    return ans;
            }
        }
    }
    return ans;
}
//暴力循环,前提是数组A无重复数字，但是有
int longestArithSeqLengthCyc(vector<int>& A) {
    int ans=0;
    map<int,int> nums;
    for(int i=0;i<A.size();i++){
        nums.emplace(A[i],i);
    }
    for(int start=0;start<A.size()-1;start++){
        int index;
        for(int j=start+1;j<=A.size()-1;j++){
            int diff=A[j]-A[start];
            int pre=A[j];
            int len=2;
            index=j;
            while(nums.count(pre+diff)&&nums[pre+diff]>j){
                j=nums[pre+diff];
                pre=pre+diff;
                len++;
            }
            j=index;
            ans=max(ans,len);
        }
    }
    return ans;
}

//执行速度3605ms
int longestArithSeqLength(vector<int>& A) {
    //每个位置存在的差值用map映射
    vector<unordered_map<int,int>> dp(A.size(),unordered_map<int,int>(10000));
    int ans=2;
    for(int end=0;end<=A.size()-1;end++){
        for(int j=0;j<end;j++) {
            int key=A[end]-A[j];
           if(dp[j][key]!=0)dp[end][key]=dp[j][key]+1;
           else
               dp[end][key]=2;
           ans=max(ans,dp[end][key]);
        }
    }
    return ans;
}

//执行速度74ms
int longestArithSeqLengthImp(vector<int>& A) {
    vector<vector<int>> dp(A.size(),vector<int>(A.size(),0));
    vector<int> index(10001,-1);
    int ans=2;
    for(int i=0;i<A.size()-1;i++){
        //重复的数字后面的会把前面的覆盖了，保证每次都是离后面最近的一个数字
        index[A[i]] = i;
        for(int j=i+1;j<=A.size()-1;j++) {
            int pre=2*A[i]-A[j];
            if(pre<0||pre>10000||index[pre]==-1)
                dp[i][j] = 2;
            else
                dp[i][j] = dp[index[pre]][i] + 1;
            ans = max(ans, dp[i][j]);
        }
    }
    return ans;
}


int main(){
    vector<int> vec{83,20,17,43,52,78,68,45};
    cout<<longestArithSeqLengthImp(vec);
    return 0;
}