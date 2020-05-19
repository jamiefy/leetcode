//
// Created by anranzhai on 2020/5/19.
//
#include <iostream>
#include <vector>
using namespace std;
//给定列表中的中间元素将会作为二叉搜索树的根，该点左侧的所有元素递归的去构造左子树，同理右侧的元素
//构造右子树。这必然能够保证最后构造出的二叉搜索树是平衡的。
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

ListNode* findmid(ListNode* head){
        ListNode* pre= nullptr;
        ListNode* slow=head;
        ListNode* fast=head;
        while(fast!= nullptr&&fast->next!= nullptr){
            pre=slow;
            slow=slow->next;
            fast=fast->next->next;
        }
        if(pre!= nullptr)
            pre->next= nullptr;
        return slow;
}
//递归，时间复杂度O(nlgn)，空间复杂度O(1)
TreeNode* sortedListToBSTRecur(ListNode* head) {
    if(head== nullptr)
        return nullptr;
    ListNode* node=findmid(head);
    TreeNode* mid=new TreeNode(node->val);
    if(head==node)//当只剩下一个节点时退出递归循环，不然递归不会终止
        return mid;

    mid->left=sortedListToBSTRecur(head);
    mid->right=sortedListToBSTRecur(node->next);
    return mid;
}

vector<int> map;
TreeNode* recursive(int left,int right){
    if(left>right)
        return nullptr;
    int mid=left+(right-left>>1);//int mid=left+(right-left+1>>1);跟递归方法得出的结果一样，不加1不一样
    TreeNode* node=new TreeNode(map[mid]);
    node->left=recursive(left,mid-1);
    node->right=recursive(mid+1,right);
    return node;
}
//递归+数组，空间换时间，时间复杂度O(n),空间复杂度O(n)
TreeNode* sortedListToBSTRecursive(ListNode* head) {
    if (head == nullptr)
        return nullptr;
    ListNode* cur=head;
    while(cur!=nullptr){
        map.emplace_back(cur->val);
        cur=cur->next;
    }
    return recursive(0,map.size()-1);
}

//中序遍历一棵二叉搜索树的结果是得到一个升序序列。
//1.遍历整个链表获得它的长度，我们用两个指针标记结果数组的开始和结束，记为 start 和 end，他们的初始值分别为 0 和 length - 1。
//2.记住，我们当前需要模拟中序遍历，找到中间元素 (start + end) / 2。注意这里并不需要在链表中找到确定的元素是哪个，只需要用一个变量告诉我们中间元素的下标。我们只需要递归调用这两侧。
//3.递归左半边，其中开始和结束的值分别为 start, mid - 1。
//4.在这个算法中，每当我们构建完二叉搜索树的左半部分时，链表中的头指针将指向根节点或中间节点（它成为根节点）。 因此，我们只需使用头指针指向的当前值作为根节点，并将指针后移一位，即 head = head.next。
//5.我们在递归右半部分 mid + 1, end。
//时间复杂度：时间复杂度仍然为 O(N) 因为我们需要遍历链表中所有的顶点一次并构造相应的二叉搜索树节点。
//空间复杂度：O(logN) ，额外空间只有一个递归栈，由于是一棵高度平衡的二叉搜索树，所以高度上界为logN
ListNode* root;
TreeNode* inorder(int left,int right){
    if(left>right)
        return nullptr;

    auto mid=left+(right-left>>1);
    TreeNode* l=inorder(left,mid-1);

    TreeNode* node=new TreeNode(root->val);
    node->left=l;

    root=root->next;

    node->right=inorder(mid+1,right);
    return node;
}

TreeNode* sortedListToBST(ListNode* head) {
    if (head == nullptr)
        return nullptr;
    ListNode* cur=head;
    auto cnt=0;
    while(cur!=nullptr){
        cnt++;
        cur=cur->next;
    }

    root=head;
    return inorder(0,cnt-1);
}

int main(){
    ListNode* one=new ListNode(-10);
    ListNode* two=new ListNode(-3);
    ListNode* three=new ListNode(0);
    ListNode* four=new ListNode(5);
    ListNode* five=new ListNode(9);
    one->next=two;
    two->next=three;
    three->next=four;
    four->next=five;
    TreeNode* node=sortedListToBST(one);
    cout<<0<<endl;
}