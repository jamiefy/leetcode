//
// Created by anranzhai on 2020/4/27.
//
#include <iostream>
#include <vector>
//位运算不合适，当size>=32时会超出整数的范围,位运算适合于位置大小固定的题
int getcnt(long num,std::vector<int>& nums){
    int cnt=0;
    for(int i=0;num&&(i<nums.size());i++){
        cnt+=(num&1)*nums[nums.size()-1-i];
        num>>=1;
    }
    return cnt;
}

int robBit(std::vector<int>& nums) {
    std::vector<int> dp(1<<nums.size(),0);
    int max=INT64_MIN;
    for(long i=0;i<(1<<nums.size());i++){
        if(i&(i<<1))
            continue;
        dp[i]=getcnt(i,nums);
        if(dp[i]>max)
            max=dp[i];
    }
    return max;
}

//递归会超出时间限制
int maxCount=INT32_MIN;
void recursive(std::vector<int> &nums,int index,int cursum,bool pre){
    if(index==nums.size()-1){
        maxCount=std::max(maxCount,cursum);
        return ;
    }
    if(pre)
        recursive(nums,index+1,cursum, false);
    else{
        recursive(nums,index+1,cursum+nums[index+1], true);
        recursive(nums,index+1,cursum, false);
    }
}

int robRec(std::vector<int>& nums) {
    if(nums.size()==0)
        return 0;
    recursive(nums,0,nums[0], true);
    recursive(nums,0,0, false);
    return maxCount;
}

//动态规划
//动态规划方程：dp[n] = MAX( dp[n-1], dp[n-2] + num )
//由于不可以在相邻的房屋闯入，所以在当前位置 n 房屋可盗窃的最大值，要么就是 n-1 房屋可盗窃的最大值，
//要么就是 n-2 房屋可盗窃的最大值加上当前房屋的值，二者之间取最大值
//时间复杂度：O(n)。其中 n 为房子的数量。
//空间复杂度：O(n)。
int rob(std::vector<int>& nums) {
    int n=nums.size();
    if(n==0)
        return 0;
    if(n==1)
        return nums[0];
    std::vector<int> dp(n);
    dp[0]=nums[0];
    dp[1]=nums[0]>nums[1]?nums[0]:nums[1];
    for(int i=2;i<n;i++){
        dp[i]=std::max(dp[i-2]+nums[i],dp[i-1]);
    }
    return dp[n-1];
}

//动态规划优化，空间复杂度O(1),但是执行时间和空间消耗几乎一样
int robImp(std::vector<int>& nums) {
    int n=nums.size();
    if(n==0)
        return 0;
    if(n==1)
        return nums[0];
    int f1=nums[0];
    int f2=nums[0]>nums[1]?nums[0]:nums[1];
    for(int i=2;i<n;i++){
        int cur=std::max(f1+nums[i],f2);
        f1=f2;
        f2=cur;
    }
    return f2;
}

int main(){
    std::vector<int> vec{1,2,3,1};
    std::cout<<rob(vec);
}