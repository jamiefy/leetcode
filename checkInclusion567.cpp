//
// Created by anranzhai on 2020/6/29.
//
#include <iostream>
#include <vector>
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
bool checkInclusion(string s1, string s2) {
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
int main(){
    cout<<checkInclusion("ab"
                   ,"eidbaooo");
}