//
// Created by anranzhai on 2020/5/8.
//
#include <iostream>
#include <vector>
using namespace std;
//用KMP算法得出来是最长子串：串中任意个连续的字符组成的子序列称为该串的子串；不是最长子序列：一个字符串的 子序列 是指
//这样一个新的字符串：它是由原字符串在不改变字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
void getNextVal(string p,vector<int> &next){
    next[0]=-1;
    int k=-1;
    int j=0;
    while(j<next.size()-1){
        if(k==-1||p[j]==p[k]){
            k++;
            j++;
            if(p[j]!=p[k])
                next[j]=k;
            else
                next[j]=next[k];
        } else
            k=next[k];
    }
}

int longestCommonSubstring(string text1, string text2) {
    if(text1.size()==0||text2.size()==0)
        return 0;
    if(text1.size()<text2.size())
        swap(text1,text2);
    int i=0;
    int j=0;
    int maxIndex=INT32_MIN;
    vector<int> next(text2.size());
    getNextVal(text2,next);
    while(i<text1.size()&&j<text2.size()){
        if(text1[i]==text2[j]){
            i++;
            j++;
        } else{
            maxIndex=max(maxIndex,j);
            j=next[j];
        }
    }
    return maxIndex;
}

//暴力时间复杂度O(n*n*m)
int longestCommonSubsequencebaoli(string text1, string text2) {
    if(text1.size()==0||text2.size()==0)
        return 0;
    int maxCount=INT32_MIN;
    for(int k=0;k<text1.size();k++){
        int count=0;
        int index=0;
        for(int i=k;i<text1.size();i++){
            for(int j=index;j<text2.size();j++){
                if(text1[i]==text2[j]){
                    index=j+1;
                    count++;
                    break;
                }
            }
        }
        maxCount=max(maxCount,count);
    }
    return maxCount;
}

//穷举出所有可能的结果都不容易，而动态规划算法做的就是穷举 + 剪枝，它俩天生一对儿。
//所以可以说只要涉及子序列问题，十有八九都需要动态规划来解决
//动态规划优化+空间压缩
//时间复杂度O(n*m)
//空间复杂度O(m)
int longestCommonSubsequence(string text1, string text2) {
    if(text1.size()==0||text2.size()==0)
        return 0;
    vector<int> dp(text2.size()+1,0);
    for(int i=1;i<=text1.size();i++){
        int last=0;
        for(int j=1;j<=text2.size();j++){
            int tmp=dp[j];
            if(text1[i-1]==text2[j-1])
                dp[j]=last+1;
            else
                dp[j]=max(dp[j],dp[j-1]);
            last=tmp;
        }
    }
    return dp[text2.size()];
}

int main(){
    cout<<longestCommonSubsequencebaoli("mhunuzqrkzsnidwbun"
                                        ,"szulspmhwpazoxijwbq");
}