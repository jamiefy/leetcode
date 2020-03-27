//
// Created by anranzhai on 2020/3/27.
//
#include <iostream>
#include <vector>
#include <unordered_map>
#include <utility>
#include <stack>
int singleNumber(std::vector<int>& nums) {
    if(nums.size()==0)
        return -1;
    int ret=nums[0];
    for(int i=1;i<nums.size();i++)
        ret^=nums[i];
    return ret;
}

class Logger {
public:
    /** Initialize your data structure here. */
    Logger() {

    }

    /** Returns true if the message should be printed in the given timestamp, otherwise returns false.
        If this method returns false, the message will not be printed.
        The timestamp is in seconds granularity. */
    bool shouldPrintMessage(int timestamp, std::string message) {
        if(timeMap.find(message)==timeMap.end()){
            timeMap.insert(std::pair<std::string,int>(message,timestamp));
            return true;
        }
        if(timestamp-timeMap[message]>=10){
            timeMap[message]=timestamp;
            return true;
        }
        else
            return false;
    }

private:
    std::unordered_map<std::string,int> timeMap;
};


struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
//反向中序遍历
class BSTIterator {
public:
    BSTIterator(TreeNode* root) {
        if(root==NULL)
            return;
        init(root);
    }

    void init(TreeNode* root){
        if(root->right!=NULL)
            init(root->right);
        minStack.push(root->val);
        if(root->left!=NULL)
            init(root->left);
    }
    /** @return the next smallest number */
    int next() {
        if(hasNext()){
            int min=minStack.top();
            minStack.pop();
            return min;
        }
        return -1;
    }

    /** @return whether we have a next smallest number */
    bool hasNext() {
        if(!minStack.empty())
            return true;
        else
            return false;
    }

private:
    std::stack<int> minStack;
};