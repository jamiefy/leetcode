//
// Created by anranzhai on 2020/3/10.
//
#include <iostream>
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
int ans;
int depth(TreeNode* root){
    if(root==NULL)return 0;
    int L=depth(root->left);
    int R=depth(root->right);
    ans=std::max(ans,L+R+1);//必须每次都顺便更新一下最大直径，保证以当前节点为根节点的最大直径的情况不会被漏掉
    return std::max(L,R)+1;
}
int diameterOfBinaryTree(TreeNode* root) {
    if(root==NULL||(root->left==NULL&&root->right==NULL))
        return 0;
    ans = 1;
    depth(root);
    return ans - 1;
}

int main(){
    TreeNode* root=new TreeNode(1);
    TreeNode* two=new TreeNode(2);
    TreeNode* three=new TreeNode(3);
    root->left=two;
    root->right=three;
    TreeNode* four=new TreeNode(4);
    TreeNode* five=new TreeNode(5);
    two->left=four;
    two->right=five;
    std::cout<<diameterOfBinaryTree(root);
}