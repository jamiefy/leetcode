//
// Created by anranzhai on 2020/2/28.
//
#include <iostream>
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

//哈希表时间复杂度O(n)空间复杂度O(n)
Node* copyRandomListHash(Node* head) {

}

//回溯时间复杂度O(n)空间复杂度O(n)
Node* copyRandomListRecursive(Node* head) {

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
    Node* copy=copyRandomList(head);
    while(copy!=NULL){
        std::cout<<copy->val<<"  "<<copy->random->val<<std::endl;
        copy=copy->next;
    }
}