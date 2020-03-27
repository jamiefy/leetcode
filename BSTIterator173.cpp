//
// Created by anranzhai on 2020/3/27.
//
#include <iostream>
#include <stack>
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };
//递归实现中序遍历
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        init(root);
    }
    /** @return the next smallest number */
    int next() {
        TreeNode* top=nodeStack.top();
        nodeStack.pop();
        if(top->right!=NULL)
            init(top->right);
        return top->val;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(!nodeStack.empty())
            return true;
        else
            return false;
    }

private:
    std::stack<TreeNode*> nodeStack;
    void init(TreeNode* root){
        while(root!=NULL){
            nodeStack.push(root);
            root=root->left;
        }
    }
};
