//
// Created by anranzhai on 2020/7/30.
//
#include <iostream>
using  namespace std;
class Node {
public:
    int val;
    Node* left;
    Node* right;

    Node() {}

    Node(int _val) {
        val = _val;
        left = NULL;
        right = NULL;
    }

    Node(int _val, Node* _left, Node* _right) {
        val = _val;
        left = _left;
        right = _right;
    }
};

//有序双向链表
Node* treeToDoublyList(Node* root) {
    if(root==nullptr)
        return nullptr;
    if(root->left== nullptr&&root->right== nullptr)
        return root;

    Node* left=treeToDoublyList(root->left);
    Node* cur=left;
    while(cur!= nullptr && cur->right!=nullptr){
        cur=cur->right;
    }
    if(cur!= nullptr){
        cur->right=root;
        root->left=cur;
    }

    Node* next=treeToDoublyList(root->right);
    if(next!=nullptr){
        next->left=root;
        root->right=next;
    }
    return left!= nullptr?left:root;
}



Node* treeToList(Node* root){
    if(root==nullptr)
        return nullptr;
    if(root->left== nullptr&&root->right== nullptr)
        return root;

    Node* left=treeToList(root->left);
    if(left!=nullptr){
        Node* cur=left;
        while(cur!= nullptr){
            if(cur->right!=nullptr)
                cur=cur->right;
            else
                break;
        }
        if(cur!= nullptr){
            cur->right=root;
            root->left=cur;
        }
    }


    Node* next=treeToList(root->right);
    if(next!=nullptr){
        next->left=root;
        root->right=next;
    }
    return left!= nullptr?left:root;
}
//循环双向链表，注意首尾节点也要连接
Node* treeToDoublyListXunHuan(Node* root) {
    if(root==nullptr)
        return nullptr;
    Node* p=treeToList(root);
    Node* tail=p;
    while(tail!=nullptr&&tail->right!=nullptr){
        tail=tail->right;
    }
    tail->right=p;
    p->left=tail;
    return p;
}

//中序遍历，pre cur连接相邻节点，执行速度最快
Node* treeToDoublyListInorderMirrors(Node* root) {
    if(root==nullptr)
        return nullptr;
    Node *cur = root;
    Node *head =nullptr;
    Node *pre =nullptr;
    while (cur != NULL) {
        if (cur->left == NULL) {
            //这里遍历了叶子节点（没有左节点也就没有右节点，就是叶子结点）
            if(head==nullptr)
                head=cur;
            cur->left=pre;
            if(pre!=nullptr)
                pre->right=cur;

            pre=cur;
            //cur指向被添加的索引，否则就是整棵树的最右叶子节点
            cur = cur->right;
        } else {
            Node *temp = cur->left;
            while (temp->right != NULL && temp->right != cur) {
                temp = temp->right;
            }

            if (temp->right == NULL) {
                //这是填充线索的过程
                temp->right = cur;
                cur = cur->left;
            } else {
                //这里遍历了每个子树的根节点
                cur->left=temp;
                pre=cur;//遍历节点的过程中每次更新cur都要更新pre
                cur = cur->right;
            }
        }
    }
    Node* tail=head;
    while(tail!=nullptr&&tail->right!=nullptr){
        tail=tail->right;
    }
    head->left=tail;
    tail->right=head;
    return head;
}

int main(){
    Node* one=new Node(0);
    Node* left=new Node(-2);
    Node* right=new Node(2);
    one->left=left;
    one->right=right;

    Node* lleft=new Node(-3);
    Node* lright=new Node(-1);
    left->left=lleft;
    left->right=lright;

    Node* rleft=new Node(1);
    Node* rright=new Node(3);
    right->left=rleft;
    right->right=rright;

    Node* ret=treeToDoublyList(one);
    cout<<1;

}