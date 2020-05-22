//
// Created by anranzhai on 2020/5/22.
//
#include <stack>
#include <iostream>
using namespace std;
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode() : val(0), left(nullptr), right(nullptr) {}
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
int kthSmallestinorder(TreeNode* root, int k) {
    auto cnt=0;
    TreeNode* cur=root;
    stack<TreeNode*> st;
    while(cur!=nullptr||!st.empty()){
        while(cur!=nullptr){
            st.emplace(cur);
            cur=cur->left;
        }
        TreeNode* top=st.top();
        st.pop();
        cnt++;
        if(cnt==k)
            return top->val;
        cur=top->right;
    }
    return -1;
}

//morris 栈溢出AddressSanitizer: stack-overflow on address 0x7ffea542cff8
int kthSmallest(TreeNode* root, int k) {
    auto cnt=0;
    TreeNode* cur=root;
    while(cur!=nullptr){
        if(cur->left== nullptr){
            cnt++;
            if(cnt==k)
                return cur->val;
            cur=cur->right;
        } else{
            TreeNode* node=cur->left;
            while(node->right!= nullptr&&node->right!=cur)
                node=node->right;
            if(node->right==nullptr){
                node->right=cur;
                cur=cur->left;
            }
            if(node->right==cur){
                cnt++;
                if(cnt==k)
                    return cur->val;
                node->right= nullptr;
                cur=cur->right;
            }
        }
    }
}



int main(){
    TreeNode* one=new TreeNode(3);
    TreeNode* two=new TreeNode(1);
    TreeNode* three=new TreeNode(4);
    TreeNode* four=new TreeNode(2);

    one->left=two;
    one->right=three;
    two->right=four;
    cout<<kthSmallest(one,1);
}