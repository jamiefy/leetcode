//
// Created by anranzhai on 2019/10/15.
//
#include <iostream>
#include <vector>
#include <algorithm>

//使用递归把第一位分别压入nums的每一个int值,然后第二位分别压入除第一位外的其他值
//n*(n-1)*(n-2)*...*1当nums为空时完成一个vector
//edited by bf to test git
void recur(std::vector<int>& nums,std::vector<int> &num,std::vector<std::vector<int>>& ret){//&减少时间和内存消耗
    if(nums.size()==0)
        ret.emplace_back(num);
    for(auto it=nums.begin();it!=nums.end();it++){
        //在num尾部构造该值,使下层压入的vector中包括该值
        num.emplace_back(*it);
        //擦除nums中该值,使下层压入的值中不包括已经压入的值
        nums.erase(it);
        //进入下一层
        recur(nums,num,ret);
        //在nums的it位置前插入刚刚删除的值,从而使下一个值压入的过程中还是在
        // 原nums的基础上,不然下一个值压入后传入下层的nums中缺少当前值
        nums.insert(it,*num.rbegin());
        //弹出num尾部新构造的值,从而使下一个值压入时前缀不改变
        // 使用clear,会删除上一层的
        num.pop_back();
    }
}

std::vector<std::vector<int>> permute(std::vector<int>& nums) {
    std::vector<std::vector<int>> ret;
    if(nums.size()==0)
        return ret;
    std::vector<int> num;
    recur(nums,num,ret);
    return ret;
}


//传递空std::vector<std::vector<int>>& ,比定义一个全局td::vector<std::vector<int>>消耗更更少的时间和空间,要择优
//使用交换法在原vector的基础上直接更改,用index记录更改到的位置,省去了上面方法中的一些数组操作
void backtTracking(std::vector<int> &nums,int index,std::vector<std::vector<int>>& ret){
    if(index==nums.size())
        ret.emplace_back(nums);
    for(int i=index;i<nums.size();i++){
        //前缀保持不变,从index开始与后面的值依次交换位置
        std::swap(nums[index],nums[i]);
        //完成index位,进入下一层处理下一位
        backtTracking(nums,index+1,ret);
        //再交换回来保持下一个值与index交换时仍在一开始传入函数的参数的基础上
        std::swap(nums[index],nums[i]);
    }
}

std::vector<std::vector<int>> permuteBack(std::vector<int>& nums) {
    std::vector<std::vector<int>> ret;
    if(nums.size()==0)
        return ret;
    backtTracking(nums,0,ret);
    return ret;
}

//时间和空间消耗和recur方法一样少
//DFS：用visited标记已经填进去的数，若之前填过则跳过
void DFS(std::vector<std::vector<int>> &ret,std::vector<int>& nums,std::vector<bool> &visited,std::vector<int> &num){
    if(num.size()==nums.size())
        ret.emplace_back(num);
    for(int i=0;i<nums.size();i++){
        if(visited[i]==true)
            continue;
        visited[i]=true;
        num.emplace_back(nums[i]);
        DFS(ret,nums,visited,num);
        //改变的一定要变回来，保证该层循环过程中visited数组和num数组不变——称为状态重置
        visited[i]= false;
        num.pop_back();
    }
}


std::vector<std::vector<int>> permuteDFS(std::vector<int>& nums) {
    std::vector<std::vector<int>> ret;
    std::vector<bool> visited(nums.size(),false);
    std::vector<int> num;
    DFS(ret,nums,visited,num);
    return ret;
}

int main(){
    std::vector<int> nums{1,2,3};permuteDFS(nums);
    std::vector<std::vector<int>> ret;
    ret=permute(nums);
    for(int i=0;i<ret.size();i++){
        for(int j=0;j<ret[i].size();j++){
            std::cout<<ret[i][j]<<" ";
        }
        std::cout<<std::endl;
    }
}