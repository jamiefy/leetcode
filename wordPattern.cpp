//
// Created by anranzhai on 2020/5/9.
//
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <cstring>
using namespace std;
//双百真棒哈哈哈哈
bool wordPattern(string pattern, string str) {
    int plen=pattern.size();
    int slen=str.size();
    if(plen==0&&slen==0)
        return true;
    if(plen==0||slen==0)
        return false;
    int p=0;
    unordered_map<char,string> nmap;
    unordered_set<string> nset;
    auto s=strtok(const_cast<char*>(str.c_str())," ");
    while(p<plen&&s!=NULL){
        if(nmap.count(pattern[p])){
            if(s!=nmap[pattern[p]])
                return false;
        } else{
            if(nset.count(s))
                return false;
            nmap[pattern[p]]=s;
            nset.emplace(s);
        }
        p++;
        s=strtok(NULL," ");
    }
    return p==plen&&s==NULL;
}

int main(){
    cout<<wordPattern("abba"
                     , "dog dog dog dog");
}