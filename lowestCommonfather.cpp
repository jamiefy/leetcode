//
// Created by anranzhai on 2020/5/3.
//
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

//从根节点开始。
//将 (root, root_state) 放在栈上。root_state 定义要遍历该节点的一个子节点还是两个子节点。
//当栈不为空时，查看栈的顶部元素，该元素表示为 (parent_node, parent_state) 。
//在遍历 parent_node 的任何子节点之前，我们检查 parent_node 本身是否是 p 或 q 中的一个。
//当我们第一次找到 p 或 q 的时候，设置一个布尔标记，名为 one_node_found 为 true 。还可以通过在变量 LCA_index 中记录栈的顶部索引来跟踪最近的公共祖先。因为栈的所有当前元素都是我们刚刚发现的节点的祖先。
//第二次 parent_node == p or parent_node == q 意味着我们找到了两个节点，我们可以返回 LCA node 。
//每当我们访问 parent_node 的子节点时，我们将 (parent_node, updated_parent_state) 推到栈上。我们更新父级的状态为子级/分支已被访问/处理，并且相应地更改状态。
//当状态变为 BOTH_DONE 时，最终会从栈中弹出一个节点，这意味着左、右子树都被推到栈上并进行处理。如果 one_node_found 是 true 的，那么我们需要检查被弹出的顶部节点是否可能是找到的节点的祖先之一。在这种情况下，我们需要将 LCA_index 减一。因为其中一位祖先被弹出了。
//当同时找到 p 和 q 时，LCA_index 将指向栈中包含 p 和 q 之间所有公共祖先的索引。并且 LCA_index 元素具有 p 和 q 之间的最近公共祖先。
//
//时间复杂度：O(n).其中 N是二叉树中的节点数。在最坏的情况下，我们可能会访问二叉树的所有节点。
//这种方法的优点是可以减少回溯。只要找到两个节点，我们就返回。
//空间复杂度：O(n).在最坏的情况下，栈使用的空间是 N 且斜二叉树的高度可能是 N。
class Solution {
enum {BOTH_DONE = 0,LEFT_DONE,BOTH_PENDING};
//一定程度上模拟后序遍历
TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
    if (root == NULL)
        return NULL;
    stack<pair<TreeNode *, int>> st;
    TreeNode* LCA=NULL;
    TreeNode* childnode=NULL;
    bool one_node_find= false;
    st.push(pair<TreeNode*,int>(root,BOTH_PENDING));

    while(!st.empty()){
        auto top=st.top();
        TreeNode* parentnode=top.first;
        if(top.second!=BOTH_DONE){
            //如果该节点左右节点没有遍历完
            if(top.second==BOTH_PENDING){
                //如果该节点左节点还未遍历，visit该节点
                if(top.first==p||top.first==q){
                    if(one_node_find){
                        return LCA;
                    }
                    one_node_find=true;
                    LCA=top.first;
                }
                //不管该节点是否是所查找的节点都要继续向左遍历
                childnode=top.first->left;
            } else{
                //如果该节点左节点已经遍历过了，说明已经visit该节点，则此次不用visit，可直接遍历其右节点
                childnode=top.first->right;
            }
            //改变该节点的遍历状态
            st.top().second-=1;
            //当子节点不为空时把子节点压入栈
            if(childnode!=NULL)
                st.push(pair<TreeNode*,int>(childnode,BOTH_PENDING));
        } else{
            //该节点左右节点都遍历过了，判断该节点是否被LCA指向，如果指向且已经找到一个节点则改变LCA记录当前最小公共父节点，
            //继续寻找另一个；不指向或者并没有找到一个节点则直接弹出
            if(parentnode==LCA && one_node_find){
                st.pop();
                LCA=st.top().first;
            } else
                st.pop();
        }
    }
    return NULL;
}
};
