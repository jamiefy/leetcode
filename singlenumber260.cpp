//
// Created by anranzhai on 2020/3/27.
//
#include <iostream>
#include <vector>
std::vector<int> singleNumber(std::vector<int>& nums) {
    int resultXOR=0;
    for(auto num:nums)
        resultXOR^=num;
    //找出两个不同数字x、y最右边第一个不同的位置index
    int rightFirstDiff=resultXOR & (-resultXOR);//-resultXOR=~resultXOR+1;
    int x=0,y=0;
    int *a=&x,*b=&y;
    for(auto num:nums)
        //将数组分为两组，一组index位为1，另一组index为0，（1）两组分别异或（2）一组异或得到x,则y=x^resultXOR
        // != 优先级高于 & ，num & rightFirstDiff !=0 的逻辑顺序是 num & (rightFirstDiff !=0)
        if(num & rightFirstDiff)
            *a^=num;
        else
            *b^=num;
//        if(num & rightFirstDiff!=0)
//            x^=num;
//        return std::vector<int>{x,x^resultXOR};
    return std::vector<int>{*a,*b};
}

int main(){
    std::vector<int> vec{1,2,1,3,2,5};
    std::vector<int> ret=singleNumber(vec);
    for(auto num:ret){
        std::cout<<num<<std::endl;
    }
}