//
// Created by anranzhai on 2020/5/4.
//
#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <map>
using namespace std;
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

TreeNode* backTracking(vector<int>& preorder, vector<int>& inorder,int prestart,int preend,int instart,int inend){
   //注意界限的判定
    if(prestart>preend||instart>inend)
        return NULL;
    TreeNode* root=new TreeNode(preorder[prestart]);
    //当只剩一个时可直接返回
    if(prestart==preend)
        return root;
    int mid=find(inorder.begin(),inorder.end(),root->val)-inorder.begin()-instart;
    root->left=backTracking(preorder,inorder,prestart+1,prestart+mid,instart,instart+mid-1);
    root->right=backTracking(preorder,inorder,prestart+mid+1,preend,instart+mid+1,inend);
    return root;
}
TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    //注意空矩阵输入
    if(preorder.size()==0||inorder.size()==0)
        return NULL;
    return backTracking(preorder,inorder,0,preorder.size()-1,0,inorder.size()-1);
}

//空间换时间提高执行速度
map<int,int> nmap;
TreeNode* backTrack(vector<int>& preorder, vector<int>& inorder,int prestart,int preend,int instart,int inend){
    //注意界限的判定
    if(prestart>preend||instart>inend)
        return NULL;
    TreeNode* root=new TreeNode(preorder[prestart]);
    //当只剩一个时可直接返回
    if(prestart==preend)
        return root;
    int mid=nmap[root->val]-instart;
    root->left=backTrack(preorder,inorder,prestart+1,prestart+mid,instart,instart+mid-1);
    root->right=backTrack(preorder,inorder,prestart+mid+1,preend,instart+mid+1,inend);
    return root;
}
TreeNode* buildTreeImp(vector<int>& preorder, vector<int>& inorder) {
    //注意空矩阵输入
    if(preorder.size()==0||inorder.size()==0)
        return NULL;
    int index=0;
    for(auto v:inorder){
        nmap[v]=index++;
    }
    return backTrack(preorder,inorder,0,preorder.size()-1,0,inorder.size()-1);
}

int main(){
    vector<int> v1{1,2};
    vector<int> inorder{2,1};
    TreeNode* root=buildTreeImp(v1,inorder);
    stack<TreeNode*> st;
    st.emplace(root);
    while(!st.empty()){
        root=st.top();
        st.pop();
        cout<<root->val<<endl;
        if(root->right)
            st.emplace(root->right);
        if(root->left)
            st.emplace(root->left);
    }
}