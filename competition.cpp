//
// Created by anranzhai on 2020/3/1.
//
#include <vector>
#include <algorithm>
#include <stack>
std::vector<int> smallerNumbersThanCurrent(std::vector<int>& nums) {
    if(nums.empty())
        return nums;
    std::vector<int> ret(nums);
    std::sort(nums.begin(),nums.end());
    for(auto it=ret.begin();it!=ret.end();it++){
        auto iterater=std::find_first_of(nums.begin(),nums.end(),it,it+1);
        *it=iterater-nums.begin();
    }
    return ret;
}

//类似于桶排序，时间复杂度空间复杂度O(n)
std::vector<int> smallerNumbersThanCurrentImp(std::vector<int>& nums) {
    std::vector<int> cnt(101,0);
    for (auto num: nums) {
        cnt[num]++;
    }
    for (int i = 1; i <= 100; i++) {
        cnt[i] +=cnt[i-1];
    }
    std::vector<int> ans;
    for (auto num: nums) {
        if(num!=0)
            ans.push_back(cnt[num-1]);
        else
            ans.push_back(0);
    }
    return ans;
}


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

bool getIsSubPath(ListNode* head, TreeNode* root){
    if(head==NULL)
        return true;
    if(root==NULL)
        return false;
    if(head->val==root->val)
        return getIsSubPath(head->next,root->left) || getIsSubPath(head->next,root->right);
    else
        return false;
}

bool isSubPath(ListNode* head, TreeNode* root) {
    if(head==NULL)
        return true;
    if(root==NULL)
        return false;
    ListNode* currListNode=head;
    TreeNode* currTreeNode;
    std::stack<TreeNode*> treeStack;
    treeStack.push(root);
    while(!treeStack.empty()){
        currTreeNode=treeStack.top();
        if(getIsSubPath(currListNode,currTreeNode))
            return true;
        else{
            treeStack.pop();
            if(currTreeNode->left!=NULL)
                treeStack.push(currTreeNode->left);
            if(currTreeNode->right!=NULL)
                treeStack.push(currTreeNode->right);
        }
    }
    return false;
}

