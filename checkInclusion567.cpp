//
// Created by anranzhai on 2020/6/29.
//
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
vector<int> getNext(string s){
    int len=s.size();
    vector<int> next(len);
    next[0]=-1;
    int k=-1;
    int j=0;
    while(j<len-1){
        if(k==-1||s[k]==s[j]){
            k++;
            j++;
            if(s[k]!=s[j])
                next[j]=k;
            else
                next[j]=next[k];
        }else
            k=next[k];
    }
    return next;
}
bool KMP(string s1, string s2) {
    int l1=s1.size();
    int l2=s2.size();
    if(l1>l2)return false;
    if(l1==l2) return s1==s2;
    vector<int> next=getNext(s1);
    int i=0,j=0;
    while(i<l2&&j<l1){
        if(j==-1||s1[j]==s2[i]){
            i++;
            j++;
        }else
            j=next[j];
    }
    if(j==l1)
        return true;
    else
        return false;
}

bool checkInclusion(string s1, string s2) {
    int l1=s1.size();
    int l2=s2.size();
    if(l1>l2)return false;
    array<int,26> nmap;
    fill(nmap.begin(),nmap.end(),0);
    for(int i=0;i<l1;i++)
        nmap[s1[i]-'a']++;
    array<int,26> tmp;
    fill(tmp.begin(),tmp.end(),0);
    for(int i=0,j=0;i<=j&&j<l2;j++){
        if(nmap[s2[j]-'a']!=0){
            tmp[s2[j]-'a']++;
            while(nmap[s2[j]-'a']<tmp[s2[j]-'a']){
                tmp[s2[i]-'a']--;
                i++;
            }
        } else{
            i=j+1;
            fill(tmp.begin(),tmp.end(),0);
        }
        if(nmap==tmp)
            return true;
    }
    return false;
}

bool checkInclu(string s1, string s2) {
    if (s1.length() > s2.length())
        return false;
    array<int,26> s1map;
    array<int,26> s2map;
    fill(s1map.begin(),s1map.end(),0);
    fill(s2map.begin(),s2map.end(),0);
    for (int i = 0; i < s1.length(); i++) {
        s1map[s1[i] - 'a']++;
        s2map[s2[i] - 'a']++;
    }
    int count = 0;
    for (int i = 0; i < 26; i++)
        if (s1map[i] == s2map[i])
            count++;
    for (int i = 0; i < s2.length() - s1.length(); i++) {
        int r = s2[i + s1.length()] - 'a', l = s2[i] - 'a';
        if (count == 26)
            return true;
        s2map[r]++;
        if (s2map[r] == s1map[r])
            count++;
        else if (s2map[r] == s1map[r] + 1)
            count--;
        s2map[l]--;
        if (s2map[l] == s1map[l])
            count++;
        else if (s2map[l] == s1map[l] - 1)
            count--;
        }
        return count == 26;
}

int main(){
    cout<<checkInclu("ab"
                         ,"ba");
}