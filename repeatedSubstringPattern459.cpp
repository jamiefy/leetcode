//
// Created by anranzhai on 2020/6/14.
//
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using std::string;
using std::vector;
//s+s从下标为1处搜索，包含一个s子串，如果s由重复子串构成，则find返回pos<s.size()，
//否则，返回s.size(),即添加上的第二个s
bool repeatedSubstringPattern(string s) {
    if(s.size()==0)
        return false;
    return (s+s).find(s,1)!=s.size();
}

//KMP基本算法,不能用改进的
//运用公式 x.size() = length - next[length]; x为最小周期子串
//KMP最小循环节、循环周期：
//定理：假设S的长度为len，则S存在最小循环节，循环节的长度L为len-next[len]，子串为S[0…len-next[len]-1]。
//（1）如果len可以被len - next[len]整除，则表明字符串S可以完全由循环节循环组成，循环周期T=len/L。
//（2）如果不能，说明还需要再添加几个字母才能补全。需要补的个数是循环个数L-len%L=L-(len-L)%L=L-next[len]%L，L=len-next[len]。
bool repeatedSubstringPatternKMP(string s) {
    int n = s.size();
    vector<int> next(n+1,-1);
    int i = 0;
    int j = next[0];
    while (i < n){
        if (j == -1 || s[i] == s[j]){
            i++;
            j++;
            next[i] = j;
        }
        else
            j = next[j];
    }
    int x = n - next[n];
    if (n % x == 0 && x != n)
        return true;
    return false;

}