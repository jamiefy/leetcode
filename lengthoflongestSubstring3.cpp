//
// Created by anranzhai on 2020/6/9.
//
#include <iostream>
#include <array>
#include <string>
using namespace std;
int lengthOfLongestSubstring(string s) {
    if (s.size() == 0)
        return 0;
    array<int, 128> index;
    index.fill(-1);
    auto ans = INT32_MIN;
    auto i = 0, j = 0;
    for (; i < s.size() && j < s.size(); j++) {
        if (index[s[j]] == -1 || j - i < j - index[s[j]]) {
            index[s[j]] = j;
        } else {
            ans = max(ans, j - i);
            i = index[s[j]] + 1;
            index[s[j]] = j;
        }
    }
    ans = max(ans, j - i);
    return ans;
}
int main(){
    cout<<lengthOfLongestSubstring("abcabcbb");
}
