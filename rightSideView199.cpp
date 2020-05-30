//
// Created by anranzhai on 2020/5/29.
//
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

//层次遍历 单向队列
//bfs从左向右
using Node=pair<TreeNode*,int>;
vector<int> rightSideViewBFS(TreeNode* root) {
    if(root==nullptr)
        return vector<int>();
    queue<Node> quelist;
    quelist.emplace(root,1);
    vector<int> ret;
    while(!quelist.empty()){
        Node top=quelist.front();
        quelist.pop();
        if(ret.size()<top.second)
            ret.emplace_back(top.first->val);
        else
            ret[top.second-1]=top.first->val;
        if(top.first->left!= nullptr)
            quelist.emplace(top.first->left,top.second+1);
        if(top.first->right!= nullptr)
            quelist.emplace(top.first->right,top.second+1);
    }
    return ret;
}

//层次遍历 单向队列
//bfs从右向左
vector<int> rightSideViewbfs(TreeNode* root) {
    if(root==nullptr)
        return vector<int>();
    queue<Node> quelist;
    quelist.emplace(root,1);
    vector<int> ret;
    while(!quelist.empty()){
        Node top=quelist.front();
        quelist.pop();
        if(ret.size()<top.second)
            ret.emplace_back(top.first->val);
        if(top.first->right!= nullptr)
            quelist.emplace(top.first->right,top.second+1);
        if(top.first->left!= nullptr)
            quelist.emplace(top.first->left,top.second+1);
    }
    return ret;
}

//dfs 从右向左
vector<int> rightSideView(TreeNode* root) {
    if(root==nullptr)
        return vector<int>();
    stack<Node> quelist;
    quelist.emplace(root,1);
    vector<int> ret;
    while(!quelist.empty()){
        Node top=quelist.top();
        quelist.pop();
        if(ret.size()<top.second)
            ret.emplace_back(top.first->val);
        if(top.first->left!= nullptr)
            quelist.emplace(top.first->left,top.second+1);
        if(top.first->right!= nullptr)
            quelist.emplace(top.first->right,top.second+1);
    }
    return ret;
}

int main(){
    TreeNode* node0=new TreeNode(0);
    TreeNode* node1=new TreeNode(1);
    TreeNode* node2=new TreeNode(2);
    TreeNode* node3=new TreeNode(3);

    node0->left=node1;
    node0->right=node2;
    node1->left=node3;

    std::vector<int> vec;
    vec=rightSideView(node0);
    for(auto v:vec){
        cout<<v<<endl;
    }
}