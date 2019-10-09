//
// Created by Administrator on 2019/9/30.
//
#include <String>
#include <iostream>

std::string longestPalindrome(std::string s) {//暴力算法不能通过
    int len=s.size();
    int maxlen=0,maxlow=0;
    for(int i=0;i<len;i++){
        for(int j=i+1;j<len;j++){
            int low=i,high=j;
            while(s[low]==s[high]){
                if(low>=high && j-i+1>maxlen){
                    maxlen=j-i+1;
                    maxlow=i;
                    break;
                }
                low++;
                high--;
            }
        }
    }
    return s.substr(maxlow,maxlen);
}

int main(){
    std::string s("abab");
    std::cout<<longestPalindrome(s);
}