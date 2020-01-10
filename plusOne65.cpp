//
// Created by Administator on 2020/1/10.
//
#include <vector>
#include <iostream>

//时间复杂度：O(n),运行时间为4ms
//空间复杂度：O(1)
std::vector<int> plusOne(std::vector<int>& digits) {
    int len=digits.size();
    if(len==0)
        return digits;
    digits[len-1]+=1;
    if(digits[len-1]<10)
        return digits;
    else
        digits[len-1]%=10;
    int carry=1;
    for(int i=digits.size()-2;i>=0;i--){
        digits[i]+=carry;
        if(digits[i]<=9)
            return digits;
        else{
            carry=digits[i]/10;
            digits[i]=digits[i]%10;
        }
    }
    digits.insert(digits.begin(),carry);
    return digits;
}

//时间复杂度：O(n),运行时间几乎为0ms
//空间复杂度：O(1)
std::vector<int> plusOneImp(std::vector<int>& digits) {
    int len=digits.size();
    if(len==0)
        return digits;
    for(int i=digits.size()-1;i>=0;i--){
        digits[i]++;
        digits[i]=digits[i]%10;
        if(digits[i]!=0)return digits;
    }
    digits.insert(digits.begin(),1);
    return digits;
}

int main(){
    std::vector<int> vec{9,9};
    std::vector<int> digits=plusOneImp(vec);
    for(int i=0;i<digits.size();i++)
        std::cout<<digits[i]<<" ";
    std::cout<<std::endl;
}