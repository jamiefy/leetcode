//
// Created by anranzhai on 2020/5/3.
//
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

vector<int> ret;
void recur(TreeNode* root){
    if(root==NULL)
        return;
    ret.emplace_back(root->val);
    recur(root->left);
    recur(root->right);
}
vector<int> preorderTraversalRecur(TreeNode* root) {
    recur(root);
    return ret;
}

//先压最左再压右，压的过程中把最左统统输出
vector<int> preorderTraversal(TreeNode* root) {
    if(root==NULL)
        return vector<int>();
    vector<int> vec{root->val};
    stack<TreeNode*> st;
    st.emplace(root);
    TreeNode* parent=root->left;
    while(parent!=NULL||!st.empty()){
        while(parent!=NULL){
            vec.emplace_back(parent->val);
            st.emplace(parent);
            parent=parent->left;
        }
        parent=st.top()->right;
        st.pop();
    }
    return vec;
}

//从上到下，从右到左压栈——>每次弹出最左下角的节点
//运行时间几乎为0ms
vector<int> preorderTraversalUni(TreeNode* root) {
    if(root==NULL)
        return vector<int>();
    vector<int> vec;
    stack<TreeNode*> st;
    st.emplace(root);
    TreeNode* parent=root->left;
    //注意循环判断条件的不同
    while(!st.empty()){
        TreeNode* top=st.top();
        st.pop();
        vec.emplace_back(top->val);
        if(top->right!=NULL)
            st.emplace(top->right);
        if(top->left!=NULL)
            st.emplace(top->left);
    }
    return vec;
}

int main(){
    TreeNode* node0=new TreeNode(0);
    TreeNode* node1=new TreeNode(1);
    TreeNode* node2=new TreeNode(2);
    TreeNode* node3=new TreeNode(3);

    node0->left=node1;
    node0->right=node2;
    node1->left=node3;

    std::vector<int> vec;
    vec=preorderTraversal(node0);
    for(auto v:vec){
        cout<<v<<endl;
    }
}