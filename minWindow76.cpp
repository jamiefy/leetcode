//
// Created by anranzhai on 2020/6/10.
//
#include <iostream>
#include <vector>
#include <map>
using namespace std;
//用一个哈希表表示 t 中所有的字符以及它们的个数，用一个哈希表动态维护窗口中所有的字符以及它们的个数，如果这个动态表中包含 t 的哈希表
//中的所有字符，并且对应的个数都不小于 t 的哈希表中各个字符的个数，那么当前的窗口是「可行」的。
string minWindow(string s, string t) {
    int len=s.size();
    int size=t.size();
    map<char,int> nmap;
    for(int i=0;i<size;i++){
        nmap[t[i]]++;
    }
    int cnt=0;
    int ans=INT32_MAX;
    int left=-1;
    map<char,int> tmp;
    for(int i=0,j=0;i<=j&&j<=len;i++){
        while(cnt<size&&j<=len){
            if(nmap.count(s[j])){
                tmp[s[j]]++;
                if(tmp[s[j]]<=nmap[s[j]])
                    cnt++;
            }
            j++;
        }
        if(cnt==size && j-i<ans){
            ans=j-i;
            left=i;
        }
        if(nmap.count(s[i])){
            tmp[s[i]]--;
            if(tmp[s[i]]<nmap[s[i]]){
                cnt--;
            }
        }
    }
    return ans==INT32_MAX?"":s.substr(left,ans);
}

//滑动窗口优化：用数组替代map
string minWindowArray(string s, string t)
{
    vector<int> m(128,0);
    string res="";
    int left=0,cnt=0,minLeft=-1,minLen=INT_MAX;
    for(auto a : t)
        ++m[a];
    for(int i=0;i<s.size();i++)
    {
        if(--m[s[i]]>=0)
            cnt++;
        while(cnt==t.size())
        {
            if(minLen>i-left+1)
            {
                minLen=i-left+1;
                minLeft=left;
            }
            if(++m[s[left]]>0)
                cnt--;
            ++left;
        }
    }
    return minLeft==-1 ? "" : s.substr(minLeft,minLen);
}

int main(){
    string ret=minWindow("ADOBECODEBANC", "ABC");
    cout<<0;
}