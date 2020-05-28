//
// Created by anranzhai on 2020/5/28.
//
#include <bits/stdc++.h>
using namespace std;

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };

//仿照mirrors
//将左子树插入到右子树的地方
//将原来的右子树接到左子树的最右边节点
//考虑新的右子树的根节点，一直重复上边的过程，直到新的右子树为 null
void flattenmirrors(TreeNode* root) {
    TreeNode* node= nullptr;
    while(root!= nullptr){
        if(root->left== nullptr){
            root=root->right;
        } else{
            node=root->left;
            while(node->right!= nullptr){
                node=node->right;
            }
            node->right=root->right;
            root->right=root->left;
            root->left= nullptr;
            root=root->right;
        }
    }
}

//先序遍历的逆序
//利用一个全局变量 pre，更新当前根节点的右指针为 pre，左指针为 null,不用担心左孩子丢失，因为是先序遍历的逆序，左孩子已经遍历过了
TreeNode* pre= nullptr;
void flattenreverse(TreeNode* root) {
    if(root== nullptr)
        return;

    flattenreverse(root->right);
    flattenreverse(root->left);
    root->right=pre;
    root->left=nullptr;//root->left一定要置NULL
    pre=root;
}

//解法一和解法三可以看作自顶向下的解决问题，解法二可以看作自底向上。
//栈 前序遍历迭代法变形
//用栈保存右孩子，不需要担心右孩子丢失了。用一个 pre 变量保存上次遍历的节点
void flatten(TreeNode* root) {
    if(root== nullptr)
        return;
    stack<TreeNode*> st;
    st.emplace(root);
    TreeNode* pre= nullptr;
    while(!st.empty()){
        TreeNode* top=st.top();
        st.pop();
        if(top->right!= nullptr)
            st.emplace(top->right);
        if(top->left!= nullptr)
            st.emplace(top->left);
        if(pre!= nullptr){
            pre->right=top;
            pre->left= nullptr;
        }
        pre=top;
    }
}