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
    ListNode* ahead=head;
    ListNode* behind=head->next;
    while(behind!=NULL&&behind->next!=NULL){
        if(ahead==behind)
            return true;
        ahead=ahead->next;
        behind=behind->next->next;
    }
    return false;
}
