//
// Created by anranzhai on 2020/2/28.
//
#include <iostream>
#include <vector>
#include <stack>
using namespace std;
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
    inorderTra(root,ret);
    return ret;
}

//栈,时间复杂度空间复杂度均为O(n),运行时间快，消耗空间少
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
        tmp.pop();
        ret.push_back(curr->val);
        curr=curr->right;
    }
    return ret;
}

//线索二叉树,时间复杂度空间复杂度均为O(n),改变树结构
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


vector<int> inorderTraversalagain(TreeNode* root) {
    if(root==NULL)
        return vector<int>();
    vector<int> ret;
    stack<TreeNode*> st;
    st.emplace(root);
    TreeNode* parent=root->left;
    while(parent!=NULL||!st.empty()){
        while(parent!=NULL){
            st.emplace(parent);
            parent=parent->left;
        }
        ret.emplace_back(st.top()->val);//中序遍历和前序遍历仅此一句位置不同
        parent=st.top()->right;
        st.pop();
    }
    return ret;
}

//morris（保持树原有结构）,空间消耗最少
vector<int> inorderTraversalmirror(TreeNode* root) {
    if(root==NULL)
        return vector<int>();
    vector<int> ret;
    TreeNode* cur = root;
    TreeNode* pre = NULL;
    while(cur!=NULL) {
        if (cur->left == NULL) {
            ret.emplace_back(cur->val);
            cur = cur->right;
        } else {
            pre = cur->left;
            //找到前驱节点，即左子树中的最右节点
            //pre->right!=NULL第一遍遍历到该最右节点
            //pre->right!=cur第二遍遍历到该最右节点
            while (pre->right != NULL && pre->right != cur)
                pre = pre->right;
            //创建中序遍历线索
            if (pre->right == NULL) {
                pre->right = cur;
                cur = cur->left;
            }
            //恢复树原有结构
            if (pre->right == cur) {
                pre->right = NULL;
                ret.emplace_back(cur->val);
                cur = cur->right;
            }
        }
    }
    return ret;
}