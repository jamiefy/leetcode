//
// Created by anranzhai on 2020/3/23.
//
#include <iostream>
struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};
bool hasCycle(ListNode *head) {
    if(head==NULL)
        return false;
    ListNode* behind=head;
    ListNode* ahead=head->next;
    while(ahead!=NULL&&ahead->next!=NULL){
        if(ahead==behind)
            return true;
        behind=behind->next;
        ahead=ahead->next->next;
    }
    return false;
}
ListNode* hasCycleNode(ListNode *head) {
    if(head==NULL)
        return NULL;
    ListNode* behind=head;
    ListNode* ahead=head->next;
    while(ahead!=NULL&&ahead->next!=NULL){
        if(ahead==behind){
            return ahead;
        }
        behind=behind->next;
        ahead=ahead->next->next;
    }
    return NULL;
}

//给定阶段 1 找到的相遇点，阶段 2 将找到环的入口。首先我们初始化额外的两个指针： ptr1 ，指向链表的头， ptr2 指向相遇点。然后，我们每次将它们往前移动一步，直到它们相遇，它们相遇的点就是环的入口，返回这个节点。
ListNode *detectCycle(ListNode *head) {
    ListNode* behind=head;
    ListNode* ahead=hasCycleNode(head);
    if(ahead==NULL)
        return NULL;
    ahead=ahead->next;
    while(behind!=ahead){
        behind=behind->next;
        ahead=ahead->next;
    }
    return behind;
}