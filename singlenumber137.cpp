//
// Created by anranzhai on 2020/3/27.
//
#include <iostream>
#include <vector>
int singleNumber(std::vector<int>& nums) {
    int bits[32]={0};
    for(auto num:nums) {
        int bitMask = 1;
        for (int i = 31; i >= 0; i--) {
            int bit=num & bitMask;
            if(bit!=0)
                bits[i]+=1;
            //bits[i] += num & bitMask;错误：num & 10 = 10（当num=2时）而不是 1 此时bits[i] += num & bitMask;等价于bits[i]+=2；而不是bits[i]+=1;
            bitMask<<=1;
        }
    }
    int result=0;
    for(int i=0;i<=31;i++){
        result<<=1;
        result+=bits[i]%3;
    }
    return result;
}

//位运算：NOT/AND/XOR
//时间复杂度：O(N)，遍历输入数组。
//空间复杂度：O(1)，不使用额外空间。
int singleNumberXOR(std::vector<int> nums) {
    int seenOnce = 0, seenTwice = 0;

    for (int num : nums) {
        // first appearence:
        // add num to seen_once
        // don't add to seen_twice because of presence in seen_once

        // second appearance:
        // remove num from seen_once
        // add num to seen_twice

        // third appearance:
        // don't add to seen_once because of presence in seen_twice
        // remove num from seen_twice
        seenOnce = ~seenTwice & (seenOnce ^ num);
        seenTwice = ~seenOnce & (seenTwice ^ num);
    }
    return seenOnce;
}

int main(){
    std::vector<int> vec{2,2,3,2};
    std::cout<<singleNumber(vec);
}