//
// Created by anranzhai on 2020/2/28.
//
#include <iostream>
#include <map>
class Node {
public:
    int val;
    Node* next;
    Node* random;

    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};

//三步走：1.复制 2.设置random 3.拆分成原链表和复制链表
//时间复杂度O(n),空间复杂度O(1)
Node* copyRandomList(Node* head) {
    if(head==NULL)return NULL;
    Node* curr=head;
    while(curr!=NULL){
        Node *copy=new Node(*curr);
        curr->next= copy;
        curr=copy->next;
    }
    curr=head;
    while(curr!=NULL){
        Node* copy=curr->next;
        if(curr->random!=NULL)
            copy->random=curr->random->next;
        curr=copy->next;
    }
    curr=head;
    Node* copyHead=head->next;
    Node* copy;
    while(curr!=NULL){
        copy=curr->next;
        curr->next=copy->next;
        curr=curr->next;
        if(curr!=NULL)
            copy->next=curr->next;
    }
    return copyHead;
}

//哈希表时间复杂度O(n)空间复杂度O(n),执行时间最多
Node* copyRandomListHash(Node* head) {
    if(head==NULL)return NULL;
    std::map<Node*,Node*> nMap;
    Node* curr=head;
    while(curr!=NULL){
        nMap[curr]=new Node(curr->val);
        curr=curr->next;
    }
    Node* copyHead=nMap[head];
    curr=head;
    while(curr!=NULL){
        if(curr->next!=NULL)
            nMap[curr]->next=nMap[curr->next];
        if(curr->random!= nullptr)
            nMap[curr]->random=nMap[curr->random];
         curr=curr->next;
    }
    return copyHead;
}

//哈希表优化,执行时间极大减少
std::map<Node*,Node*> map;
Node* getCloned(Node* node){
    if(node==NULL)
        return NULL;
    if(map.find(node)==map.end())
        map[node]=new Node(node->val);
    return map[node];
}
Node* copyRandomLHash(Node* head) {
    if(head==NULL)return NULL;
    Node* copyHead=new Node(head->val),*copyCurr=copyHead,*curr=head;
    map[head]=copyHead;
    while(curr!=NULL){
        copyCurr->next=getCloned(curr->next);
        copyCurr->random=getCloned(curr->random);
        curr=curr->next;
        copyCurr=copyCurr->next;
    }
    return copyHead;
}

Node* copyNode(Node* node,std::map<Node*,Node*> &nodeMap) {
    if(nodeMap[node]==NULL){
        nodeMap[node]=new Node(node->val);
        if(node->next!=NULL)
            nodeMap[node]->next=copyNode(node->next,nodeMap);
        if(node->random!=NULL)
            nodeMap[node]->random=copyNode(node->random,nodeMap);
    }
    return nodeMap[node];
}
//回溯时间复杂度O(n)空间复杂度O(n)
Node* copyRandomListRecursive(Node* head) {
    std::map<Node*,Node*> nodeMap;
    if(head==NULL)return NULL;
    return copyNode(head,nodeMap);
}

//回溯,内存消耗最多
std::map<Node*,Node*> nMap;
Node* copyRandomListRecur(Node* head) {
    if(head==NULL)return NULL;
    if(nMap.find(head)!=nMap.end())
        return nMap[head];
    nMap[head]=new Node(head->val);
    nMap[head]->next=copyRandomListRecur(head->next);
    nMap[head]->random=copyRandomListRecur(head->random);
    return nMap[head];
}

int main(){
    Node *head=new Node(7);
    Node *second=new Node(13);
    Node *third=new Node(11);
    head->next=second;
    second->next=third;
    head->random=second;
    second->random=head;
    third->random=second;
    Node* copy=copyRandomLHash(head);
    while(copy!=NULL){
        std::cout<<copy->val<<"  "<<copy->random->val<<std::endl;
        copy=copy->next;
    }
}