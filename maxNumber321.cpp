//
// Created by I538989 on 6/19/2020.
//
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>
using std::stack;
using std::queue;
using std::vector;
using PII=std::pair<int,int>;
//单调栈求出nums选m个数最大值
//合并两个最大值数组
//求出合并后的最大值
//时间复杂度O((min(k,size1)-max(0,k-size2))*max(nums1.size(),nums2.size())
vector<int> selectMaxNumber(const vector<int>& nums, int m) {
    int k = nums.size() - m;
    vector<int> st;
    auto index=0;
    while (index<nums.size()){
        if(st.empty()||st.back()>=nums[index]||k<=0)
            st.emplace_back(nums[index++]);
        else{
            st.pop_back();
            k--;
        }
    }
    while(k-->0)
        st.pop_back();
    return st;
}

vector<int> merge(const vector<int>& nums1, const vector<int>& nums2) {
    vector<int> ret;
    for(auto i=nums1.begin(),j=nums2.begin();i!=nums1.end()||j!=nums2.end();){
        //如果第一个序列的字典序小于第二个，这个算法会返回 true，否则返回 false
        ret.push_back(std::lexicographical_compare(i,nums1.end(),j,nums2.end())?*j++:*i++);
    }
    return ret;
}

vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    int size1=nums1.size();
    int size2=nums2.size();

    vector<int> ans;
    for(int m=std::max(0,k-size2);m<=std::min(k,size1);m++){
        int n=k-m;
        auto&& maxM=selectMaxNumber(nums1,m);
        auto&& maxN=selectMaxNumber(nums2,n);
        auto&& maxMN=merge(maxM,maxN);
        if(maxMN>ans) ans=std::move(maxMN);
    }
    return ans;
}

int main(){
    vector<int> v1{3,9};
    vector<int> v2{8,9};
    auto&& v=maxNumber(v1,v2,3);
    std::cout<<1;
}
