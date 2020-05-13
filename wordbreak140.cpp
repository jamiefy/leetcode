//
// Created by anranzhai on 2020/5/12.
//
#include <vector>
#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;
//递归超出时间限制
void dfs(const string s,const unordered_set<string>& nset,int index,string now,vector<string>& ret){
    if(index==s.size()){
        ret.emplace_back(now);
        return;
    }
    for(int i=index;i<s.size();i++){
        string str=s.substr(index,i-index+1);
        if(nset.count(str)){
            if(index==0)
                dfs(s,nset,i+1,str,ret);
            else
                dfs(s,nset,i+1,now+" "+str,ret);
        }
    }
}

vector<string> wordBreakrecur(string s, vector<string>& wordDict) {
    int slen=s.size();
    unordered_set<string> nset;
    for(auto word:wordDict){
        nset.emplace(word);
    }
    vector<string> ret;
    dfs(s,nset,0,"",ret);
    return ret;
}


struct TreeNode{
    //一定要设置初始值，不然会出现未定义行为
    array<TreeNode*,26> children{};
    bool isWord= false;
    string word="";
};

void insert(TreeNode* root,string str){
    for(auto i=0;i<str.size();i++){
        auto index=str[i]-'a';
        if(!root->children[index])
            root->children[index]=new TreeNode;
        root=root->children[index];
    }
    root->isWord=true;
    root->word=str;
}

bool dfs(std::string s,TreeNode* root,int index,vector<vector<string>> &dp){
    if(index==s.size())
        return true;
    TreeNode* cur=root;
    bool flag=false;
    for(int i=index;i<s.size();i++){
        //如果该字符不在当前前缀里，说明以index开头的字符后面部分不可拆分，可直接退出
        if(cur->children[s[i]-'a']==NULL)
            break;
        cur=cur->children[s[i]-'a'];
        if(cur->isWord&&dfs(s,root,i+1,dp)){
            dp[index].emplace_back(cur->word);
            flag=true;
        }
    }

    return flag;
}

vector<string> wordBreak(std::string s, std::vector<std::string>& wordDict) {
    if(s.size()==0)
        return vector<string>();
    TreeNode* root=new TreeNode;
    for(int i=0;i<wordDict.size();i++){
        insert(root,wordDict[i]);
    }

    vector<string> ret;
    TreeNode* cur=root;
    for(int i=0;i<s.size();i++){
        //如果该字符不在当前前缀里，说明以index开头的字符后面部分不可拆分，可直接退出
        if(cur->children[s[i]-'a']==NULL)
            break;
        cur=cur->children[s[i]-'a'];
        string now="";
        if(cur->isWord&&dfs(s,root,i+1,now)){
            now+=string(cur->word.rbegin(),cur->word.rend());
            reverse(now.begin(),now.end());
            ret.emplace_back(now);
        }
    }
    return ret;
}

int main(){
    vector<string> vec{"apple","pen","applepen","pine","pineapple"};
    vector<string> ret=wordBreak("pineapplepenapple",vec);
    cout<<0;
}