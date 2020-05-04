//
// Created by anranzhai on 2020/5/4.
//
//
// Created by anranzhai on 2020/5/4.
//
//
// Created by Administrator on 2019/9/30.
//
#include <String>
#include <iostream>
#include <vector>
std::string longestPalindromebaoli(std::string s) {//暴力算法不能通过
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

//中心扩展法
//时间复杂度：O(n^2)由于围绕中心来扩展回文会耗去 O(n)O(n) 的时间，所以总的复杂度为 O(n^2)
//空间复杂度：O(1)
int expand(std::string s,int low,int high){
    while(s[low]==s[high]){
        low--;
        high++;
        if(low<0||high>=s.size())
            break;
    }
    return high-low-1;
}

std::string longestPalindromeExpand(std::string s) {
    if(s.size()==0||s.size()==1)
        return s;
    int maxlow=0,maxhigh=0,len=INT32_MIN;
    for(int i=0;i<s.size();i++){
        int len1=expand(s,i,i);
        int len2=expand(s,i,i+1);
        len=std::max(len1,len2);
        if(len>maxhigh-maxlow+1){
            maxlow=i-(len-1)/2;
            maxhigh=i+len/2;
        }
    }
    return s.substr(maxlow,maxhigh-maxlow+1);
}

//动态规划
//时间复杂度：O(N^2)
//空间复杂度：O(N^2)，二维 dp 问题，一个状态得用二维有序数对表示，因此空间复杂度是 O(N^2)
std::string longestPalindrome(std::string s) {
    std::vector<std::vector<bool >> dp(s.size(),std::vector<bool>(s.size(), false));
    for(int i=0;i<s.size();i++)
        dp[i][i]=true;
    int low=0,high=0;
    for(int right=1;right<s.size();right++){
        for(int left=0;left<right;left++){
            if(s[left]==s[right]&&(right-left<=2||dp[left+1][right-1])){
                dp[left][right]=true;
                if(high-low<right-left){
                    low=left;
                    high=right;
                }
            }
        }
    }
    return s.substr(low,high-low+1);
}

int main(){
    std::string s("babad");
    std::cout<<longestPalindrome(s);
}

