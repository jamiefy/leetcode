#include <iostream>
#include <string.h>
#include <math.h>

int lengthOfLongestSubstring(std::string s) {
    int len=s.length();
    int ans=0;
    for(int i=0,j=0;i<len && j<len;){
        if(s.find(s.at(j),i)==j){
            ans=std::max(ans,j-i+1);
            j++;
        }
        else{
            i=s.find(s.at(j),i);
            i++;
        }
    }
    return ans;
}

int main() {
    std::string str="pwwkew";
    std::cout<<lengthOfLongestSubstring(str);
    return 0;
}