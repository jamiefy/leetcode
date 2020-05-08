//
// Created by anranzhai on 2020/5/8.
//
#include <iostream>
#include <vector>
#include <stack>
#include <deque>
#include <algorithm>
using namespace std;
struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 };

//从根节点开始依次迭代，弹出栈顶元素输出到输出列表中，然后依次压入它的所有孩子节点，按照从上到下、从左至右的顺序依次压入栈中。
//
//因为深度优先搜索后序遍历的顺序是从下到上、从左至右，所以需要将输出列表逆序输出。
//时间复杂度：访问每个节点恰好一次，因此时间复杂度为 O(N)，其中 N是节点的个数，也就是树的大小。
//空间复杂度：取决于树的结构，最坏情况需要保存整棵树，因此空间复杂度为 O(N)
vector<int> postorderTraversal(TreeNode* root) {
    if(root==NULL)
        return vector<int>();
    deque<int> deq;
    stack<TreeNode*> st;
    st.emplace(root);
    while(!st.empty()){
        TreeNode* top=st.top();
        deq.push_front(top->val);
        st.pop();
        if(top->left!=NULL)
            st.emplace(top->left);
        if(top->right!=NULL)
            st.emplace(top->right);
    }
    return vector<int>(deq.begin(),deq.end());
}

//前序遍历顺序为：根 -> 左 -> 右
//后序遍历顺序为：左 -> 右 -> 根
//如果1： 我们将前序遍历中节点插入结果链表尾部的逻辑，修改为将节点插入结果链表的头部
//那么结果链表就变为了：右 -> 左 -> 根
//如果2： 我们将遍历的顺序由从左到右修改为从右到左，配合如果1
//那么结果链表就变为了：左 -> 右 -> 根
//这刚好是后序遍历的顺序
vector<int> postorderTraversalprereverse(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode*> st;
    TreeNode* cur=root;
    while(cur!=NULL||!st.empty()){
        while(cur!=NULL){
            ret.emplace_back(cur->val);
            st.emplace(cur);
            cur=cur->right;
        }
        TreeNode* top=st.top();
        st.pop();
        cur=top->left;
    }
    reverse(ret.begin(),ret.end());
    return ret;
}


//建立一个指向前一节点的指针，标记右孩子是否被访问
//niupi
vector<int> postorderTraversalflag(TreeNode* root) {
    vector<int> ret;
    stack<TreeNode *> st;
    TreeNode *cur = root;
    TreeNode* pre=NULL;
    while (cur != NULL || !st.empty()) {
        while(cur!=NULL){
            st.emplace(cur);
            cur=cur->left;
        }
        cur=st.top();
        //判断右孩子是否为空或者被访问过
        if(cur->right==NULL||cur->right==pre){
            ret.emplace_back(cur->val);
            st.pop();
            pre=cur;
            cur=NULL;
        } else
            cur=cur->right;
    }
    return ret;
}

//要求
//在二叉树的后序遍历中，常常依靠队列，要么在队列中前向插入，要么利用队列去判断该节点是否遍历过，现在要求只能利用栈去做，不能用队列去辅助判断（即，只允许在队列尾部添加答案）
//思路
//这道题的难点在于仅利用栈去判断该节点是否为父结点，创新性思路是每次在栈中压入父节点后压入nullptr，之后再依次压入右子节点和左子节点。
//妙
vector<int> postorderTraversalNULL(TreeNode* root) {
    if(root==NULL)
        return vector<int>();
    vector<int> ret;
    stack<TreeNode *> st;
    st.emplace(root);
    while(!st.empty()){
        TreeNode* top=st.top();
        if(top==NULL){
            st.pop();
            top=st.top();
            ret.emplace_back(top->val);
            st.pop();
            continue;
        }
        st.push(NULL);
        if(top->right)
            st.emplace(top->right);
        if(top->left)
            st.emplace(top->left);
    }
    return ret;
}