//
// Created by anranzhai on 2020/5/30.
//
#include <iostream>
#include <queue>
using namespace std;
class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() : val(0), left(NULL), right(NULL), next(NULL) {}

    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}

    Node(int _val, Node* _left, Node* _right, Node* _next)
            : val(_val), left(_left), right(_right), next(_next) {}
};

//时间复杂度：O(N)。每个节点被访问一次，即从队列中弹出，并建立 next 指针。
//空间复杂度：O(N)。这是一棵完美二叉树，它的最后一个层级包含N/2 个节点。广度优先遍历的复杂度取决于一个层级上的最大元素数量。这种情况下空间复杂度为O(N)。
//层次遍历每次遍历一个节点
//执行时间最短
Node* connectbfs(Node* root) {
    if(root== nullptr)
        return nullptr;
    queue<pair<Node*,int>> quelist;
    quelist.emplace(root,1);
    //使用pre记录右边相邻节点
    Node* pre= nullptr;
    auto prelayer=0;
    while(!quelist.empty()){
        Node* node=quelist.front().first;
        auto layer=quelist.front().second;
        quelist.pop();

        //判断每层的最右节点
        if(prelayer<layer){
            pre= nullptr;
            prelayer++;
        }
        node->next=pre;
        pre=node;
        if(node->right!= nullptr)
            quelist.emplace(node->right,layer+1);
        if(node->left!= nullptr)
            quelist.emplace(node->left,layer+1);
    }
    return root;
}

//层次遍历 queue 不使用pair记录层数，每次直接把一整层遍历完
//时间复杂度：O(N)。每个节点被访问一次，即从队列中弹出，并建立 next 指针。
//空间复杂度：O(N)。这是一棵完美二叉树，它的最后一个层级包含N/2 个节点。广度优先遍历的复杂度取决于一个层级上的最大元素数量。这种情况下空间复杂度为O(N)。
//执行时间最长
Node* connectBFS(Node* root) {
    if(root== nullptr)
        return nullptr;
    queue<Node*> quelist;
    quelist.emplace(root);
    while(quelist.empty()){
        auto size=quelist.size();

        //层次遍历，一次一层
        for(int i=0;i<size;i++){
            Node* node=quelist.front();
            quelist.pop();
            if(i<size-1)
                node->next=quelist.front();
            if(node->left!= nullptr)
                quelist.push(node->left);
            if(node->right!= nullptr)
                quelist.push(node->right);
        }
    }
    return root;
}

//时间复杂度：O(N)，每个节点只访问一次。
//空间复杂度: O(1)，不需要存储额外的节点。
//层次遍历 每次遍历一个节点下的左节点和右节点next连接
Node* connect(Node* root) {
    if(root== nullptr)
        return nullptr;
    Node* leftmost=root;
    //判断每层最左节点是否还有左子节点，没有则是最后一层
    while(leftmost->left!= nullptr){
        Node* head=leftmost;
        //一次处理一个节点
        while(head!= nullptr){
            head->left->next=head->right;
            if(head->next!= nullptr){
                head->right->next=head->next->left;
            }
            head=head->next;
        }

        leftmost=leftmost->left;
    }
    return root;
}