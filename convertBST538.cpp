//
// Created by anranzhai on 2020/5/19.
//
#include <iostream>
#include <stack>
using namespace std;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

//栈迭代
TreeNode* convertBSTinorder(TreeNode* root) {
    if(root==nullptr)
        return nullptr;
    stack<TreeNode*> st;
    TreeNode* cur=root;
    auto value=0;
    while(cur!=nullptr||!st.empty()){
        while(cur!=nullptr){
            st.emplace(cur);
            cur=cur->right;
        }

        TreeNode* top=st.top();
        top->val+=value;
        value=top->val;
        st.pop();

        cur=top->left;
    }
    return root;
}

//mirrors  线索二叉树
TreeNode* convertBST(TreeNode* root) {
    if(root==nullptr)
        return nullptr;
    TreeNode* cur=root;
    auto value=0;
    while(cur!=nullptr){
        if(cur->right== nullptr){
            cur->val+=value;
            value=cur->val;
            cur=cur->left;
        } else{
            TreeNode* pre=cur->right;
            while(pre->left!= nullptr&&pre->left!=cur){
                pre=pre->left;
            }

            if(pre->left== nullptr){
                pre->left=cur;
                cur=cur->right;
            }
            if(pre->left==cur){
                cur->val+=value;
                value=cur->val;
                pre->left=nullptr;
                cur=cur->left;
            }
        }
    }
    return root;
}