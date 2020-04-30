//
// Created by anranzhai on 2020/4/30.
//
#include <iostream>
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//二叉搜索树
//迭代循环
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

    // Value of p
    int pVal = p->val;

    // Value of q;
    int qVal = q->val;

    // Start from the root node of the tree
    TreeNode* node = root;

    // Traverse the tree
    while (node != NULL) {

        // Value of ancestor/parent node.
        int parentVal = node->val;

        if (pVal > parentVal && qVal > parentVal) {
            // If both p and q are greater than parent
            node = node->right;
        } else if (pVal < parentVal && qVal < parentVal) {
            // If both p and q are lesser than parent
            node = node->left;
        } else {
            // We have found the split point, i.e. the LCA node.
            return node;
        }
    }
    return NULL;
}

//递归
TreeNode* lowestCommonAncestorRec(TreeNode* root, TreeNode* p, TreeNode* q) {
    if(root==NULL)
        return NULL;
    if(p==q||q==root||p==root)
        return p==root?p:q;
    if((p->val<root->val&&q->val>root->val)||(p->val>root->val&&q->val<root->val))
        return root;
    else if(p->val<root->val&&q->val<root->val)
        return lowestCommonAncestor(root->left,p,q);
    else//p->val>root->val&&q->val>root->val
        return lowestCommonAncestor(root->right,p,q);

}