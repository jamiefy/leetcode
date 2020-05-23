//
// Created by anranzhai on 2020/5/22.
//
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;
//迭代
//时间复杂度：O(N×2^N),生成所有的子集，并复制到输出列表中。
//空间复杂度：O(N×2^N)，存储所有子集，共 n 个元素，每个元素都有可能存在或者不存在。
vector<vector<int>> subsetsRecursive(vector<int>& nums) {
    vector<vector<int>> ret(1,vector<int>());
    for(auto& num:nums){
        vector<vector<int>> group;
        //按值传递
        for(auto r:ret){
            //生成ret中对象的副本进行操作
            r.emplace_back(num);
            group.push_back(r);
        }
        //右值引用
        for(auto&& g:group){
            //进行一次移动构造，把group内的值直接移到ret
            ret.push_back(std::move(g));
        }
    }
    return ret;
}

//递归回溯
//时间复杂度：O(N×2^N),生成所有的子集，并复制到输出列表中。
//空间复杂度：O(N×2^N)，存储所有子集，共 n 个元素，每个元素都有可能存在或者不存在。
void backTracking(const vector<int>& nums,int len,int index,vector<int>& curr,vector<vector<int>>& ret){
    if(curr.size()==len){
        ret.push_back(curr);
        return;
    }
    for(int i=index;i<nums.size();i++){
        curr.emplace_back(nums[i]);
        //每个数只用跟他后面的数组合
        backTracking(nums,len,i+1,curr,ret);
        curr.pop_back();
    }
}
vector<vector<int>> subsets(vector<int>& nums) {
    vector<vector<int>> ret(1,vector<int>());
    vector<int> curr;
    //子集的所有可能长度
    for(int len=1;len<=nums.size();len++)
        backTracking(nums,len,0,curr,ret);
    return ret;
}

//字典排序（二进制排序子集）：基于二进制位掩码和对应位掩码之间的映射字典生成排列/组合/子集
//1.生成所有长度为 n 的二进制位掩码。
//2.将每个子集都映射到一个位掩码数：位掩码中第 i 位如果是 1 表示子集中存在 nums[i]，0 表示子集中不存在 nums[i]。
//3.返回子集列表。
//时间复杂度：O(N×2^N),生成所有的子集，并复制到输出列表中。
//空间复杂度：O(N×2^N)，存储所有子集，共 n 个元素，每个元素都有可能存在或者不存在。
vector<vector<int>> subsetsbits(vector<int>& nums) {
    vector<vector<int>> ret;
    auto n=nums.size();
    for(int i=0;i<pow(2,n);i++){
        vector<int> cur;
        for(int j=0;j<n;j++){
            if(i & (1<<j))//取每位是否为1
                cur.emplace_back(nums[j]);
        }
        ret.push_back(move(cur));

    }
    return ret;
}
int main(){
    vector<int> vec{1,2,3};
    vector<vector<int>> ret=subsetsbits(vec);
    cout<<0;
}