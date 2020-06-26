//
// Created by anranzhai on 2020/6/26.
//
#include <vector>
#include <iostream>
using namespace std;
int minSubArrayLenDoublePointers(int s, vector<int> nums) {
    if(nums.size()==0)return 0;
    int sum=0;
    int ans=INT32_MAX;
    //判断条件sum>s||j<nums.size(),避免遗漏当j==nums.size()时还可以不断缩小的i
    for(int i=0,j=0;sum>=s||j<nums.size();){
        while(sum<s&&j<nums.size()){
            sum+=nums[j++];
        }
        if(sum>=s&&j-i<ans){
            ans=j-i;
        }
        if(sum>=s){
            sum-=nums[i++];
        }
    }
    return ans==INT32_MAX?0:ans;
}
//双指针 滑动窗口 时间复杂度O(n)
int minSubArrayLenDoublePointers(int s, vector<int>& nums)
{
    int n = nums.size();
    int ans = INT_MAX;
    int left = 0;
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += nums[i];
        while (sum >= s) {
            ans = min(ans, i + 1 - left);
            sum -= nums[left++];
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}

//二分查找 时间复杂度O(nlgn)
int minSubArrayLen(int s, vector<int> nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    int ans = INT_MAX;
    vector<int> sums(n,nums[0]); //size = n+1 for easier calculations
    //sums[0]=0 : Meaning that it is the sum of first 0 elements
    //sums[1]=A[0] : Sum of first 1 elements
    //ans so on...

    for (int i = 1; i <n; i++)
        sums[i] = sums[i - 1] + nums[i];
    for (int i = 0; i < n; i++) {
        int to_find = s + (i==0?0:sums[i - 1]);
        //函数lower_bound()在first和last中的前闭后开区间进行二分查找，返回大于或等于val的第一个元素位置。
        //upper_bound()返回的是第一个大于x的值的地址
        auto bound = lower_bound(sums.begin(), sums.end(), to_find);
        if (bound != sums.end()) {
            ans = min(ans, static_cast<int>(bound - (sums.begin() + i - 1)));
        }
    }
    return (ans != INT_MAX) ? ans : 0;
}

int main(){
    cout<<minSubArrayLen(7,{2,3,1,2,4,3});

}
