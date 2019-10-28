//
// Created by 54293 on 2019/10/28.
//
#include <iostream>
#include <vector>

//乘法不是对应位相乘，每位都应与对方每位相乘
std::string multiply(std::string num1, std::string num2) {
    std::vector<int> multiplyVec;
    int len1=num1.size();
    int len2=num2.size();
    int  carry=0,index1=len1-1,index2=len2-1;
    int n1=0,n2=0;
    while(index1>=0&&index2>=0){
        n1=num1[index1]-'0';
        n2=num2[index2]-'0';
        multiplyVec.emplace_back((n1*n2+carry)%10);
        carry=(n1*n2+carry)/10;
        index1--;
        index2--;
    }
    if(index1<0){
        while(index2>=0){
            n2=num2[index2]-'0';
            multiplyVec.emplace_back((n2+carry)%10);
            carry=(n1+carry)/10;
            index2--;
        }
    } else{
        while(index1>=0){
            n1=num1[index1]-'0';
            multiplyVec.emplace_back((n1+carry)%10);
            carry=(n1+carry)/10;
            index1--;
        }
    }
    if(carry!=0)
        multiplyVec.emplace_back(carry);
    std::string multiplyStr;
    for(auto c:multiplyVec){
        multiplyStr+=(char)(c+'0');
    }
    return multiplyStr;
}

int main(){
    std::cout<<multiply("123","10")<<std::endl;

}