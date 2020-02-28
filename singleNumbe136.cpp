//
// Created by anranzhai on 2020/2/28.
//
#include <iostream>
#include <vector>
#include <algorithm>
//泛型算法，时间复杂度O(n),空间复杂度O(1)，但是实际执行时间贼大
int singleNumber(std::vector<int>& nums) {
    for(int i=nums.size()-1;i>=0;i--){
        auto it=std::find(nums.begin(),nums.end(),nums[i]);
        auto rit=std::find(nums.rbegin(),nums.rend(),nums[i]);
        if(rit.base()-1==it)
            return *it;
    }
    return 0;//不严谨但是lc执行通过
}

//异或。如果我们对 0 和二进制位做 XOR 运算，得到的仍然是这个二进制位：a⊕0=a
//如果我们对相同的二进制位做 XOR 运算，返回的结果是 0：a⊕a=0
//XOR 满足交换律和结合律：a⊕b⊕a=(a⊕a)⊕b=0⊕b=b
//时间复杂度：O(n),我们只需要将nums 中的元素遍历一遍，所以时间复杂度就是nums 中的元素个数。执行时间贼快
//空间复杂度：O(1)
int singleNumberXOR(std::vector<int>& nums) {
    int ret=0;
    for(auto &num:nums){
        ret^=num;
    }
    return ret;
}

int main(){
    std::vector<int> vec{3,4,3};
    std::cout<<singleNumberXOR(vec)<< std::endl;
}
