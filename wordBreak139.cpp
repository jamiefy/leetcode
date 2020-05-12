//
// Created by anranzhai on 2020/5/12.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;
bool wordBreakdp(std::string s, std::vector<std::string>& wordDict) {
    int n=s.size();
    std::vector<bool> dp(n+1, false);
    dp[0]=true;
    for(int i=1;i<=n;i++){
        for(int j=0;j<i;j++){
            //dp[j]==true意味着前缀可以拆分成单词
            if(dp[j]&&std::find(wordDict.begin(),wordDict.end(),s.substr(j,i-j))!=wordDict.end()){
                dp[i]=true;
                //存在一种使0到i-1的i个字母可拆分成单词的情况就可直接跳出循环，因为dp[i]已经设为true
                break;
            }
        }
    }
    return dp[n];
}

struct TreeNode{
    //一定要设置初始值，不然会出现未定义行为
    array<TreeNode*,26> children{};
    bool isWord= false;
};

void insert(TreeNode* root,string str){
    for(auto i=0;i<str.size();i++){
        auto index=str[i]-'a';
        if(!root->children[index])
            root->children[index]=new TreeNode;
        root=root->children[index];
    }
    root->isWord=true;
}

bool dfs(std::string s, std::vector<int>& isWordBreak,TreeNode* root,int index){
    if(index==s.size())
        return true;
    if(isWordBreak[index]!=0)return isWordBreak[index]>0;
    TreeNode* cur=root;
    for(int i=index;i<s.size();i++){
        //如果该字符不在当前前缀里，说明以index开头的字符后面部分不可拆分，可直接退出
        if(cur->children[s[i]-'a']==NULL)
            break;
        cur=cur->children[s[i]-'a'];
        //如果以index开头的字符在此处不可拆分有可能在下一处有可能拆分
        if(cur->isWord&&dfs(s,isWordBreak,root,i+1)){
            isWordBreak[index]=1;
            return true;
        }
    }
    isWordBreak[index]=-1;
    return false;
}

bool wordBreak(std::string s, std::vector<std::string>& wordDict) {
    if(s.size()==0)
        return false;
    TreeNode* root=new TreeNode;
    for(int i=0;i<wordDict.size();i++){
        insert(root,wordDict[i]);
    }
    vector<int> isWordBreak(s.size(),0);
    return dfs(s,isWordBreak,root,0);
}

int main(){
    string s{"bb"};
    vector<string> words{"a","b","bbb","bbbb"};
    cout<<wordBreak(s,words);
}