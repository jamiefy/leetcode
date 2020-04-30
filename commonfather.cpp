//
// Created by anranzhai on 2020/4/30.
//
#include <stack>
#include <queue>
using namespace std;
struct TreeNode{
    int value;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* commonFather(TreeNode* root,TreeNode* a,TreeNode* b){
    if(a==b)
        return a;
    stack<TreeNode*> st;
    st.push(root);
    queue<TreeNode*> list;
    TreeNode* another;
    while(!st.empty()){
        TreeNode* top=st.top();
        if(top==a||top==b){
            another=top==a?b:a;

        }
        if(top->left!=NULL)
            st.push(top->left);
        else if(top->right!=NULL)
            st.push(top->right);
        else{
            top=NULL;
            st.pop();
        }
    }

    while(!st.empty()){
        TreeNode* top=st.top();
        st.pop();
    }
}
