//
// Created by anranzhai on 10/7/19.
//
#include <iostream>

int strStr(std::string haystack, std::string needle) {
    int index=haystack.find(needle);
    return index;
}

int strStrDoublePointer(std::string haystack, std::string needle) {
    if(needle.size()==0)return 0;
    for(int i=0,j=0;i<haystack.size()&&j<needle.size();){
        if(haystack[i]==needle[j]){
            i++;
            j++;
            if(j==needle.size())return i-j;
        } else{
            i=i-j+1;
            j=0;
        }
    }
    return -1;
}