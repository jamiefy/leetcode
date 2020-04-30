//
// Created by anranzhai on 2020/4/30.
//
#include <stack>
#include <queue>
using namespace std;
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
};

//递归
//时间复杂度：O(N) ，N是二叉树中的节点数，最坏情况下，我们需要访问二叉树的所有节点。
//空间复杂度：O(N)，这是因为递归栈使用的最大空间位 N,斜二叉树的高度可以是 N。
TreeNode* ans=NULL;
int recursive(TreeNode* root,TreeNode* p,TreeNode* q){
    if(root==NULL)
        return 0;
    int left=recursive(root->left,p,q);
    int right=recursive(root->right,p,q);
    int mid=(root==p||root==q)?1:0;
    if(mid+left+right>=2)
        ans=root;
    return mid+left+right>0;
}
TreeNode* commonFather(TreeNode* root,TreeNode* p,TreeNode* q){
    recursive(root,p,q);
    return ans;
}

