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

//动态规划+前缀树
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

//把dp中所有可能性组合拼接起来
void collect(std::string s,vector<vector<int>> &dp,int index,string now,vector<string> &ret){
    if(index==s.size()){
        //注意把最后一个空格去掉


        now=now.substr(0,now.size()-1);
        ret.emplace_back(now);
        return;
    }
    if(index>s.size())return;
    for(auto p:dp[index]){
        collect(s,dp,p+1,now+s.substr(index,p-index+1)+" ",ret);
    }
}

vector<string> wordBreak(std::string s, std::vector<std::string>& wordDict) {
    if(s.size()==0)
        return vector<string>();
    TreeNode* root=new TreeNode;
    for(int i=0;i<wordDict.size();i++){
        insert(root,wordDict[i]);
    }

    vector<string> ret;
    //每个index对应一个容器，如果包含该index及之后的字符串可拆分，则把右边最近距离的可差费
    vector<vector<int>> dp(s.size(),vector<int>());
    vector<bool> canBreak(s.size()+1, false);
    canBreak[s.size()]=true;
    for(int i=s.size()-1;i>=0;i--){
        TreeNode* cur=root;
        for(int j=i;j<s.size();j++){
            //说明从i的前面不可断开，没有以i开头的单词
            if(cur->children[s[j]-'a']==NULL)
                break;
            cur=cur->children[s[j]-'a'];
            //i~j也就是i包括i及之后到j包括j组成单词，且j后可拆
            if(cur->isWord&&canBreak[j+1]){
                //说明i后可在j处拆分
                dp[i].emplace_back(j);
            }
        }
        if(dp[i].size()>0)
            canBreak[i]=true;
    }

    if(!canBreak[0])
        return ret;
    else
        collect(s,dp,0,"",ret);

    return ret;
}

int main(){
    vector<string> vec{"apple","pen","applepen","pine","pineapple"};
    vector<string> ret=wordBreak("pineapplepenapple",vec);
    cout<<0;
}