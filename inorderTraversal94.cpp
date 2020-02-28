//
// Created by anranzhai on 2020/2/28.
//
#include <iostream>
#include <vector>
#include <stack>
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     };

void inorderTra(TreeNode* root,std::vector<int> &vec){
    if(root->left!=NULL)
        inorderTra(root->left,vec);
    vec.emplace_back(root->val);
    if(root->right!=NULL)
        inorderTra(root->right,vec);
}

//时间复杂度：O(n)。递归函数 T(n) =2⋅T(n/2)+1。
//空间复杂度：最坏情况下需要空间O(n)，平均情况为O(logn)。
std::vector<int> inorderTraversal(TreeNode* root) {
    std::vector<int> ret;
    if(root==NULL)
        return ret;
    inorderTra(root,ret);
    return ret;
}

//栈,时间复杂度空间复杂度均为O(n)
std::vector<int> inorderTraverse(TreeNode* root) {
    std::vector<int> ret;
    if(root==NULL)
        return ret;
    std::stack<TreeNode*> tmp;
    TreeNode* curr=root;
    while(curr!=NULL || !tmp.empty()){
        while(curr!=NULL){
            tmp.push(curr);
            curr=curr->left;
        }
        curr=tmp.top();
        ret.push_back(curr->val);
        curr=curr->right;
    }
    return ret;
}

//线索二叉树,时间复杂度空间复杂度均为O(n)
std::vector<int> inorderTraver(TreeNode* root) {
    std::vector<int> ret;
    if(root==NULL)
        return ret;
    TreeNode* curr=root,*pre;
    while(curr!=NULL){
        if(curr->left==NULL){
            ret.push_back(curr->val);
            curr=curr->right;
        } else{
            pre=curr->left;
            while(pre->right!=NULL){
                pre=pre->right;
            }
            TreeNode* tmp=curr->left;
            curr->left=NULL;
            pre->right=curr;
            curr=tmp;
        }
    }
    return ret;
}